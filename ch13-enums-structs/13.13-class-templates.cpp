#include "../print.h"
#include <utility>

template <typename T> struct Pair {
    T first {};
    T second {};
};

template <typename T> constexpr T max(Pair<T> p) {
    return (p.first < p.second ? p.second : p.first);
}

template <typename T, typename U> struct Pair2 {
    T first {};
    U second {};
};

struct Point {
    int first {};
    int second {};
};

// template <typename T, typename U>
// void print_pair(Pair2<T, U> p) {
template <typename T> void print_parts(T p) {
    std::cout << "[" << p.first << ", " << p.second << "]";
}

int main() {
    Pair<int> p1 { 5, 6 };
    print(p1.first, p1.second, "\n");
    print(max<int>(p1));

    Pair<double> p2 { 1.2, 3.4 };
    print(p2.first, p2.second, "\n");
    print(max(p2));

    Pair<double> p3 { 7.6, 9.0 };
    print(p3.first, p3.second, "\n");

    Pair2<int, double> p4 { 1, 2.3 };
    print_parts(p4);

    std::cout << "\n";

    Point p5 { 7, 8 };
    print_parts(p5);

    std::cout << "\n";

    std::pair<int, int> p6 { 7, 8 };
    print_parts(p6);

    std::cout << "\n";

    return 0;
}