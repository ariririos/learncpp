#include <functional>
#include <iostream>
#include <limits>

int add(int x, int y) { return x + y; }
int subtract(int x, int y) { return x - y; }
int multiply(int x, int y) { return x * y; }
int divide(int x, int y) { return x / y; }

using ArithmeticFunction = std::function<int(int, int)>;

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

ArithmeticFunction get_arithmetic_function(char op) {
    switch (op) {
    case '+':
        return add;
    case '-':
        return subtract;
    case '*':
        return multiply;
    case '/':
        return divide;
    default:
        return nullptr;
    }
}

int main() { get_arithmetic_function(get_operation()); }
