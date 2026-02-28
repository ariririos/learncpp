#include "../print.h"
#include <iostream>
#include <string>
#include <string_view>

struct Owner {
    std::string name {};
};

struct Viewer {
    std::string_view name {};
};

struct Company {
    struct Employee { // path is Company::Employee
        int id {};
        int age {};
        double wage {};
    };
    int num_employees {};
    Employee CEO {};
};

std::string get_name() {
    std::cout << "Enter a name: ";
    std::string name {};
    std::cin >> name;
    return name;
}

struct Foo {
    short a {};
    int b {};
    double c {};
};

struct Foo1 {
    short a {};
    int b {};
    short c {};
};

struct Foo2 {
    int b {};
    short a {};
    short c {};
};

int main() {
    Company my_company { 7, { 1, 32, 100000.0 } };

    std::cout << my_company.CEO.wage << "\n";

    // get_name() returns a temporary in these initializations
    Owner a {
        get_name()
    }; // temporary is used to initialize an owned value, makes a copy
    std::cout << "Owner's name is " << a.name << "\n";

    Viewer b {
        get_name() // NOLINT
    }; // temporary is used to initialize a viewer, then dropped at the end of the expression
    std::cout << "Viewer's name is " << b.name
              << "\n"; // dangling reference, undefined behavior

    // structs can have padding:
    print(sizeof(short));  // 2
    print(sizeof(int));    // 4
    print(sizeof(double)); // 8
    print(sizeof(Foo));    // 2 + 4 + 8 != 16

    // padding depends on declaration order:

    print(sizeof(Foo1)); // 12
    print(sizeof(Foo2)); // 8

    // the C++ compiler is not allowed to reorder members

    return 0;
}