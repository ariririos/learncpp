#include <iostream>

template <typename T>
struct Pair {
    T first {};
    T second {};
};

// alias template; must be declared globally like any other template
template <typename T>
using Coord = Pair<T>;

// template <typename T>
// void print(const Pair<T>& p) {
//     std::cout << p.first << " " << p.second << "\n";
// }

template <typename T>
void print(const Coord<T>& c) {
    std::cout << c.first << " " << c.second << "\n";
}

int main() {
    using Point = Pair<int>;
    Point p { 1, 2 };
    print(p);

    Coord<int> p1 { 1, 2 }; // pre-c++20, arguments to alias templates must be provided
    Coord p2 { 1, 2 }; // starting with c++20 they can be deduced
    print(p1);
    print(p2);

    return 0;
}