#include <iostream>
#include <limits>

void print_binary(unsigned int num) {
    if (num > 1) { // handles zero
        print_binary(num / 2);
    }
    unsigned int remainder { num % 2 };
    std::cout << remainder;
}

unsigned int get_number() {
    unsigned int num {};
    while (true) {
        std::cout << "Enter an integer: ";
        std::cin >> num;
        if (!std::cin) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }
        return num;
    };
}

int main() {
    unsigned int num { get_number() };
    print_binary(num);
    std::cout << "\n";

    return 0;
}