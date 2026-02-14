#include <iostream>

class Simple {
private:
    int m_id {};

public:
    Simple(int id) : m_id { id } {}

    int get_id() const { return m_id; }
    void set_id(int id) { m_id = id; }
    void print() const {
        std::cout << this->m_id;
    } // the `this` pointer points at the implicit object, and `->` selects m_id
    // equivalent to:
    // void print() const { std::cout << m_id; }
};

// returning *this for function chaining:
class Calc {
private:
    int m_value {};

public:
    // there's no need to check for null pointer before dereferencing because
    // `this` always points to the implicit object
    Calc &add(int value) {
        m_value += value;
        return *this;
    }
    Calc &sub(int value) {
        m_value -= value;
        return *this;
    }
    Calc &mult(int value) {
        m_value *= value;
        return *this;
    }
    int get_value() const { return m_value; }
    void reset() {
        *this = {};
    } // this creates a new object using the default constructor and assigns it
      // to the current implicit object
};

int main() {
    Simple simple { 1 };
    simple.set_id(2);
    // the call above gets rewritten to:
    // Simple::set_id(&simple, 2);
    // and the set_id signature becomes something like
    // (implementation-specific): static void set_id(Simple* const this, int id)
    simple.print(); // this = &simple, prints 2
    std::cout << "\n";
    // each object has its own implicit this pointer:
    Simple simple2 { 2 };
    simple2.set_id(3);
    simple2.print(); // this = &simple2, prints 3
    std::cout << "\n";

    // you could use `this` for disambiguate member function parameters named
    // the same as data members, but it's used more for function chaining:
    Calc calc {};
    calc.add(5).sub(3).mult(4); // 8
    std::cout << calc.get_value() << "\n";
    calc.reset();
    std::cout << calc.get_value() << "\n";

    // calling a non-const member function on a const object fails because converting `this` from (a const pointer to a const object) to (a const pointer to a non-const object)
    // `this` is only a pointer because it predates references
    return 0;
}