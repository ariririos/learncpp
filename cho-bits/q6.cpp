#include <cstdint>
#include <iostream>

void calc_bit(int number, int pow) {
    int bit = (number / pow) % 2;
    std::cout << bit;
}

int main() {
    std::cout << "Enter a number between 0 and 255: ";
    int number {};
    std::cin >> number;
    calc_bit(number, 128);
    calc_bit(number, 64);
    calc_bit(number, 32);
    calc_bit(number, 16);
    std::cout << " ";
    calc_bit(number, 8);
    calc_bit(number, 4);
    calc_bit(number, 2);
    calc_bit(number, 1);

    std::cout << "\n";
    return 0;
}