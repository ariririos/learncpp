#include <iostream>

template <typename T> class Pair1 {
private:
    T m_a {};
    T m_b {};

public:
    Pair1(const T &a, const T &b) : m_a { a }, m_b { b } {}
    T &first() {
        return m_a;
    } // can't make these const functions because then they have the same return type as the const-returning versions below but functions that differ only in return type can't be overloaded
    T &second() { return m_b; }
    const T &first() const { return m_a; }
    const T &second() const { return m_b; }
};

int main() {
    Pair1<int> p1 { 5, 8 };
    std::cout << "Pair: " << p1.first() << ' ' << p1.second() << '\n';

    const Pair1<double> p2 { 2.3, 4.5 };
    std::cout << "Pair: " << p2.first() << ' ' << p2.second() << '\n';

    return 0;
}