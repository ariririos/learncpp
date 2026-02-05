#include <iostream>

int get_number() {
    std::cout << "Enter a number 0-9: ";
    int x {};
    std::cin >> x;
    return x;
}

bool is_prime(int x) { return x == 2 || x == 3 || x == 5 || x == 7; }

int main() {
    int x { get_number() };

    if (is_prime(x)) {
        std::cout << "Prime!\n";
    } else {
        std::cout << "Not prime!\n";
    }

    return 0;
}