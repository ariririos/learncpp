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

int main() { get_operation(); }