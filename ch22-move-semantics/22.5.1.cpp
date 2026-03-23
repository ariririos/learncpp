#include <iostream>
#include <memory>

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

void print_fraction(const Fraction *ptr) {
    if (ptr)
        std::cout << *ptr << "\n";
    else
        std::cout << "No fraction\n";
}

int main() {
    auto ptr { std::make_unique<Fraction>(3, 5) };

    print_fraction(ptr.get());

    return 0;
}