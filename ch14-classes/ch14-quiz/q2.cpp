#include <iostream>

class Fraction {
private:
    int m_numerator { 0 };
    int m_denominator { 1 };
public:
    // explicit here ensures that nonsense like f1.multiply(true) will be prevented
    explicit Fraction(int numerator = 0, int denominator = 1)
        : m_numerator { numerator }, m_denominator { denominator }
    {}
    void get_fraction() {
        std::cout << "Enter a value for numerator: ";
        std::cin >> m_numerator;
        std::cout << "Enter a value for denominator: ";
        std::cin >> m_denominator;
        std::cout << "\n";
    }
    Fraction multiply(const Fraction& f2) {
        return Fraction { m_numerator * f2.m_numerator, m_denominator * f2.m_denominator };
    }

    void print_fraction() const {
        std::cout << m_numerator << "/" << m_denominator << "\n";
    }
};

int main() {
    Fraction f1 {};
    f1.get_fraction();

    Fraction f2 {};
    f2.get_fraction();

    std::cout << "Your fractions multiplied together: ";
    f1.multiply(f2).print_fraction();

    return 0;
}