#include <iostream>

struct Fraction {
    int numerator { 0 };
    int denominator { 1 };
};

Fraction get_fraction() {
    Fraction frac {};

    std::cout << "Enter a value for the numerator: ";
    std::cin >> frac.numerator;

    std::cout << "Enter a value for the denominator: ";
    std::cin >> frac.denominator;

    return frac;
}

constexpr Fraction multiply_fractions(const Fraction& frac1, const Fraction& frac2) {
    return { frac1.numerator * frac2.numerator, frac1.denominator * frac2.denominator };
}

void print_fraction(const Fraction& frac) {
    std::cout << frac.numerator << "/" << frac.denominator;
}

int main() {
    Fraction frac1 { get_fraction() };
    std::cout << "\n";
    Fraction frac2 { get_fraction() };

    std::cout << "Your fractions multiplied together: ";
    print_fraction(multiply_fractions(frac1, frac2));
    std::cout << "\n";

    return 0;
}