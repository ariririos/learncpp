#include <iostream>

int factorial(int num) {
    if (num == 0) {
        return 1;
    }
    return num * factorial(num - 1);
}
int main() {
    for (int i { 0 }; i < 8; i++) {
        std::cout << i << "! = " << factorial(i) << "\n";
    }

    return 0;
}