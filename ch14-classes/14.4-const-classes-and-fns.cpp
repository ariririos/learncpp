#include <iostream>

struct Date {
    int year {};
    int month {};
    int day {};
    void increment_day() {
        ++day;
    }
    void print() {
        std::cout << "non-const: " << year << "/" << month << "/" << day << "\n";
    }
    void print() const { // could also have named it differently but `const` is still required either way
        std::cout << "const: " << year << "/" << month << "/" << day << "\n";
        // ++day; // not allowed
    }
};

int main() {
    constexpr Date today { 2020, 10, 14 };

    // today.year = 2012; // won't compile
    // today.increment_day(); // won't compile
    // today.print(); // can't call non-const member function
    today.print(); // fine, can call const-qualified member function (the second overload)

    Date tomorrow { today };
    tomorrow.increment_day(); // fine
    tomorrow.print(); // calls the non-const version

    return 0;
}