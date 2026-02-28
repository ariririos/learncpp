#include <iostream>

void print_string_reverse(const char str[]) {
    const char *end { str };
    // to avoid using strlen, walk the string looking for the \0
    while (*end != '\0') {
        end++;
    }

    // a for loop here creates an off-by-one error because the condition is evaluated before the next iteration regardless of whether end is prefix or postfix decremented
    while (end-- != str) {
        std::cout << *end;
    }
    std::cout << "\n";
}

int main() {
    print_string_reverse("Hello, world!");

    return 0;
}