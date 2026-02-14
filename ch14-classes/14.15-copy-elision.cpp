#include <iostream>

class Foo {
public:
    // Default constructor
    Foo() {
        std::cout << "Foo()\n";
    }
    // Regular constructor
    Foo(int x) {
        std::cout << "Foo(int x = " << x << ")\n";
    }
    // Copy constructor
    Foo(const Foo& x) {
        std::cout << "Foo(const Foo&)\n";
    }
};

class Something {
    int m_x {};
public:
    Something(int x)
        : m_x { x }
    {
        std::cout << "Something(int x);\n";
    }
    Something(const Something& s)
        : m_x { s.m_x }
    {
        std::cout << "Something(const Something& s)\n";
    }

    void print() const { std::cout << "Something(" << m_x << ")\n"; }
};

class Something2 {
public:
    Something2() = default;
    Something2(const Something2&) {
        std::cout << "Something2(const Something2&)\n";
    }
};

Something2 rvo() {
    return Something2 {}; // calls Something2() and the copy constructor
}

Something2 nrvo() {
    Something2 s {}; // calls Something()
    return s; // calls copy constructor
}

int main() {
    // reminder of the types of initialization for fundamental types:
    int a; // no initializer (default initialzation)
    int b = 5; // copy initialization
    int c ( 6 ); // direct initialization
    // c++11 and after:
    int d { 7 }; // direct list initialization
    int e = { 8 }; // copy list initialization
    int f {}; // value initialization

    // all can be used with classes:

    // Foo() default constructor:
    Foo f1; // default initialization
    Foo f2 {}; // value initialization (preferred)

    // Foo(int) regular constructor:
    Foo f3 = 3; // copy-initialization (non-explicit constructors only)
    Foo f4 ( 4 ); // direct-initialization
    Foo f5 { 5 }; // direct-list initialization (preferred)
    Foo f6 = { 6 }; // copy list initialization (non-explicit constructors only)

    // Foo(const Foo&) copy constructor:
    Foo f7 = f3; // copy initialization
    Foo f8 ( f3 ); // direct initialization
    Foo f9 { f3 }; // direct-list initialization (preferred)
    Foo f10 = { f3 }; // copy list initialization

    // copy initialization, direct initialization, and list initialization are basically the same thing -- initialization of an object
    // implicit conversions of arguments are allowed
    // for non-class types the implicit conversion rules are used to determine whether an implicit conversion exists

    // list initialization disallows narrowing conversions
    // copy initialization only considers non-explicit constructors/conversions (14.16)
    // list initialization matches list constructors over other matching constructors (16.2)
    // copy initialization is not allowed in constructor member initializer lists

    // Copy elision:
    Something s { Something { 5} }; // compiler is likely to omit this copy, exception to "as-if" rule
    s.print();

    std::cout << "Initializing s1\n";
    Something2 s1 { rvo() }; // calls copy something

    std::cout << "Initializing s2\n";
    Something2 s2 { nrvo() }; // calls copy constructor

    // without copy elision the above four lines produce four calls to the copy constructor, two each for copying the return value of a function back to main, two for initializing variables

    // but it seems gcc elides all four copies

    // as of c++17 the copy constructors for when rvo() returns and initializing s1 are required to be elided
    // but the two for nrvo() returning and initializing s2 are not
    // when copy elision is optional, the copy constructor must be accessible (e.g. not deleted), even if its call is elided
    // but when copy elision is mandatory, an accessible copy constructor does not need to be available

    // (if optional copy elision isn't performed, it may still be moved by move semantics = 16.5)
    
    return 0;
}