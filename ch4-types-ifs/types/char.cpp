#include <iostream>

int main() {
    std::cout << "Enter a character: ";

    char ch {};
    std::cin >> ch;
    std::cout << "You entered: " << ch << "\n";

    std::cin >> ch;
    std::cout << "You entered: " << ch << "\n";

    std::cout << "Enter a character with some whitespace: ";
    std::cin.get(ch);
    std::cout << "You entered: " << ch << "\n";

    std::cin.get(ch);
    std::cout << "You entered: " << ch << "\n";

    return 0;
}