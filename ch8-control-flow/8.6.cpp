#include <iostream>
int calculate(int x, int y, char op) {
    switch (op) {
    case '+':
        return x + y;
    case '-':
        return x - y;
    case '*':
        return x * y;
    case '/':
        return x / y;
    case '%':
        return x % y;
        break;
    default:
        std::cout << "Unsupported operation\n";
        return 0;
    }
}

int main() {
    std::cout << "(3, 4, +) = " << calculate(3, 4, '+') << "\n";
    std::cout << "(3, 4, -) = " << calculate(3, 4, '-') << "\n";
    std::cout << "(3, 4, *) = " << calculate(3, 4, '*') << "\n";
    std::cout << "(3, 4, /) = " << calculate(3, 4, '/') << "\n";
    std::cout << "(3, 4, %) = " << calculate(3, 4, '%') << "\n";
    return 0;
}