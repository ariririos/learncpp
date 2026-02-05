#include <iostream>

int main() {
    std::cout << "Enter a number: ";
    int x {};
    std::cin >> x;
    std::cout << "You wrote: " << x << "\n";

    std::cout << "Enter two numbers separated by a space: ";
    int y {};
    int z {};
    std::cin >> y >> z;
    std::cout << "You wrote: " << y << " and " << z << "\n";
    return 0;
}