#include <iostream>

template <typename T, typename U, typename V> class Triad {
private:
    T m_first {};
    U m_second {};
    V m_third {};

public:
    Triad(const T &t, const U &u, const V &v)
        : m_first { t }, m_second { u }, m_third { v } {}

    const T &first() const { return m_first; }
    const T &second() const { return m_second; }
    const T &third() const { return m_third; }
    void print() const;
};

template <typename T, typename U, typename V>
void Triad<T, U, V>::print() const {
    std::cout << "[" << m_first << ", " << m_second << ", " << m_third << "]";
}

int main() {
    Triad<int, int, int> t1 { 1, 2, 3 };
    t1.print();
    std::cout << "\n";
    std::cout << t1.first() << "\n";

    using namespace std::literals::string_literals;
    const Triad t2 { 1, 2.3, "Hello"s };
    t2.print(); // 15.2.2, this won't compile if const is removed, would be calling non-const member function on a const object
    std::cout << "\n";

    return 0;
}