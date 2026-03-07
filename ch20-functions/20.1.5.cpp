#include <functional>
#include <iostream>
#include <limits>

template <typename T> void handle_input(T &in) {
    std::cin >> in;
    if (!std::cin) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
}

int add(int x, int y) { return x + y; }
int subtract(int x, int y) { return x - y; }
int multiply(int x, int y) { return x * y; }
int divide(int x, int y) { return x / y; }

using ArithmeticFunction = std::function<int(int, int)>;

char get_operation() {
    char op {};

    do {
        std::cout << "Enter an operation (+, -, *, /): ";
        handle_input(op);
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

int get_number() {
    std::cout << "Enter a number: ";
    int num {};
    handle_input(num);
    return num;
}

int main() {
    int x { get_number() };
    ArithmeticFunction fn { get_arithmetic_function(get_operation()) };
    int y { get_number() };
    if (fn) {
        std::cout << "Result: " << fn(x, y) << "\n";
    } else {
        std::cout << "Invalid operation\n";
    }
    return 0;
}
