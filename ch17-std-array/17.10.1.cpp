#include <iostream>

void print_string(const char str[]) {
    for (; *str != '\0'; str++) {
        std::cout << *str;
    }
    std::cout << "\n";
}

int main() {
    print_string("Hello, world!");

    return 0;
}