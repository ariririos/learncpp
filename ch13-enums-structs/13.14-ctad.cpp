#include <iostream>
#include <utility>

template <typename T=int, typename U=int>
struct Pair {
    T first {};
    U second {};
};

// deduction guide (only needed in c++17)
template <typename T, typename U>
Pair(T, U) -> Pair<T, U>;

struct Foo {
    std::pair<int, int> p1 { 1, 2 };
    // std::pair p2 { 1, 2 }; // error: CTAD not allowed in non-static member initialization
};

// void print(std::pair p) { // won't work, there's no way the compiler can deduce the types at this point, before the function has been called
template<typename T, typename U>
void print(std::pair<T, U> p) { // using a template allows deduction of the types based on what the function is actually called with
    std::cout << p.first << " " << p.second << "\n";
}

int main() {
    std::pair<int, int> p1 { 1, 2 };
    std::pair p2 { 1, 2 }; // from c++17, template type arguments can be deduced
    // std::pair<> p1 { 1, 2 }; // not allowed
    // std::pair<int> p1 { 1, 2 }; // not allowed either
    std::pair p3 { 3.4f, 5.6f }; // deduced as pair<float, float>
    std::pair p4 { 1u, 2u }; // pair<unsigned int, unsigned int>
    Pair p5 { 1, 2 }; // in c++17 only, can't deduce template types without the deduction guide above
    Pair p6; // uses default Pair<int, int>
    print(p4);
}