#include <iostream>
#include <string>

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

template <typename V> class StringValuePair : public Pair<std::string, V> {
public:
    StringValuePair(std::string_view str, const V &val)
        : Pair<std::string, V> { static_cast<std::string>(str), val } {}
};

int main() {
    StringValuePair<int> svp { "Hello", 5 };
    std::cout << "Pair: " << svp.first() << ' ' << svp.second() << '\n';

    return 0;
}