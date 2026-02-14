#include <iostream>

struct Pair {
    int m_x {};
    int m_y {};

    constexpr int greater() const { // can be run at either compile-time or runtime
        return (m_x > m_y ? m_x : m_y);
    }
};

class Pair2 {
private:
    int m_x {};
    int m_y {};
public:
    constexpr Pair2(int x, int y): m_x { x }, m_y { y } {}
    constexpr int greater() const { return (m_x > m_y ? m_x : m_y); }
    constexpr void reset() {
        m_x = m_y = 0; // non-const member function can change members
    }
    constexpr const int& get_x() const { return m_x; }
    // ...
    constexpr const int* const get_x_ptr() const { return &m_x; }
};

constexpr int init() {
    Pair2 p { 5, 6 }; // requires a constexpr constructor despite not being marked constexpr
    return p.greater(); // requires greater() to be a constexpr member function
}

constexpr Pair2 zero() {
    Pair2 p { 1, 2 }; // p is non-const
    p.reset(); // calling non-const member function on non-const object is fine
    return p;
}

int main() {
    constexpr Pair p { 5, 6 };
    std::cout << p.greater() << "\n";

    constexpr int g { p.greater() }; // this requires p to be made constexpr, since this must evaluate at compile-time
    std::cout << g << "\n";

    // if Pair had private data members or a constructor, it would become a non-aggregate, and we get an error about Pair not being a "literal type"
    // "literal type" == any type where it might be possible to create an object within a constant expression
    // includes:
    // scalar types (types holding a single value, such as fundamental types and pointers)
    // reference types
    // most aggregates
    // classes with a constexpr constructor

    constexpr Pair p2 { 5, 6 }; // constexpr constructor makes this fine, despite the private members
    std::cout << p2.greater() << "\n";
    
    constexpr int g2 { p2.greater() }; // also fine, constexpr member function
    std::cout << g2 << "\n";

    constexpr int g3 { init() }; // requires init() to be evaluated at compile time (see above)
    std::cout << g3 << "\n";

    // in c++11, non-static constexpr member functions are implicitly const (except constructors)
    // but as of c++14, this is no longer true and you must explicitly mark constexpr member functions const

    Pair2 p4 { 3, 4 };
    p4.reset(); // calling non-const member function on non-const object is fine
    std::cout << p4.get_x() << "\n"; // 0

    Pair2 p5 { zero() }; // zero() is evaluated at runtime
    p5.reset(); // calling non-const member function on non-const object is fine
    std::cout << p5.get_x() << "\n"; // 0

    constexpr Pair2 p6 { zero() }; // zero() is evaluated at compile-time
    // this is fine even though zero() returns a non-const object: constexpr can use non-const objects and even return them, as long as they're a constant expression
    // p6.reset(); // not allowed: non-const member function call on const object
    std::cout << p6.get_x() << "\n"; // 0

    return 0;
}