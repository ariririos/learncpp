#include <iostream>

class Date {
private:
    int m_year { 2020 };
    int m_month { 10 };
    int m_day { 14 };

public:
    void print() const {
        std::cout << m_year << "/" << m_month << "/" << m_day << "\n";
    }

    int get_year() const { return m_year; }
    void set_year(int year) { m_year = year; }

    int get_month() const { return m_month; }
    void set_month(int month) { m_month = month; }

    int get_day() const { return m_day; }
    void set_day(int day) { m_day = day; }
};

int main() {
    Date d {};
    d.set_year(2021);

    std::cout << "The year is: " << d.get_year() << "\n";

    return 0;
}