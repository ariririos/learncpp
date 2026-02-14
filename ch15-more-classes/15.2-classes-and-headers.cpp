#include <iostream>

class Date {
private:
    int m_year {};
    int m_month {};
    int m_day {};
public:
    Date(int year, int month, int day);
    void print() const;
    int get_year() const { return m_year; }
    int get_month() const { return m_month; }
    int get_day() const { return m_day; }
};

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
    const Date d { 2015, 10, 14 };
    d.print();

    return 0;
}