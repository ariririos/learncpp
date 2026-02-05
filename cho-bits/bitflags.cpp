#include <bitset>
#include <iostream>

int main() {
    std::bitset<8> bits { 0b0000'0101 };
    std::cout << "All bits: " << bits << "\n";
    bits.set(3);
    bits.flip(4);
    bits.reset(4);
    std::cout << "All bits: " << bits << "\n";
    std::cout << "Bit 3 is " << bits.test(3) << "\n";
    std::cout << "Bit 4 is " << bits.test(4) << "\n";

    std::cout << bits.size() << " bits are in the bitset\n";
    std::cout << bits.count() << " bits are set to true\n";

    std::cout << std::boolalpha;
    std::cout << "All bits are true: " << bits.all() << '\n';
    std::cout << "Some bits are true: " << bits.any() << '\n';
    std::cout << "No bits are true: " << bits.none() << '\n';

    std::cout << "(bits >> 1) = " << (bits >> 1) << "\n";
    std::cout << "(bits << 1) = " << (bits << 1) << "\n";
    std::cout << "~bits = " << ~bits << "\n";
    std::cout << "bits | 01010101 = " << (bits | std::bitset<8> { 0b01010101 })
              << "\n";
    std::cout << "bits & 01010101 = " << (bits & std::bitset<8> { 0b01010101 })
              << "\n";
    std::cout << "bits ^ 01010101 = " << (bits ^ std::bitset<8> { 0b01010101 })
              << "\n";
              

    return 0;
}