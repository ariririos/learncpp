#include <iostream>

int add(int x, int y) {
    return x + y;
}

double add(double x, double y) {
    return x + y;
}

void foo(int) {}
void foo(double) {}

void print(char, int) {}
void print(char, double) {}
void print(char, float) {}

void foo(char) = delete;

void print_int(int x) {
    std::cout << x << "\n";
}

template <typename T>
void print_int(T x) = delete;

void print_default(int num = 0) {
    std::cout << num;
}

int main() {
    // foo(5L); - not allowed, ambiguous
    print('x', 'a'); // calls print(char, int) via promotion
    // foo('a'); // not allowed, deleted
    print_int(7);
    // print_int('a'); // not allowed, resolves to deleted template
    print_default();
    std::cout << "3 + 4 = " << add(3, 4) << "\n";
    std::cout << "3.5 + 3.5 = " << add(3.5, 3.5) << "\n";
    return 0;
} 