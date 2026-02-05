#include <iostream>

double get_value() {
    std::cout << "Enter a double value: ";
    double x {};
    std::cin >> x;
    return x;
}

char get_operation() {
    std::cout << "Enter +, -, *, or /: ";
    char o {};
    std::cin >> o;
    return o;
}

void print_result(double x, double y, char op) {
    double result {};
    if (op == '+') {
        result = x + y;
    } else if (op == '-') {
        result = x - y;
    } else if (op == '*') {
        result = x * y;
    } else if (op == '/') {
        result = x / y;
    } else {
        std::cout << "error\n";
        return;
    }
    std::cout << x << " " << op << " " << y << " is " << result << "\n";
}

int main() {
    double x { get_value() };
    double y { get_value() };
    char op { get_operation() };

    print_result(x, y, op);

    return 0;
}