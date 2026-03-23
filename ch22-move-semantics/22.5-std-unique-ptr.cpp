#include <iostream>
#include <memory>

class Resource {
public:
    Resource() { std::cout << "Resource acquired\n"; }
    ~Resource() { std::cout << "Resource destroyed\n"; }
};

std::ostream &operator<<(std::ostream &out, const Resource &) {
    out << "I am a resource\n";
    return out;
}

class Fraction {
private:
    int m_numerator { 0 };
    int m_denominator { 1 };

public:
    Fraction(int numerator = 0, int denominator = 1)
        : m_numerator { numerator }, m_denominator { denominator } {}

    friend std::ostream &operator<<(std::ostream &out, const Fraction &f) {
        out << f.m_numerator << '/' << f.m_denominator;
        return out;
    }
};

std::unique_ptr<Resource> create_resource() {
    return std::make_unique<Resource>();
}

void take_ownership(std::unique_ptr<Resource> res) {
    if (res) {
        std::cout << *res << "\n";
    }
}

void use_resource(const Resource *res) {
    if (res) {
        std::cout << *res;
    } else {
        std::cout << "No resource\n";
    }
}

int main() {
    // std::unique_ptr (c++11) should be used to manage any dynamically allocated object that isn't shared by multiple objects; it should completely own the object it manages
    {
        std::unique_ptr<Resource> res { new Resource };
    } // Resource destroyed here

    // std::unique_ptr properly implements move semantics:
    {
        std::unique_ptr<Resource> res1 { new Resource {} };
        std::unique_ptr<Resource> res2 {};

        std::cout << "res1 is " << (res1 ? "not null" : "null") << "\n";
        std::cout << "res2 is " << (res2 ? "not null" : "null") << "\n";

        // res2 = res1; // won't compile, copy assignment disabled
        res2 = std::move(res1);

        std::cout << "Ownership transferred\n";

        std::cout << "res1 is " << (res1 ? "not null" : "null") << "\n";
        std::cout << "res2 is " << (res2 ? "not null" : "null") << "\n";
    } // Resource destroyed here

    // std::unique_ptr overloads operator* to return a reference to the managed object, and operator-> to return a pointer
    // it can be empty, either because it was created empty (default constructor or given a nullptr) or moved from; we can check if it's null or not by casting to bool
    {
        std::unique_ptr<Resource> res { new Resource {} };
        if (res) {
            std::cout << *res;
        }
    }

    // std::unique_ptr handles arrays correctly and will use scalar delete or array delete appropriately; but a std::array, std::vector, or std::string are almost always a better choice

    // std::make_unique (c++14) creates an object with the template type and initialized with the arguments passed in
    // create one single dynamically allocated Fraction:
    auto f1 { std::make_unique<Fraction>(3, 5) };
    std::cout << *f1 << "\n"; // prints 3/5

    // create a dynamically allocated array of Fractions of length 4
    auto f2 { std::make_unique<Fraction[]>(4) };
    std::cout << f2[0] << "\n"; // prints 0/1
    // std::make_unique saves a bit of typing and specifically in c++14 it resolves an exception safety issue

    // the exception safety issue:
    // in an expression like this one --
    // some_function(std::unique_ptr<T>(new T), function_that_can_throw_exception())
    // the compiler (until c++17) could decide to evaluate these function arguments by:
    // 1. creating a new T
    // 2. calling function_that_can_throw_exception()
    // 3. creating the std::unique_ptr
    // and if an exception occurred in step 2, then the T allocated in step 1 wouldn't be deallocated and would leak
    // std::make_unique doesn't have this problem because it handles allocating T and creating std::unique_ptr within itself where order of execution is unambiguous
    // but c++17 fixes this anyway by disallowing interleaved evaluation of function arguments

    {
        auto ptr { create_resource() };
        // create_resource() returns a std::unique_ptr by value; if it hadn't been assigned to a variable, the Resource would've been destroyed when create_resource() returns
        // since it was assigned to a variable, in c++14 and earlier, move semantics will be employed to transfer the Resource from the return value to the object assigned to in main(); in c++17 or newer, the return will be elided
        // the combination of these two behaviors (cleaning up when not assigned and move assignment/elision when assigned to a variable) make returning a std::unique_ptr much safer than returning a raw pointer
        // std::unique_ptr should not be returned by pointer (ever) or reference (unless there's a good reason)
    }

    // if passing std::unique_ptr to a function, we can pass by value if we want the function to take ownership of the contents of the pointer (we need to use std::move to actually do the move)
    {
        auto ptr { std::make_unique<Resource>() };
        // take_ownership(ptr); // won't work, copy assignment disabled
        take_ownership(std::move(
            ptr)); // Resource destroyed at the end of take_ownership()
        std::cout << "Back in main()\n";
    }

    // but if we don't want the function to take ownership, we have a couple options: pass the std::unique_ptr by const reference (not preferred), or pass the resource itself by pointer or reference (depending on whether null is allowed) -- allowing the function to remain agnostic of how the caller manages its resources
    // .get() extracts a raw pointer from a std::unique_ptr
    {
        auto ptr { std::make_unique<Resource>() };
        use_resource(ptr.get());
        std::cout << "Back in main()\n";
    }

    // we can have a std::unique_ptr as a member of our class, and it will be automatically destroyed when the class object is destroyed
    // but the std::unique_ptr won't be destroyed if the class object isn't destroyed properly (e.g. it's dynamically allocated and not deallocated properly)

    // **don't have multiple std::unique_ptr managing the same resource**, it will lead to a double free
    // **don't delete the resource out from underneath the std::unique_ptr**, will also lead to a double free
    // both of these problems can be prevented by using std::make_unique()
    return 0;
}