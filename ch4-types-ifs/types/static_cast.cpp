#include <iostream>

// void print(int x) { std::cout << x << "\n"; }

int main() {
    // print(5.5);
    // print(static_cast<int>(5.5));

    std::cout << "Enter a single character: ";
    char ch {};
    std::cin >> ch;
    int c { ch };
    std::cout << "You entered '" << ch << "', which has ASCII code " << c
              << ".\n";

    return 0;
}