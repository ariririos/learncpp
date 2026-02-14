#include <iostream>

// to access a private static member, we could use a regular member function on
// the class, but that would require instantiating an object to be able to call
// the function static member functions provide a method to access those static
// data members without a specific object:
class Something {
private:
    static inline int s_x { 1 };
    int m_x { 2 };

public:
    int get_x() { return m_x; }
    static int get_value() {
        // there's no `this` pointer in a static member function
        // and you can't access non-static data members or functions
        // so these three lines fail to compile:
        // this;
        // m_x;
        // get_x();
        return s_x;
    }
    static int get_next_value();
};

int Something::get_next_value() { // no static keyword if declaring static
                                  // member function outside of the class
                                  // definition
    return ++s_x;
} // if this was in a header file it should be marked `inline` to prevent ODR
  // violations; member functions defined inside the class definition are
  // implicitly inline

// classes with purely static members are basically global variables in a
// namespace:
// - you can't have multiple copies without copying the code
// - anyone can change the state of the class
// prefer a global instance of a class with normal members
// the difference with namespaces is access controls

// static constructors are not a thing in c++
// if you need code to instantiate static members, one possibility is using a
// function to create an object and return it, then copy it into the static data
// member:

struct Chars {
    char first {};
    char second {};
    char third {};
    char fourth {};
    char fifth {};
};

class MyClass {
private:
    static Chars generate() {
        Chars c {};
        // pretend this couldn't just be a list initialization directly in the
        // member declaration below
        c.first = 'a';
        c.second = 'e';
        c.third = 'i';
        c.fourth = 'o';
        c.fifth = 'u';
        return c;
    }

public:
    static inline Chars s_my_chars { generate() }; // could also be a lambda
};

int main() {
    std::cout << Something::get_value() << "\n";
    std::cout << Something::get_next_value() << "\n";
    std::cout << MyClass::s_my_chars.third << "\n";
}