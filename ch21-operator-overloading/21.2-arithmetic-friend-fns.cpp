#include <iostream>

class Cents {
private:
    int m_cents {};

public:
    explicit Cents(int cents) : m_cents { cents } {}
    friend Cents operator+(const Cents &c1, const Cents &c2);
    friend Cents operator-(const Cents &c1, const Cents &c2);
    friend Cents operator+(const Cents &c1, int value);
    friend Cents operator+(int value, const Cents &c1);
    int get_cents() const { return m_cents; }
};

// these functions can also be defined inside the class
Cents operator+(const Cents &c1, const Cents &c2) {
    return Cents { c1.m_cents + c2.m_cents };
}
Cents operator-(const Cents &c1, const Cents &c2) {
    return Cents { c1.m_cents - c2.m_cents };
}
Cents operator+(const Cents &c1, int value) {
    return Cents { c1.m_cents + value };
}
Cents operator+(int value, const Cents &c1) {
    return Cents { c1.m_cents + value };
}

class MinMax {
private:
    int m_min {};
    int m_max {};

public:
    MinMax(int min, int max) : m_min { min }, m_max { max } {}
    int get_min() const { return m_min; }
    int get_max() const { return m_max; }
    friend MinMax operator+(const MinMax &m1, const MinMax &m2);
    friend MinMax operator+(const MinMax &m, int value);
    friend MinMax operator+(int value, const MinMax &m);
};

MinMax operator+(const MinMax &m1, const MinMax &m2) {
    int min { m1.m_min < m2.m_min ? m1.m_min : m2.m_min };
    int max { m1.m_max < m2.m_max ? m1.m_max : m2.m_max };
    return MinMax { min, max };
}

MinMax operator+(const MinMax &m, int value) {
    int min { m.m_min < value ? m.m_min : value };
    int max { m.m_max > value ? m.m_max : value };
    return MinMax { min, max };
}

MinMax operator+(int value, const MinMax &m) {
    return m + value; // calls operator+(MinMax, int)
}

int main() {
    // operator+(Cents, Cents) gets called here
    Cents cents1 { 6 };
    Cents cents2 { 8 };
    Cents cents_sum { cents1 + cents2 };
    std::cout << "I have " << cents_sum.get_cents() << " cents.\n";
    Cents cents_diff { cents1 - cents2 };
    std::cout << "Now I have " << cents_diff.get_cents() << " cents.\n";

    // but if adding a Cents and an int, we need two separate functions, operator+(Cents, int) and operator+(int, Cents)
    Cents c1 { Cents { 4 } + 6 };
    Cents c2 { 6 + Cents { 4 } };
    std::cout << "I have " << c1.get_cents() << " cents.\n";
    std::cout << "I have " << c2.get_cents() << " cents.\n";

    MinMax m1 { 10, 15 };
    MinMax m2 { 8, 11 };
    MinMax m3 { 3, 12 };
    MinMax m_final { m1 + m2 + 5 + 8 + m3 + 16 };

    std::cout << "Result: (" << m_final.get_min() << ", " << m_final.get_max()
              << ")\n";

    return 0;
}