// compiler usually needs to see the full definition of the class in order for the type to be used, a forward declaration is typically insufficient
#include "./15.2-Date.h"
#include <iostream>

Date::Date(int year, int month, int day)
    : m_year { year }
    , m_month { month }
    , m_day { day }
{}

void Date::print() const
{
    std::cout << "Date(" << m_year << ", " << m_month << ", " << m_day << ")\n";
}

int main() {
    const Date d { 2025, 10, 14 };
    d.print();

    return 0;
}