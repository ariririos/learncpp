#include <iostream>
#include <string>
#define print_expr(x) { std::cout << #x << " = " << x << "\n"; }

const std::string& get_program_name() {
    // static const std::string program_name { "Calculator" }; // fine

    static const std::string program_name { "Calculator" }; // this version causes dangling reference

    return program_name; // NOLINT
}

const int& return_by_const_ref(const int& ref) {
    return ref;
}

const std::string& first_alphabetical(const std::string& a, const std::string& b) {
    return (a < b) ? a : b;
}

std::string get_hello() {
    return "Hello";
}

int& max(int& x, int& y) {
    return (x > y) ? x : y;
}

int* return_dangling_pointer() {
    int s = 5;
    return &s; // NOLINT
}

int main() {
    // -Wreturn-local-addr
    std::cout << "This program is named " << get_program_name() << "\n"; 

    // -Wdangling-reference
    // int n = 1;
    // const int& r = std::max(n - 1, n + 1);

    // fine
    const int& ref1 { 5 };
    std::cout << ref1 << "\n";

    // -Wdangling-reference
    const int& ref2 { return_by_const_ref(5) };
    // std::cout << ref2 << "\n";

    // fine
    std::string hello { "Hello" };
    std::string world { "World" };

    std::cout << first_alphabetical(hello, world) << "\n";

    const std::string s { get_hello() };
    std::cout << s << "\n";

    int a { 5 };
    int b { 6 };

    max(a, b) = 7;
    print_expr(a);
    print_expr(b);

    // -Wreturn-local-addr
    print_expr(return_dangling_pointer());

    return 0;
}