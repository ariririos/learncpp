#include <array>
#include <iostream>

int main() {
    constexpr std::array hello { 'h', 'e', 'l', 'l', 'o' };
    std::cout << hello[1] << "\n";

    return 0;
}