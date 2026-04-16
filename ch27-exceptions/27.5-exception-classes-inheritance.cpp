#include <exception>
#include <iostream>
#include <limits>
#include <stdexcept>

class Member {
public:
    Member() { std::cerr << "Member allocated some resources\n"; }
    ~Member() { std::cerr << "Member cleaned up\n"; }
};

class A {
private:
    int m_x {};
    Member m_member;

public:
    A(int x) : m_x { x } {
        if (x <= 0) {
            throw 1;
        }
    }
    ~A() {
        std::cerr << "~A\n"; // shouldn't get called
    }
};

class ArrayException {
private:
    std::string m_error;

public:
    ArrayException(std::string_view error) : m_error { error } {}

    const std::string &get_error() const { return m_error; }
};

class IntArray {
private:
    int m_data[3] {};

public:
    IntArray() {}

    int get_length() const { return 3; }

    int &operator[](const int index) {
        if (index < 0 || index >= get_length()) {
            throw ArrayException { "Invalid index" };
        }
        return m_data[index];
    }
};

class Base {
public:
    Base() {}
};

class Derived : public Base {
public:
    Derived() {}
};

class StandardArrayException : public std::exception {
private:
    std::string m_error {};

public:
    StandardArrayException(std::string_view error) : m_error { error } {}

    // to count as an override our what() must be const and noexcept
    const char *what() const noexcept override { return m_error.c_str(); }
};

class StandardIntArray {
private:
    int m_data[3] {};

public:
    StandardIntArray() {}

    int get_length() const { return 3; }

    int &operator[](const int index) {
        if (index < 0 || index >= get_length()) {
            throw StandardArrayException { "Invalid index" };
        }
        return m_data[index];
    }
};

class RuntimeArrayException : public std::runtime_error {
public:
    RuntimeArrayException(const std::string &error)
        : std::runtime_error { error } {}
};

class RuntimeIntArray {
private:
    int m_data[3] {};

public:
    RuntimeIntArray() {}

    int get_length() const { return 3; }

    int &operator[](const int index) {
        if (index < 0 || index >= get_length()) {
            throw RuntimeArrayException { "Invalid index" };
        }
        return m_data[index];
    }
};

namespace NonCopyable {
    class Base {
    public:
        Base() {}
    };

    class Derived : public Base {
    public:
        Derived() {}
        Derived(const Derived &) = delete;
    };
} // namespace NonCopyable

int main() {
    // we can't change the signature of overloaded operators, so passing errors back through in-out parameters is impossible
    // we can use assertions to at least crash the program on debug builds, but exceptions are a better option and don't change function signatures; for example:
    /*
    int& IntArray::operator[](const int index) {
        if (index < 0 || index >= get_length()) {
            throw index;
        }
        return m_data[index];
    }
    */

    // we can use exceptions in object constructors, which will abort construction of the object and all class members (which are created and initialized before the body of the constructor runs) will be destructed as per usual
    // the class's destructor will never run because the object never finished construction, so we can't rely on it to clean up
    // we could wrap any code in the constructor that can fail in a try block, use a corresponding catch block to catch the exception, then rethrow the exception (see 27.6)
    // a better way is to do any resource allocations inside the member of the class rather than in the body of the constructor, and take advantage of the fact that class members are destructed even if the constructor fails
    try {
        A a { 0 }; // Member constructed here
        // Member destroyed here
    } catch (int) {
        std::cerr << "Oops\n";
    }

    // but instead of using our own classes, we can use c++ builtin types like std::fstream (for handling files, 28.6) and std::unique_ptr to handle resources for us:
    /*
    // instead of:
    ```
    class Foo {
    private:
        int* ptr;
    }```
    // we can do:
    ```
    class Foo {
    private:
        std::unique_ptr<int> ptr;
    }
    ```
    */
    // in the first case, if the Foo constructor failed, we'd have to handle cleanup ourselves
    // but in the second case, ptr's destructor would execute; we don't have to explicitly do any cleanup if we delegate resource handling to RAII-compliant members

    // instead of using fundamental types for errors, which suffer from ambiguity and difficulty with multiple error conditions, we can use exception classes, which are just regular classes designed to be thrown as exceptions
    IntArray array {};
    try {
        [[maybe_unused]] int value { array[5] };
    } catch (const ArrayException &exception) {
        // we catch class exception objects by const reference rather than by value to avoid copies and object slicing with derived classes
        std::cerr << "An array exception occurred (" << exception.get_error()
                  << ")\n";
    }

    // exception handlers will match both classes of a specific type and all classes derived from that specific type:
    try {
        throw Derived();
    } catch (const Base &base) {
        std::cerr << "Caught Base\n";  // this will print
    } catch (const Derived &derived) { // NOLINT
        std::cerr << "Caught Derived\n";
    }

    // the correct thing to do here is to flip the order of the catch blocks:
    try {
        throw Derived();
    } catch (const Derived &derived) {
        std::cerr << "Caught Derived\n"; // this will print
    } catch (const Base &base) {
        std::cerr << "Caught Base\n";
    }

    // stdlib classes and operators throw exceptions: operator new can throw std::bad_alloc if OOM, a failed dynamic_cast will throw std::bad_cast, etc.; there are 28 exception classes as of c++20
    // but they all derive from std::exception (<exception>), and we can use catch matching derived classes to check for all stdlib exceptions:
    try {
        std::string s;
        s.resize(
            std::numeric_limits<std::size_t>::
                max()); // triggers either std::length_error or allocation exception
    } catch (const std::length_error &exception) {
        // catches only this type of exception, lets all others derived from std::exception fall through
        std::cerr << "You ran out of memory!\n";
    } catch (const std::exception &exception) {
        std::cerr << "Standard exception: " << exception.what() << "\n";
        // .what() is a virtual function implemented by most derived classes of std::exception; its text is implementation defined so it cannot be used for comparisons
    }

    // nothing throws a std::exception directly and we shouldn't either; but we can throw the other standard exception classes if one fits our purposes (http://en.cppreference.com/w/cpp/error/exception)
    // std::runtime_error (<stdexcept>) is a common choice:
    try {
        throw std::runtime_error("Bad things happened");
    } catch (const std::exception &exception) {
        std::cerr << "Standard exception: " << exception.what() << "\n";
    }

    // we can derive our own classes from std::exception:
    StandardIntArray array2;

    try {
        int value { array2[5] };
    } catch (const StandardArrayException &exception) {
        std::cerr << "An array exception occurred (" << exception.what()
                  << ")\n";
    } catch (const std::exception &exception) {
        std::cerr << "Some other std::exception occurred (" << exception.what()
                  << ")\n";
    }

    // we could also derive from std::runtime_error which takes either a C-style string or a const std::string&
    // and we don't need to override what() because we just use std::runtime_error::what()
    try {
        int value { array2[5] };
    } catch (const RuntimeArrayException &exception) {
        std::cerr << "An array exception occurred (" << exception.what()
                  << ")\n";
    } catch (const std::exception &exception) {
        std::cerr << "Some other std::exception occurred (" << exception.what()
                  << ")\n";
    }

    // when an exception is thrown, the object actually being thrown is usually a temporary or local variable on the stack; but exception handling may unwind the stack and destroy all local variables
    // to keep the thrown object from being destroyed, the compiler makes a copy of the exception object to some unspecified memory outside of the call stack reserved for exception handling, guaranteeing that the object will exist until the exception is handled
    // this means that objects that are thrown must be copyable, even if the stack doesn't actually get unwound; but the object may get moved or the copy elided in reality
    NonCopyable::Derived d {};

    try {
        // throw d; // won't compile, d needs to be copyable
    } catch (const NonCopyable::Derived &derived) {
        std::cerr << "caught Derived\n";
    } catch (const NonCopyable::Base &base) {
        std::cerr << "caught Base\n";
    }

    // exception objects shouldn't keep pointers or references to stack allocated objects because the backing object may get deallocated during stack unwinding and leave the pointer/reference dangling

    return 0;
}