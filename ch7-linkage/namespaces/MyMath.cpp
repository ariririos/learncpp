#include <iostream>

void print() { std::cout << "in global\n"; }

namespace MyMath {
    int add(int x, int y) { return x + y; }
    void print() { std::cout << "in namespace\n"; }
    void print_both() {
        print();
        ::print();
    }
} // namespace MyMath