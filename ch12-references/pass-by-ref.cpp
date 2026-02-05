#include <iostream>
#include <string>

void print_value(std::string& value) {
    std::cout << value << "\n";
}

void print_addresses(int val, int& ref) {
    std::cout << "&val = " << &val << "\n";
    std::cout << "&ref = " << &ref << "\n";
}

void add_one_to_ref(int& ref) {
    ref++;
}

void print_int(int val) {
    std::cout << val << "\n";
}

void print_int_ref(const int& ref) {
    std::cout << ref << "\n";
}

struct S {
    double a;
    double b;
    double c;
};

void print_sv(std::string_view sv) {
    std::cout << sv << "\n";
}

void print_const_str(const std::string& str) {
    std::cout << str << "\n";
}

int main() {
    std::string x { "Hello world" };
    print_value(x); // no difference in how to call the function with a reference
    int y { 5 };
    std::cout << "&y = " << &y << "\n";
    print_addresses(y, y); // prints two different addresses, the second matching above
    add_one_to_ref(y);
    std::cout << y << "\n";
    const int z { 6 };
    // add_one_to_ref(z); // won't compile, needs const in function signature
    print_int(5);
    print_int(5.0); // temporary int copied
    print_int_ref(5.0); // temporary int bound
    print_int_ref(z);

    std::cout << "sizeof(z) = " << sizeof(z) << "\n";
    std::cout << "sizeof(S) = " << sizeof(S) << "\n";

    std::string_view sv { "Hello, again" };
    print_sv(x);
    print_const_str(x);
    print_sv(sv);
    // print_const_str(sv); // compile error without explicit cast

    return 0;
}