#include <iostream>
#include <optional>

class Foo {
private:
    int m_x {};
    int m_y {};

public:
    Foo(int x, int y)
        : m_x { x }, m_y { y } { 
        std::cout << "Foo(" << x << ", " << y << ") constructed\n";
    }

    void print() const {
        std::cout << "Foo(" << m_x << ", " << m_y << ")\n"; // wrong because constructor does not initialize the private data members
    }
};

// members are initialized in the order they're defined in the class, *not* the order they're defined in the initializer list
class Bar {
private:
    int m_x {};
    int m_y {};
public:
    Bar(int x, int y)
        : m_y { std::max(x, y) }, m_x { m_y } // NOLINT
        // m_x will be initialized first,
        // with an uninitialized m_y
        {}

    void print() const {
        std::cout << "Foo(" << m_x << ", " << m_y << ")\n";
    }
};

// use a private constructor to enforce class invariants (at least until we get exceptions -- assert only catches issues in debug mode):
class Fraction {
private:
    int m_numerator { 0 };
    int m_denominator { 1 };

    Fraction(int numerator, int denominator)
        : m_numerator { numerator }, m_denominator { denominator }
        {}
public:
    friend std::optional<Fraction> create_fraction(int numerator, int denominator); // apparently allows a non-member function to access private members
};

std::optional<Fraction> create_fraction(int numerator, int denominator) {
    if (denominator == 0) return {};
    return Fraction { numerator, denominator };
}

int main() {
    Foo foo { 6, 7 };
    foo.print();

    Bar bar { 6, 7 };
    bar.print();

    auto f1 { create_fraction(0, 1) };
    if (f1) {
        std::cout << "Fraction created\n";
    }

    auto f2 { create_fraction(0, 0) };
    if (!f2) {
        std::cout << "Bad fraction\n";
    }
    return 0;
}