#include <iostream>

template <typename T, typename U> class Pair {
private:
    T m_a {};
    U m_b {};

public:
    Pair(const T &a, const U &b) : m_a { a }, m_b { b } {}
    T &first() { return m_a; }
    U &second() { return m_b; }
    const T &first() const { return m_a; }
    const U &second() const { return m_b; }
};

int main() {
    Pair<int, double> p1 { 5, 6.7 };
    std::cout << "Pair: " << p1.first() << ' ' << p1.second() << '\n';

    const Pair<double, int> p2 { 2.3, 4 };
    std::cout << "Pair: " << p2.first() << ' ' << p2.second() << '\n';

    return 0;
}