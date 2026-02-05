#include <bitset>
#include <iostream>

// "rotl" stands for "rotate left"
std::bitset<4> rotl(std::bitset<4> bits) {
    // bitwise `or` works here because bits right shifted by 3 will result in
    // 000{x} where x is the leftmost bit so there's no possibility of having a
    // 1 where there wasn't a value originally
    return (bits << 1) | (bits >> 3);
}

int main() {
    std::bitset<4> bits1 { 0b0001 };
    std::cout << rotl(bits1) << '\n';

    std::bitset<4> bits2 { 0b1001 };
    std::cout << rotl(bits2) << '\n';

    return 0;
}