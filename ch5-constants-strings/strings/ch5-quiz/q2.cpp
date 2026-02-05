// #include <cstdint> // for std::uint8_t
#include <iostream>

int main() {
    std::cout << "How old are you?\n";

    int age {};
    std::cin >> age;

    std::cout << "Allowed to drive a car in Texas: ";
    constexpr int driving_age = 16;

    if (age >= driving_age)
        std::cout << "Yes";
    else
        std::cout << "No";

    std::cout << ".\n";

    return 0;
}