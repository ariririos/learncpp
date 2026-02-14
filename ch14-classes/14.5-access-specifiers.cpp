#include <iostream>

// all struct members and functions are public by default
struct Date {
    int year {};
    int month {};
    int day {};

    void print() const {
        std::cout << year << "/" << month << "/" << day << "\n";
    }
};

// class members and functions are private by default
class PrivDate {
    int m_year {};
    int m_month {};
    int m_day {};

    void print() const {
        std::cout << m_year << "/" << m_month << "/" << m_day << "\n";
    }
};

class NewDate {
public:
    void print() const {
        std::cout << m_year << "/" << m_month << "/" << m_day << "\n"; // accessing private members inside class definition is fine
    }
private:
    int m_year { 2020 };
    int m_month { 10 };
    int m_day { 14 };
};

// access specifiers are per-class not per-object
class Person {
private:
    std::string m_name {};
public:
    void kisses(const Person& p) const {
        std::cout << m_name << " kisses " << p.m_name << "\n"; // ... meaning we can access private members of another instance of the same class
    }
    void set_name(std::string_view name) {
        m_name = name;
    }
};

// main is part of "the public"
int main() {
    Date today { 2020, 10, 14 };
    today.day = 16; // fine, public data member
    today.print(); // fine, public member function

    // PrivDate tomorrow { 2020, 10, 14 }; // won't compile, private non-static data members conflict with aggregate initialization
    // tomorrow.m_day = 14; // won't compile, inaccessible
    // tomorrow.print(); // won't compile, inaccessible

    NewDate today2; // can't aggregate-initialize but private data members will be default-initialized
    today2.print();

    Person joe;
    joe.set_name("Joe");

    Person kate;
    kate.set_name("Kate");

    joe.kisses(kate);

    return 0;
}