#include <iostream>
#include <string>

struct Fraction {
    int numerator { 0 };
    int denominator { 1 };
};

void print_fraction_value(const Fraction &f) {
    std::cout << f.numerator / f.denominator << "\n"; // NOLINT
}

class Employee {
    int m_id {};
    int m_age {};
    double m_wage {};
};

class Date {
public:
    int m_day {};
    int m_month {};
    int m_year {};
};

void print_date(const Date& date) {
    std::cout << date.m_day << "/" << date.m_month << "/" << date.m_year;
}

int main() {
    Fraction f { 5, 0 };     // we can set denominator to zero if we want
    // print_fraction_value(f); // and cause a floating point exception

    Date date { 4, 10, 21 };
    print_date(date);

    return 0;
}