#include <iostream>

void fizzbuzz(int x) {
    for (int i { 1 }; i <= x; i++) {
        bool output { false };
        if (i % 3 == 0) {
            std::cout << "fizz";
            output = true;
        }
        if (i % 5 == 0) {
            std::cout << "buzz";
            output = true;
        }
        if (i % 7 == 0) {
            std::cout << "pop";
            output = true;
        }
        if (!output) {
            std::cout << i;
        }
        std::cout << "\n";
    }
}

int main() { fizzbuzz(150); }