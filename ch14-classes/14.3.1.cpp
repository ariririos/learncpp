#include <iostream>

struct IntPair {
    int int1 {};
    int int2 {};
    void print() {
        std::cout << "Pair(" << int1 << ", " << int2 << ")\n";
    }
};

int main() {
    IntPair p1 { 1, 2 };
    IntPair p2 { 3, 4 };

    std::cout << "p1: ";
    p1.print();

    std::cout << "p2: ";
    p2.print();

    return 0;
}