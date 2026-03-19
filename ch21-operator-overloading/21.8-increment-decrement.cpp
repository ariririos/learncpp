#include <iostream>

class Digit {
private:
    int m_digit {};

public:
    Digit(int digit = 0) : m_digit { digit } {}
    Digit &operator++();
    Digit &operator--();
    Digit operator++(int);
    Digit operator--(int);
    friend std::ostream &operator<<(std::ostream &out, const Digit &d);
};

// no parameter so this is prefix operator++
Digit &Digit::operator++() {
    if (m_digit == 9) {
        m_digit = 0; // wrap around
    } else {
        ++m_digit;
    }

    return *this;
}

// no parameter so this is prefix operator--
Digit &Digit::operator--() {
    if (m_digit == 0) {
        m_digit = 9; // wrap around
    } else {
        --m_digit;
    }

    return *this;
}

// int parameter so this is postfix operator++
Digit Digit::operator++(int) {
    Digit temp { *this };
    ++(*this);
    return temp;
}

// int parameter so this is postfix operator--
Digit Digit::operator--(int) {
    Digit temp { *this };
    --(*this);
    return temp;
}

std::ostream &operator<<(std::ostream &out, const Digit &d) {
    out << d.m_digit;
    return out;
}

int main() {
    Digit digit { 8 };

    // the prefix increment/decrement operators are overloaded normally:
    std::cout << digit;
    std::cout << ++digit;
    std::cout << ++digit;
    std::cout << --digit;
    std::cout << --digit;

    std::cout << "\n";
    // but for the postfix operators, the language standard says that to differentiate them from the prefix operators
    // they should have an int parameter

    Digit digit2 { 5 };

    std::cout << digit2;
    std::cout << ++digit2; // calls Digit::operator++();
    std::cout << digit2++; // calls Digit::operator++(int);
    std::cout << digit2;
    std::cout << --digit2; // calls Digit::operator--();
    std::cout << digit2--; // calls Digit::operator--(int);
    std::cout << digit2;

    // the postfix operators are implemented using a temporary variable because they need to return
    // the state of the variable before the operation

    return 0;
}