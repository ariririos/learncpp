#include <iostream>
#include <stdexcept>

class Fraction {
private:
    int m_numerator {};
    int m_denominator {};

public:
    Fraction(int numerator, int denominator)
        : m_numerator { numerator }, m_denominator { denominator } {
        if (m_denominator == 0) {
            throw std::runtime_error { "Invalid denominator" };
        }
    }
    friend std::ostream &operator<<(std::ostream &out, const Fraction &f) {
        std::cout << f.m_numerator << "/" << f.m_denominator;

        return out;
    }
};

int main() {
    int numerator {};
    std::cout << "Enter the numerator: ";
    std::cin >> numerator;

    int denominator {};
    std::cout << "Enter the denominator: ";
    std::cin >> denominator;

    try {
        Fraction f { numerator, denominator };
        std::cout << "You entered: " << f << "\n";
    } catch (const std::exception &ex) {
        std::cerr << ex.what() << "\n";
    }

    return 0;
}