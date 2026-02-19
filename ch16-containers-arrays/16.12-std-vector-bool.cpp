#include <vector>
#include <iostream>

// std::vector<bool> (avoid!)
// std::vector has a class template specialization (26.4) for bool similar to std::bitset (O.1)

template <typename T>
void foo(std::vector<T>& v)
{
    T& first = v[0]; // for std::vector<bool>, error: trying to bind a non-const lvalue reference of type bool& to a std::_Bit_reference (type mismatch)
}

int main() {
    // it mostly works like a regular std::vector 
    std::vector<bool> v { true, false, false, true, true };

    for (int i : v) {
        std::cout << i << " ";
    }
    std::cout << "\n";

    v[4] = false;

    for (int i : v) {
        std::cout << i << " ";
    }
    std::cout << "\n";

    // overhead is 40 bytes
    std::vector<bool> v2 {};
    std::cout << "sizeof(std::vector<bool>): " << sizeof(v2) << "\n";

    // except it isn't actually a vector (not contiguous in memory), doesn't hold `bool` (it holds bits), and it isn't a c++ container
    
    // foo(v); // won't compile, see above

    // avoid! you can't disable it but you can:
    // use constexpr std::bitset: when there's a known number of bits, less than 64k bools to store, and no iterator support is fine
    // use std::vector<char>, which works normally, but no space savings
    // use 3rd party, e.g. boost::dynamic-bitset

    return 0;
}