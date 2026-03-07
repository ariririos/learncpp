#include <iostream>

int sum_digits(int num) {
    if (num < 10) {
        return num;
    }
    return sum_digits(num / 10) + num % 10;
}

int main() {
    std::cout << sum_digits(93427) << "\n";

    return 0;
}