#include <iostream>
#include <optional>
#include <functional>
#include <string>
#define print_expr(x) { std::cout << #x << " = " << x << "\n"; }

std::optional<int> int_divide(int x, int y) {
    if (y == 0) {
        return {};
    }
    return x / y;
}

void print_id(std::optional<const int> id = std::nullopt) {
    if (id) {
        std::cout << "Your ID number is " << *id << ".\n";
    }
    else {
        std::cout << "Your ID number is unknown.\n";
    }
}

struct Employee {
    std::string name {};
    int id;
};

void print_employee_id(std::optional<std::reference_wrapper<Employee>> e = std::nullopt) {
    if (e) {
        std::cout << "Your ID number is " << e->get().id << ".\n";
    }
    else {
        std::cout << "Your ID number is unknown.\n";
    }
}

void print_employee_id_ptr(const Employee* e=nullptr) {
    if (e) {
        std::cout << "Your ID number is " << e->id << ".\n";
    }
    else {
        std::cout << "Your ID number is unknown.\n";
    }
}

void print_employee_id_overloaded() {
    std::cout << "Your ID number is unknown.\n";
}

void print_employee_id_overloaded(const Employee& e) {
    std::cout << "Your ID number is " << e.id << ".\n";
}

int main() {
    std::optional<int> result1 { int_divide(20, 5) };
    if (result1) {
        print_expr(*result1);
        print_expr(result1.value());
    }
    else {
        print_expr(result1.value_or(42));
    }

    std::optional<int> result2 { int_divide(5, 0) };
    if (result2) {
        print_expr(*result2);
        print_expr(result2.value());
    }
    else {
        print_expr(result2.value_or(42));
    }

    print_id();

    int user_id { 34 };
    print_id(user_id);

    print_id(92); // std::optional makes a copy of whatever's passed in so rvalues are fine

    print_employee_id();
    Employee e { "James", 34 };
    print_employee_id(e);
    // print_employee_id( { "Dave", 62} ); // won't compile, rvalues can't be converted to std::optional<std::reference_wrapper<Employee>>


    print_employee_id_ptr();
    print_employee_id_ptr(&e);
    // print_employee_id_ptr(&{"Dave", 62}); // won't compile, nonsense

    print_employee_id_overloaded();
    print_employee_id_overloaded(e);
    print_employee_id_overloaded( { "Dave", 62 }); // rvalues are fine

    return 0;
}