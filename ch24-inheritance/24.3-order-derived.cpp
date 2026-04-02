#include <iostream>

class Base {
public:
    int m_id {};

    Base(int id = 0) : m_id { id } { std::cout << "Base()\n"; }

    int get_id() const { return m_id; }
};

class Derived : public Base {
public:
    double m_cost {};

    Derived(double cost = 0.0) : m_cost { cost } { std::cout << "Derived()\n"; }

    double get_cost() const { return m_cost; }
};

class A {
public:
    A() { std::cout << "A()\n"; }
};

class B : public A {
public:
    B() { std::cout << "B()\n"; }
};

class C : public B {
public:
    C() { std::cout << "C()\n"; }
};

class D : public C {
public:
    D() { std::cout << "D()\n"; }
};

int main() {
    // a derived class is basically two parts: the base part and the derived part

    // when base is instantiated, memory is allocated for Base and then calls its default constructor
    std::cout << "Instantiating base\n";
    Base base;

    // when derived is instantiated, the most-base class (at the top of the inheritance tree) is instantiated first then each child class is constructed in order until the most-child class
    // in this case the Base portion of derived is instantiated using the Base default constructor, then once it's finished, the Derived poirtion is constructued with the Derived default constructor, then we're done
    std::cout << "Instantiating derived\n";
    Derived derived;

    // this means child classes can use parts from their parents in their constructors but not the other way around

    // another example using an inheritance chain:
    std::cout << "Instantiating A\n";
    A a;
    std::cout << "Instantiating B\n";
    B b;
    std::cout << "Instantiating C\n";
    C c;
    std::cout << "Instantiating D\n";
    D d;

    return 0;
}