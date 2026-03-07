#include <iostream>
#include <limits>

void print_binary(int num) {
    if (num == 0) {
        return;
    }
    int remainder { num % 2 };
    print_binary(num / 2);
    std::cout << remainder;
}

int get_number() {
    int num {};
    do {
        std::cout << "Enter a positive integer: ";
        std::cin >> num;
        if (!std::cin) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    } while (num < 0);
    return num;
}

int main() {
    int num { get_number() };
    print_binary(num);
    std::cout << "\n";

    return 0;
}