#include <iostream>

class Cents {
private:
    int m_cents {};

public:
    explicit Cents(int cents) : m_cents { cents } {}
    int get_cents() const { return m_cents; }
};

// we can write the operator as neither a friend function nor a member function
Cents operator+(const Cents &c1, const Cents &c2) {
    return Cents { c1.get_cents() + c2.get_cents() };
}
// if we were to place Cents in a header file, we would need a prototype of this operator+ so other files would know it exists; with a friend function, the declaration in the class served as the prototype

int main() {
    Cents cents1 { 6 };
    Cents cents2 { 8 };
    Cents cents_sum { cents1 + cents2 };
    std::cout << "I have " << cents_sum.get_cents() << " cents.\n";

    // prefer to overload operators with a normal function if doing so doesn't require adding more member functions to get access to internals

    return 0;
}