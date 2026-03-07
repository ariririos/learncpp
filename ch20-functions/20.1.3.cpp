#include <functional>
#include <iostream>
#include <limits>

char get_operation() {
    char op {};

    do {
        std::cout << "Enter an operation (+, -, *, /): ";

        std::cin >> op;
        if (!std::cin) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    } while (op != '+' && op != '-' && op != '*' && op != '/');
    return op;
}

int add(int x, int y) { return x + y; }
int subtract(int x, int y) { return x - y; }
int multiply(int x, int y) { return x * y; }
int divide(int x, int y) { return x / y; }

using ArithmeticFunction = std::function<int(int, int)>;

int main() { get_operation(); }
