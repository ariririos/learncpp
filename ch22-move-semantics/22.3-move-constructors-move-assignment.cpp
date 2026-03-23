#include <chrono>
#include <iostream>

template <typename T> class Auto_ptr3 {
    T *m_ptr {};

public:
    Auto_ptr3(T *ptr = nullptr) : m_ptr { ptr } {}
    ~Auto_ptr3() { delete m_ptr; }
    Auto_ptr3(const Auto_ptr3 &a) {
        m_ptr = new T;
        *m_ptr = *a.m_ptr;
    }
    Auto_ptr3 &operator=(const Auto_ptr3 &a) {
        if (&a == this) {
            return *this;
        }
        delete m_ptr;
        m_ptr = new T;
        *m_ptr = *a.m_ptr;
        return *this;
    }
    T &operator*() const { return *m_ptr; }
    T *operator->() const { return m_ptr; }
    bool is_null() const { return m_ptr == nullptr; }
};

class Resource {
public:
    Resource() { std::cout << "Resource acquired\n"; }
    ~Resource() { std::cout << "Resource destroyed\n"; }
};

Auto_ptr3<Resource> generate_resource() {
    Auto_ptr3<Resource> res { new Resource };
    return res;
}

template <typename T> class Auto_ptr4 {
    T *m_ptr {};

public:
    Auto_ptr4(T *ptr = nullptr) : m_ptr { ptr } {}
    ~Auto_ptr4() { delete m_ptr; }
    // copy constructor
    Auto_ptr4(const Auto_ptr4 &a) {
        m_ptr = new T;
        *m_ptr = *a.m_ptr;
    }
    // move constructor
    Auto_ptr4(Auto_ptr4 &&a) noexcept : m_ptr { a.m_ptr } { a.m_ptr = nullptr; }
    // copy assignment
    Auto_ptr4 &operator=(const Auto_ptr4 &a) {
        if (&a == this) {
            return *this;
        }
        // release whatever we're holding
        delete m_ptr;
        // do the copy
        m_ptr = new T;
        *m_ptr = *a.m_ptr;
        return *this;
    }
    // move assignment
    Auto_ptr4 &operator=(Auto_ptr4 &&a) noexcept {
        if (&a == this) {
            return *this;
        }
        // release whatever we're holding
        delete m_ptr;
        // transfer ownership
        m_ptr = a.m_ptr;
        a.m_ptr = nullptr;
        return *this;
    }
    T &operator*() const { return *m_ptr; }
    T *operator->() const { return m_ptr; }
    bool is_null() const { return m_ptr == nullptr; }
};

Auto_ptr4<Resource> generate_resource2() {
    Auto_ptr4<Resource> res { new Resource };
    return res; // returning invokes the move constructor
}

template <typename T> class Auto_ptr5 {
    T *m_ptr {};

public:
    Auto_ptr5(T *ptr = nullptr) : m_ptr { ptr } {}
    ~Auto_ptr5() { delete m_ptr; }
    // copy constructor
    Auto_ptr5(const Auto_ptr5 &a) = delete;
    // move constructor
    Auto_ptr5(Auto_ptr5 &&a) noexcept : m_ptr { a.m_ptr } { a.m_ptr = nullptr; }
    // copy assignment
    Auto_ptr5 &operator=(const Auto_ptr5 &a) = delete;
    // move assignment
    Auto_ptr5 &operator=(Auto_ptr5 &&a) noexcept {
        if (&a == this) {
            return *this;
        }
        // release whatever we're holding
        delete m_ptr;
        // transfer ownership
        m_ptr = a.m_ptr;
        a.m_ptr = nullptr;
        return *this;
    }
    T &operator*() const { return *m_ptr; }
    T *operator->() const { return m_ptr; }
    bool is_null() const { return m_ptr == nullptr; }
};

void use_resource([[maybe_unused]] Auto_ptr5<Resource> a) {}

template <typename T> class DynamicArray {
private:
    T *m_array {};
    int m_length {};
    void alloc(int length) {
        m_array = new T[static_cast<std::size_t>(length)];
        m_length = length;
    }

public:
    DynamicArray(int length) { alloc(length); }
    ~DynamicArray() { delete[] m_array; }
    DynamicArray(const DynamicArray &arr) {
        alloc(arr.m_length);
        std::copy_n(arr.m_array, m_length, m_array);
    }
    DynamicArray &operator=(const DynamicArray &arr) {
        if (&arr == this) {
            return *this;
        }
        delete[] m_array;
        alloc(arr.m_length);
        std::copy_n(arr.m_array, m_length, m_array);
        return *this;
    }
    int get_length() const { return m_length; }
    T &operator[](int index) { return m_array[index]; }
    const T &operator[](int index) const { return m_array[index]; }
};

class Timer {
private:
    // Type aliases to make accessing nested type easier
    using Clock = std::chrono::high_resolution_clock;
    using Second = std::chrono::duration<double, std::ratio<1>>;

    std::chrono::time_point<Clock> m_beg { Clock::now() };

public:
    void reset() { m_beg = Clock::now(); }

    double elapsed() const {
        return std::chrono::duration_cast<Second>(Clock::now() - m_beg).count();
    }
};

DynamicArray<int> clone_array_and_double(const DynamicArray<int> &arr) {
    DynamicArray<int> dbl(arr.get_length());
    for (int i { 0 }; i < arr.get_length(); ++i) {
        dbl[i] = arr[i] * 2;
    }
    return dbl;
}

template <typename T> class DynamicArray2 {
private:
    T *m_array {};
    int m_length {};
    void alloc(int length) {
        m_array = new T[static_cast<std::size_t>(length)];
        m_length = length;
    }

public:
    DynamicArray2(int length) { alloc(length); }
    ~DynamicArray2() { delete[] m_array; }
    DynamicArray2(const DynamicArray2 &arr) = delete;
    DynamicArray2 &operator=(const DynamicArray2 &arr) = delete;
    DynamicArray2(DynamicArray2 &&arr) noexcept
        : m_array { arr.m_array }, m_length { arr.m_length } {
        arr.m_length = 0;
        arr.m_array = nullptr;
    }
    DynamicArray2 &operator=(DynamicArray2 &&arr) noexcept {
        if (&arr == this) {
            return *this;
        }
        delete[] m_array;
        m_length = arr.m_length;
        m_array = arr.m_array;
        arr.m_length = 0;
        arr.m_array = nullptr;
        return *this;
    }
    int get_length() const { return m_length; }
    T &operator[](int index) { return m_array[index]; }
    const T &operator[](int index) const { return m_array[index]; }
};

DynamicArray2<int> clone_array_and_double2(const DynamicArray2<int> &arr) {
    DynamicArray2<int> dbl(arr.get_length());
    for (int i { 0 }; i < arr.get_length(); ++i) {
        dbl[i] = arr[i] * 2;
    }
    return dbl;
}

class Name {
private:
    std::string m_name {};

public:
    Name(std::string_view name) : m_name { name } {}
    Name(const Name &name) = delete;
    Name &operator=(const Name &name) = delete;
    Name(Name &&name) = delete;
    Name &operator=(Name &&name) = delete;
    const std::string &get() const { return m_name; }
};

class Name2 {
private:
    std::string m_name {}; // std::string is move capable

public:
    Name2(std::string_view name) : m_name { name } {}
    Name2(const Name2 &name) = delete;
    Name2 &operator=(const Name2 &name) = delete;
    Name2(Name2 &&name) noexcept {
        std::cout << "Move ctor\n";
        std::swap(*this, name);
    }
    Name2 &operator=(Name2 &&name) noexcept {
        std::cout << "Move assign\n";
        std::swap(*this, name);
        return *this;
    }
    const std::string &get() const { return m_name; }
};

class Name3 {
private:
    std::string m_name {}; // std::string is move capable

public:
    Name3(std::string_view name) : m_name { name } {}
    Name3(const Name3 &name) = delete;
    Name3 &operator=(const Name3 &name) = delete;
    friend void swap(Name3 &a, Name3 &b) noexcept {
        // no infinite recursion because we call swap on the string members, not the class itself
        std::swap(a.m_name, b.m_name);
    }
    Name3(Name3 &&name) noexcept {
        std::cout << "Move ctor\n";
        swap(*this, name);
    }
    Name3 &operator=(Name3 &&name) noexcept {
        std::cout << "Move assign\n";
        swap(*this, name);
        return *this;
    }
    const std::string &get() const { return m_name; }
};

int main() {
    // with copy constructors and copy assignment, we do shallow copies by default and optionally implement deep copies
    {
        std::cout << "With copies:\n";
        Auto_ptr3<Resource> mainres;
        mainres = generate_resource();
    }
    /*
    this prints either 6 or 4 lines depending on whether the return value of generate_resource is copy elided:
    ```
    Resource acquired // Resource allocated into res in generate_resource()
    Resource acquired // res is returned back to main() by value; if not elided, the copy constructor for Auto_ptr3 makes a deep copy so we allocate a new Resource here into a temporary object
    Resource destroyed // res goes out of scope so the original Resource is destroyed
    Resource acquired // the temporary object is copied to mainres by copy assignment, which is also defined to do a deep copy
    Resource destroyed // at the end of the assignment expression the temporary object is destroyed
    Resource destroyed // at the end of the block mainres goes out of scope and the Resource is destroyed
    ```
    because we call the copy constructor once to put res into a temporary and copy assignment once to put the temporary into mainres, we have two extra objects allocated
    */

    // in c++11 we have move constructors and move assignment, which transfer resources from one object to another
    // while the copy constructor and assignment take a const l-value reference, the move constructor and assignment take a non-const r-value reference
    {
        std::cout << "With moves:\n";
        Auto_ptr4<Resource> mainres2;
        mainres2 = generate_resource2(); // assignment invokes move assignment
    }
    /*
    this only prints two lines:
    ```
    Resource acquired // Resource allocated into res in generate_resource2()
    // res is returned to main() by value so res is move constructed into a temporary object, meaning the Resource is transferred into it
    // res goes out of scope, ~Auto_ptr4() runs and deletes a nullptr (doing nothing)
    // the temporary object is move assigned to mainres, transferring the Resource into it
    // at the end of the assignment, the temporary is destroyed, ~Auto_ptr4() runs and again deletes nothing
    Resource destroyed // at the end of the block mainres2 goes out of scope and the Resource is destroyed
    ```
    instead of two (or one) copies, creating two (or one) extra objects, we do two transfers and keep the single original Resource
    */
    // move constructors and move assignment should be marked noexcept, telling the compiler that they won't throw exceptions (see 27.9 and 27.10)

    // the move constructor and assignment are called when they're defined and their argument is an rvalue, usually a literal or temporary; copies are made otherwise, i.e. for lvalues or when the move constructor and assignment aren't defined

    // an implicit move constructor and assignment will be defined if all of the following are true:
    // - no user-declared copy constructor or assignment
    // - no user-declared move constructor or assignment
    // - no user-declared destructor
    // they do a memberwise move, meaning each member's move constructor or assignment is called if defined, otherwise making copies
    // ** this means pointers will be copied not moved so the move constructor and assignment need to be user-defined to avoid that **

    // => move semantics eliminate the need to pretend that r-values will exist beyond the expression where they're used; with l-values we can't do this in case we use them again, but r-values *cannot* be referred to after their containing expression, so it's safe to move resources out of them

    // move functions should leave both objects in a valid state -- this is why we did `a.m_ptr = nullptr` at the end of the move functions above. otherwise when the destructor is called on the rvalue, we will deallocate the resource it's holding, and cause undefined behavior when using m_ptr

    // automatic (storage duration) l-values returned by value may be moved instead of copied (even though they're not r-values); this is what's happening in generate_resource2(). but the compiler can decide to completely elide the move/copy instead

    // classes that support moves often have the copy functions deleted; this ensures that we can't pass objects of that class to a function by value (we should probably be using const l-value references anyway)
    {
        Auto_ptr5<Resource> mainres3;
        // use_resource(mainres3); // won't compile, deleted copy constructor
    }

    // => Auto_ptr5 is now a *good* smart pointer. the stdlib provides std::unique_ptr which works nearly identically to this one

    // let's see a smart pointer class managing an array:
    Timer t;
    DynamicArray<int> arr(1000000);
    for (int i { 0 }; i < arr.get_length(); ++i) {
        arr[i] = i;
    }
    arr = clone_array_and_double(arr);
    std::cout << "Time elapsed with 1e6 copies: " << t.elapsed() << "s\n";

    Timer t2;
    DynamicArray2<int> arr2(1000000);
    for (int i { 0 }; i < arr2.get_length(); ++i) {
        arr2[i] = i;
    }
    arr2 = clone_array_and_double2(arr2);
    std::cout << "Time elapsed with 1e6 moves: " << t2.elapsed() << "s\n";

    // we can delete the move constructor or assignment operator the same way as any other
    // if we delete the copy constructor, the compiler won't generate an implicit move constructor, meaning the class won't be copyable or movable
    // we should be explicit about our desired behavior in this case -- either delete the move constructor explicitly (no copies or moves) or default it (moves only)
    Name n1 { "Alex" };
    // n1 = Name { "Joe" }; // won't work, no move assignment operator

    // => the rule of five says that if any of the copy constructor, copy assignment, move constructor, move assignment, or destructor are defined or deleted, then all five should be defined or deleted

    // if we delete just the move functions to try and have an object that's only copyable but not movable, this makes it impossible to return the class by value in cases where mandatory copy elision doesn't apply
    // this happens because a deleted move constructor still participates in overload resolution, and return by value will favor a deleted move constructor over a non-deleted copy constructor
    /*
    for example this wouldn't work:
    Name get_joe() {
        Name joe { "Joe" };
        return joe; // call to deleted move constructor
    }
    int main() {
        Name n { get_joe() };
    }
    */

    // previously we used the copy-and-swap idiom to implement operator= without overly duplicating the copy constructor
    // this has two benefits:
    // - the persistent object now controls the resources that the dying object previously held (main goal)
    // - the dying object now controls the resources that the persistent object previously held and it can do proper cleanup
    // but this doesn't work if we try to use std::swap, because it calls the move constructor and move assignment on move-capable objects, resulting in infinite recursion
    // for example this will loop forever:
    // Name2 n2 { "Alex" };
    // n2 = Name2 { "Joe" };
    // std::cout << n2.get() << "\n";
    // but we can implement our own swap function instead:
    Name3 n3 { "Alex" };
    n3 = Name3 { "Joe" };
    std::cout << n3.get() << "\n";

    return 0;
}