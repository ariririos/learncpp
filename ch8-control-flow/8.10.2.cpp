#include <iostream>

int sum_to(int x) {
    int sum = 0;
    for (int i { 1 }; i <= x; i++) {
        sum += i;
    }

    return sum;
}

int main() {
    std::cout << sum_to(5) << "\n";

    return 0;
}