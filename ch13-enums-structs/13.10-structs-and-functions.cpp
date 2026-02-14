#include "../print.cpp"

struct Employee {
    int id {};
    int age {};
    double wage {};
};

void print_employee(const Employee& employee){
    std::cout << "ID:\t" << employee.id << "\n";
    std::cout << "Age:\t" << employee.age << "\n";
    std::cout << "Wage:\t" << employee.wage << "\n";
}

struct Point3D {
    double x { 0.0 };
    double y { 0.0 };
    double z { 0.0 };
};

Point3D get_zero_point() {
    // all of these do the same thing:

    // Point3D temp { 0.0, 0.0, 0.0 };
    // return temp;
    // return Point3D { 0.0, 0.0, 0.0 };
    // return { 0.0, 0.0, 0.0 };
    return {}; // works because Point3D will be value-initialized to all zeroes
}

int main() {
    Employee joe { 14, 32, 24.15 };
    Employee frank { 15, 28, 18.27 };

    print_employee(joe);
    std::cout << "\n";
    print_employee(frank);
    std::cout << "\n";
    print_employee( Employee { 16, 40, 35.29 });
    std::cout << "\n";
    print_employee({ 17, 50, 65.10 }); // type deduced from parameter, implicit conversion
    // temporary objects only work in rvalue context (pass by value, pass by const ref)
    // won't work with pass by non-const ref and pass by address

    std::cout << "\n";

    Point3D zero { get_zero_point() };
    if (zero.x == 0.0 && zero.y == 0.0 && zero.z == 0.0) {
        std::cout << "The point is zero\n";
    }
    else {
        std::cout << "The point is non-zero\n";
    }

    return 0;
}