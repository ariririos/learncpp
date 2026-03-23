#include <iostream>

template <typename T> class Auto_ptr1 {
    T *m_ptr {};

public:
    Auto_ptr1(T *ptr = nullptr) : m_ptr { ptr } {}
    ~Auto_ptr1() { delete m_ptr; }

    // to satisfy -Weffc++
    // Auto_ptr1(const Auto_ptr1 &) = delete;
    // Auto_ptr1 operator=(const Auto_ptr1 &) = delete;

    T &operator*() const { return *m_ptr; }
    T *operator->() const { return m_ptr; }
};

class Resource {
public:
    Resource() { std::cout << "Resource acquired\n"; }
    ~Resource() { std::cout << "Resource destroyed\n"; }
    void say_hi() { std::cout << "Hi!\n"; }
};

void pass_by_value(Auto_ptr1<Resource> res) {}

template <typename T> class Auto_ptr2 {
    T *m_ptr {};

public:
    Auto_ptr2(T *ptr = nullptr) : m_ptr { ptr } {}
    ~Auto_ptr2() { delete m_ptr; }

    // this copy constructor implements move semantics
    Auto_ptr2(Auto_ptr2 &a) { // can't be const
        m_ptr = a.m_ptr;      // transfer the pointer
        a.m_ptr = nullptr;    // and invalidate the source
    }

    // this assignment operator implements move semantics
    Auto_ptr2 &operator=(Auto_ptr2 &a) {
        if (&a == this) {
            return *this;
        }
        delete m_ptr;      // deallocate any existing internal memory
        m_ptr = a.m_ptr;   // transfer the pointer
        a.m_ptr = nullptr; // and invalidate the source
        return *this;
    }

    T &operator*() const { return *m_ptr; }
    T *operator->() const { return m_ptr; }
    bool is_null() const { return m_ptr == nullptr; }
};

int main() {
    // forgetting to deallocate memory, whether at the end of a function or because of multiple code paths or on exception, can be prevented using destructors
    Auto_ptr1<Resource> res1 { new Resource() };
    // Auto_ptr1 owns Resource -- there isn't any way to access it afterwards except through Auto_ptr1

    int x;
    std::cout << "Enter an integer: ";
    std::cin >> x;
    if (x == 0) {
        return 0; // Resource deallocated here
    }
    res1->say_hi();
    // or here (the end of the function)

    // Auto_ptr1<Resource> res2 { res1 }; // because we didn't specify the copy constructor, this will copy the pointer from res1
    // meaning at the end of this function ~res1 and ~res2 will both run and result in a double free
    // pass_by_value(res1); // this does the same thing because it makes a copy into the parameter, and the parameter is destroyed at the end of the function

    // to fix this issue we can define the copy constructor and assignment operator since we shouldn't be passing Auto_ptr1 by value anyway
    // but then that means that returning Auto_ptr1 from a function doesn't work:
    /// ??? generate_resource() {
    //      Resource *r { new Resource() };
    //      return Auto_ptr1 { r };
    // }
    // returning by reference doesn't work because the Auto_ptr1 will be destroyed at the end of the function; we could return the pointer r directly but that defeats the purpose; and returning by value causes the shallow-copy double-free problem from before
    // one method is to make the copy constructor and assignment operator do deep copies every time and avoid duplicate references to the same object by just creating new objects every time
    // but if we don't want to do deep copies every time we return from a function (which a dumb pointer doesn't do anyway), we could implement a copy constructor with move semantics

    // move semantics means that we transfer/move ownership of the pointer from the source to the destination object rather than making a copy
    Auto_ptr2<Resource> res3(new Resource()); // Resource acquired once here
    Auto_ptr2<Resource> res4;                 // starts as nullptr
    std::cout << "res3 is " << (res3.is_null() ? "null" : "not null") << "\n";
    std::cout << "res4 is " << (res4.is_null() ? "null" : "not null") << "\n";
    res4 = res3; // transferring ownership
    std::cout << "Ownership transferred\n";
    std::cout << "res3 is " << (res3.is_null() ? "null" : "not null") << "\n";
    std::cout << "res4 is " << (res4.is_null() ? "null" : "not null") << "\n";
    // Resource destroyed here in ~res4
    // (deleting a nullptr does nothing so when ~res3 runs it's fine)

    // aside: std::auto_ptr existed from c++98 through c++17 as the first attempt at a standardized smart pointer
    // it implemented move semantics through the copy constructor and assignment operator
    // it had several problems:
    // - passing it through a function parameter would mean that the underlying resources are transferred to the parameter and destroyed at the end of the function
    // - it always deleted its contents using non-array delete meaning it wouldn't properly deallocate arrays; it also didn't prevent you from passing arrays in the first place
    // - it caused problems with the rest of the stdlib because they assume that a copy does a copy, not a move

    // to fix these issues with std::auto_ptr, move semantics were formally introduced in c++11 to separate copies from moves, and move-aware smart pointers were added: std::unique_ptr, std::weak_ptr, std::shared_ptr

    return 0;
}