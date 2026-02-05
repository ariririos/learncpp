#include <iostream>

template <typename T>
T max(T x, T y) {
    return (x > y) ? x : y;
}

template <typename T, typename U>
auto max(T x, U y) {
    return (x < y) ? y : x;
}

// auto max(auto x, auto y) {}

template <int N>
void print() { std::cout << N << "\n"; }

int main() {
    std::cout << max(1, 2) << "\n";
    std::cout << max(3.0, 4.0) << "\n";
    std::cout << max(1, 2.0) << "\n"; 
    
    print<1>();
    return 0;
}