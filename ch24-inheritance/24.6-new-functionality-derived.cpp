#include <iostream>

class Base {
protected:
    int m_value {};

public:
    Base(int value) : m_value { value } {}
    void identify() const { std::cout << "I am a Base\n"; }
};

class Derived : public Base {
public:
    Derived(int value) : Base { value } {}
    // we can add a function to access Base's m_value here for the sake of example
    int get_value() const { return m_value; }
};

int main() {
    Derived derived { 5 };
    std::cout << "derived has value " << derived.get_value() << "\n";

    return 0;
}