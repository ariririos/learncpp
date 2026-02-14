#include <iostream>

struct Date {
    int year {};
    int month {};
    int day {};

    void print() {
        std::cout << year << "/" << month << "/" << day;
    }

    void print(std::string_view prefix) { // function overloads are fine
        std::cout << prefix << year << "/" << month << "/" << day;
    }
};

struct Person {
    std::string name {};
    int age {};
    void kisses(const Person& person) {
        std::cout << name << " kisses " << person.name << "\n";
    }
};

struct Foo { // order of declarations doesn't matter *except* for undefined behavior (below)
    int z() { return m_data; }
    int x() { return y(); }
    int m_data { y() };
    int y() { return 5; }
};

struct Bad { // data members must not depend on other data members that haven't yet been declared
    int m_bad1 { m_data }; // undefined behavior, m_data not declared yet // NOLINT
    int m_bad2 { fcn() }; // undefined behavior, m_data will be accessed through fcn() but not declared yet
    int m_data { 5 };
    int fcn() { return m_data; }
};

int main() {
    Date today { 2020, 10, 14 };
    today.day = 16;
    today.print();
    std::cout << "\n";
    today.print("The date is: ");
    std::cout << "\n";

    Person joe { "Joe", 29 };
    Person kate { "Kate", 27 };
    joe.kisses(kate);

    Bad bad;
    std::cout << bad.m_bad1 << " " << bad.m_bad2 << " " << bad.m_data << "\n";

    return 0;
}