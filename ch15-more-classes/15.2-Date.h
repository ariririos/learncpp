#ifndef DATE_H
#define DATE_H
#include <iostream>

class Date {
private:
    int m_year {};
    int m_month {};
    int m_day {};

public:
    Date(int year, int month, int day);
    void print() const;
    void print_inline() const;
    int get_year() const { return m_year; }
    int get_month() const { return m_month; }
    int get_day() const { return m_day; }
    // if any of these functions had default arguments, they should go here in the class definition
};

inline void Date::print_inline() const { // functions defined outside of the class definition in header files should be made inline to avoid ODR violations. functions defined inside the class definition are implicitly inline
    std::cout << "Date(" << m_year << ", " << m_month << ", " << m_day << ")\n";
}

// putting all function definitions in the header file means any change to them will require recompilation of every file #include-ing it

#endif