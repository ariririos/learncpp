#include <iostream>

class Fraction {
private:
    int m_numerator { 0 };
    int m_denominator { 1 };

public:
    Fraction(int numerator = 0, int denominator = 1)
        : m_numerator { numerator }, m_denominator { denominator } {
        std::cout << "Fraction(" << m_numerator << ", " << m_denominator
                  << ") constructed\n";
    }
    // copy constructor:
    Fraction(const Fraction &fraction) // this function signature with the
                                       // reference is required

        // we can access private members here fine since access controls are
        // per-class not per-object
        : m_numerator { fraction.m_numerator },
          m_denominator { fraction.m_denominator } {
        std::cout << "Fraction(" << m_numerator << ", " << m_denominator
                  << ") copied\n";
        // copy constructors can be optimized out and shouldn't have any side
        // effects other than copying
    }
    // prefer the implicit copy constructor (except when dynamically allocating
    // memory - 21.13)
    // we could explicitly request default copy constructor like this:
    // Fraction(const Fraction& fraction) = default;
    // we can *prevent* copies like this:
    // Fraction(const Fraction& fraction) = delete;
    void print() const {
        std::cout << "Fraction(" << m_numerator << ", " << m_denominator
                  << ")\n";
    }

    // rule of five: if a class requires a user-defined copy constructor, destructor, copy assignment operator, move constructor, or move assignment operator, it probably requires all five
};

// pass-by-value for objects makes a copy
void print_fraction(Fraction f) { f.print(); }

Fraction generate_fraction(int n, int d) {
    Fraction f { n, d };
    return f;
}

int main() {
    Fraction f { 5, 3 };
    Fraction f_copy { f }; // the copy constructor is used here
    // if it hadn't been provided, an implicit copy constructor that printed
    // nothing would've done memberwise initialization

    f.print();
    f_copy.print();

    print_fraction(f); // this passes by value and thus makes a copy

    // if no copy constructors are optimized out:
    Fraction f2 { generate_fraction(1, 2) }; // this copies Fraction twice, once to get it out of generate_fraction and into main, and again to get it into f2
    print_fraction(f2); // and this copies it again to get it into print_fraction

    return 0;
}