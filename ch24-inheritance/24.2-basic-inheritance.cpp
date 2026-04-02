#include <iostream>

class Person {
    // everything public for simplicity
public:
    std::string m_name {};
    int m_age {};

    Person(std::string_view name = "", int age = 0)
        : m_name { name }, m_age { age } {}

    const std::string &get_name() const { return m_name; }
    int get_age() const { return m_age; }
};

// this is "public inheritance"
class BaseballPlayer : public Person {
public:
    double m_batting_average {};
    int m_home_runs {};

    BaseballPlayer(double batting_average = 0.0, int home_runs = 0)
        : m_batting_average { batting_average }, m_home_runs { home_runs } {}
};

class Employee : public Person {
public:
    double m_hourly_salary {};
    long m_employee_id {};

    Employee(double hourly_salary = 0.0, long employee_id = 0)
        : m_hourly_salary { hourly_salary }, m_employee_id { employee_id } {}

    void print_name_and_salary() const {
        std::cout << m_name << ": " << m_hourly_salary << "\n";
    }
};

class Supervisor : public Employee {
public:
    long m_oversees_ids[5] {};
};

int main() {
    // inheritance in c++ takes place between classes -- one is called the parent class/base class/superclass, and the other is the child class/derived class/subclass
    // classes can be both parents and children

    // child classes inherit both behaviors/member functions and properties/member variables from their parent, subject to some access restrictions, which become members of the derived class; child classes are full-fledged classes and can have their own members specific to them

    // given our Person class above, giving BaseballPlayer the same functionality as Person could be achieved by code duplication, or by making Person a member of BaseballPlayer, but neither is ideal; inheritance solves this problem
    BaseballPlayer joe {};
    joe.m_name = "Joe";
    std::cout << joe.get_name() << "\n";

    // Employee also derives from Person but BaseballPlayer and Employee have no direct relationship
    Employee frank { 20.25, 12345 };
    frank.m_name = "Frank";
    frank.print_name_and_salary();

    // inheritance from a class derived from another class is no different; Supervisor derives from Employee which derives from Person
    Supervisor hank {};

    return 0;
}