#include <iostream>

class Cents {
private:
    int m_cents {};

public:
    Cents(int cents) : m_cents { cents } {}
    Cents operator+(int value) const;
    int get_cents() const { return m_cents; }
};

// when written as a member function, the left parameter is removed and is replaced by the implicit *this object
Cents Cents::operator+(int value) const { return Cents { m_cents + value }; }

int main() {
    const Cents cents1 { 6 };
    const Cents cents2 { cents1 + 2 };
    std::cout << "I have " << cents2.get_cents() << " cents.\n";

    // operator=, operator[], operator(), and operator-> must be overloaded as member functions as required by the language standard
    // but if an operator needs to be added to a class that is fixed as part of the stdlib, it can't be a member function
    // so operator<< can't be a member function, since we would have to add it to std::ostream
    // operator+(Cents, int) can be a member function, but operator+(int, Cents) can't because int isn't a class

    // normal vs friend vs member operator overloads:
    // operators that don't modify the left operand like operator+ should preferably be normal/friend functions so they can work for parameters that aren't classes or aren't modifiable; plus they look more symmetric since both operands will be parameters
    // operators that do modify the left operand like operator+= should preferably be member functions, since the left operand will always be a class, and the lack of symmetry is intentional
    // unary operators are also usually member functions

    return 0;
}