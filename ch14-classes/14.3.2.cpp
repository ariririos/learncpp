#include <iostream>

struct IntPair {
    int int1 {};
    int int2 {};
    void print() {
        std::cout << "Pair(" << int1 << ", " << int2 << ")\n";
    }
    bool is_equal(const IntPair& other) {
        return (int1 == other.int1) && (int2 == other.int2);
    }
};

int main() {
    IntPair p1 { 1, 2 };
    IntPair p2 { 3, 4 };

    std::cout << "p1: ";
    p1.print();

    std::cout << "p2: ";
    p2.print();

    std::cout << "p1 and p1 " << (p1.is_equal(p1) ? "are equal" : "are not equal") << "\n";
    std::cout << "p1 and p2 " << (p1.is_equal(p2) ? "are equal" : "are not equal") << "\n";

    return 0;
}