#include <iostream>

int main() {
    std::cout << "Enter an integer: ";
    int x {};
    std::cin >> x;
    if (x > 0)
        std::cout << "The value is positive\n";
    else if (x < 0)
        std::cout << "The value is negative\n";
    else
        std::cout << "The value is zero\n";

    if (x)
        std::cout << "x exists\n";
    else
        std::cout << "x does not exist\n";

    return 0;
}