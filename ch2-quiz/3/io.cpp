#include "io.h"
#include <iostream>

int read_number() {
    int x {};
    std::cout << "Enter an integer: ";
    std::cin >> x;
    return x;
}

void write_answer(int ans) { std::cout << "The sum is " << ans << "\n"; }