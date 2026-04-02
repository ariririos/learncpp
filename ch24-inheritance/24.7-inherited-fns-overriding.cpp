#include <iostream>

class Base {
public:
    Base() {}
    void identify() const { std::cout << "Base::identify()\n"; }
};

class Derived : public Base {
public:
    Derived() {}
};

class Derived2 : public Base {
public:
    Derived2() {}
    void identify() const { std::cout << "Derived2::identify()\n"; }
};

class Derived3 : public Base {
public:
    Derived3() {}
    void identify() const {
        std::cout << "Derived3::identify()\n";
        Base::identify();
    }
};

class BaseOutput {
public:
    BaseOutput() {}

    friend std::ostream &operator<<(std::ostream &out, const BaseOutput &) {
        out << "In BaseOutput";
        return out;
    }
};

class Derived4 : public BaseOutput {
public:
    Derived4() {}

    friend std::ostream &operator<<(std::ostream &out, const Derived4 &d) {
        out << "In Derived4\n";
        out << static_cast<const BaseOutput &>(d);
        return out;
    }
};

class Base2 {
public:
    void print(int) { std::cout << "Base2::print(int)\n"; }
    void print(double) { std::cout << "Base2::print(double)\n"; }
};

class Derived5 : public Base2 {
public:
};

class Derived6 : public Base2 {
public:
    void print(double) { std::cout << "Derived6::print(double)\n"; }
};

class Derived7 : public Base2 {
public:
    using Base2::
        print; // make all Base::print() functions eligible for overload resolution
    void print(double) { std::cout << "Derived7::print(double)\n"; }
};

int main() {
    // when a function is called on a derived class object, the compiler will select the best matching function from the most-derived class with at least one function with that name
    std::cout << "base:\n";
    Base base {};
    base.identify();

    std::cout << "derived:\n";
    Derived derived {};
    derived.identify();

    // if we define Derived2::identify(), that will be called instead
    std::cout << "derived2:\n";
    Derived2 derived2 {};
    derived2.identify();
    // when you redefine a function in a derived class, the derived function doesn't inherit the access specifier of the function with the same name in the base class, but instead uses whatever access specifier it's defined under in the derived class
    // so a private function in the base class can become public in the derived class or vice versa

    // we can call the base class function from the derived class override by using its fully qualified name
    std::cout << "derived3:\n";
    Derived3 derived3 {};
    derived3.identify();

    // if we want to call friend functions in base classes, like operator<<, we can't call them using a fully qualified name because they're not actually part of the base class, but we can static_cast our derived class into the base class to call the right version of the function
    // this works because Derived4 is-a BaseOutput:
    std::cout << "derived4:\n";
    Derived4 derived4 {};
    std::cout << derived4 << "\n";

    // when we call functions on derived classes, the compiler will select the best matching function from the most-derived class with at least one function with that name
    // **this means overload resolution stops at the first class with a matching function name**
    // Derived5 has no print function so the compiler only looks at Base2 functions:
    std::cout << "derived5:\n";
    Derived5 derived5 {};
    derived5.print(5); // calls Base2::print(int)

    // Derived6 has a print function so the compiler doesn't even look at Base2 when considering overloads
    std::cout << "derived6:\n";
    Derived6 derived6 {};
    derived6.print(5); // calls Derived6::print(double)

    // what if we do want to call Base2::print(int) on a Derived6? we could define a Derived6::print(int) that just calls Base2::print(int) directly; but then we'd need to define a Derived6 equivalent to every Base2 function overload we want to pass through
    // a better option is to use a `using` declaration to pass through all Base functions with a certain name and make them eligible for overload resolution
    std::cout << "derived7:\n";
    Derived7 derived7 {};
    derived7.print(5); // calls Base2::print(int)

    return 0;
}