#include "../print.h"
#include <iostream>

struct Employee {
    int id {};
    int age {};
    double wage { 10000.0 };
};

std::ostream &operator<<(std::ostream &out, const Employee &e) {
    out << "id: " << e.id << " age: " << e.age << " wage: " << e.wage;
    return out;
}

int main() {
    Employee frank = { 1, 32, 60000.0 };
    Employee joe { 2, 28, 45000.0 };

    print(frank);
    print(joe);

    Employee dave {};
    print(dave);

    const Employee mike {};
    print(mike);
    // mike.age = 10; // not allowed, const

    Employee alice {
        .id { 10 }, // NOLINT
        // age is value initialized
        .wage { 30000 }, // NOLINT
        // won't compile if initializers not in the same order as declarations
    };

    print(alice);

    alice = { 20, 30, 40000.0 };

    print(alice);

    alice = {
        .id { 30 }, // NOLINT
        .age { 40 } // NOLINT
    }; // wage is value initialized

    print(alice);

    alice = { mike };

    print(alice);

    return 0;
}