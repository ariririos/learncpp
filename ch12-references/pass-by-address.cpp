#include <iostream>
#include <string>
#include <cassert>
#define print_expr(x) { std::cout << #x << " = " << x << "\n"; }

void print_by_value(std::string val) {
    std::cout << val << "\n";
}

void print_by_ref(const std::string& ref) {
    std::cout << ref << "\n";
}

void print_by_address(const std::string* ptr) {
    std::cout << *ptr << "\n";
}

void change_val(int* ptr) {
    *ptr = 6;
}

void dont_change_val(const int* ptr) {
    // *ptr = 6; // expression must be a modifiable lvalue
}

void print_int(int* ptr) {
    std::cout << *ptr << "\n";
}

void print_int_checked(int* ptr) {
    // assert(ptr); // this aborts early in debug mode

    if (!ptr) { // and this does the same in prod
        return;
    }
    std::cout << *ptr << "\n";
}

void print_id_num(const int *id=nullptr) {
    if (id) {
        std::cout << "Your ID number is " << *id << ".\n";
    }
    else {
        std::cout << "Your ID number is not known.\n";
    }
}

void print_id_num2() {
    std::cout << "Your ID is not known.\n";
}

void print_id_num2(int id) {
    std::cout << "Your ID is " << id << ".\n";
}

void dont_nullify(int* ptr2) {
    ptr2 = nullptr;
}

void nullify(int*& refptr) {
    refptr = nullptr;
}

int main() {
    std::string str { "Hello world" };
    
    print_by_value(str);
    print_by_ref(str);
    print_by_address(&str);

    int a { 5 };
    print_expr(a);
    change_val(&a);
    print_expr(a);

    print_int(&a);

    int* b {};
    // print_int(b); // null pointer dereference, will segfault
    print_expr(b);
    std::cout << "This will print nothing if b is null: ";
    print_int_checked(b);
    std::cout << "\n";
    std::cout << "This should print nothing as well: ";
    print_int_checked(nullptr);
    std::cout << "\n";
    std::cout << "But this will print a: ";
    print_int_checked(&a);

    print_id_num();

    int user_id { 34 };
    print_id_num(&user_id);

    print_id_num2();
    print_id_num2(user_id);

    int* c { &user_id };
    print_expr(c);
    dont_nullify(c);
    print_expr(c);
    nullify(c);
    print_expr(c);

    return 0;
}