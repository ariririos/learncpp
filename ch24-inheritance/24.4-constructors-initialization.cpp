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

class Derived2 : public Base {
public:
    double m_cost {};

    Derived2(double cost = 0.0, int id = 0) : Base(id), m_cost { cost } {
        std::cout << "Derived2()\n";
    }

    double get_cost() const { return m_cost; }
};

class Base2 {
private:
    int m_id {};

public:
    Base2(int id = 0) : m_id { id } {}

    int get_id() const { return m_id; }
};

class Derived3 : public Base2 {
private:
    double m_cost {};

public:
    Derived3(double cost = 0.0, int id = 0) : Base2 { id }, m_cost { cost } {}

    double get_cost() const { return m_cost; }
};

class Person {
private:
    std::string m_name {};
    int m_age {};

public:
    Person(std::string_view name = "", int age = 0)
        : m_name { name }, m_age { age } {}

    const std::string &get_name() const { return m_name; }
    int get_age() const { return m_age; }
};

class BaseballPlayer : public Person {
private:
    double m_batting_average {};
    int m_home_runs {};

public:
    BaseballPlayer(std::string_view name = "", int age = 0,
                   double batting_average = 0.0, int home_runs = 0)
        : Person { name, age }, m_batting_average { batting_average },
          m_home_runs { home_runs } {}

    double get_batting_average() const { return m_batting_average; }
    int get_home_runs() const { return m_home_runs; }
};

class A {
public:
    A(int a) { std::cout << "A: " << a << "\n"; }
};

class B : public A {
public:
    B(int a, double b) : A { a } { std::cout << "B: " << b << "\n"; }
};

class C : public B {
public:
    C(int a, double b, char c) : B { a, b } { std::cout << "C: " << c << "\n"; }
};

int main() {
    // when base is instantiated:
    // - memory for base is set aside
    // - the appropriate Base constructor is called
    // - the member initializer list initializes variables
    // - the constructor body executes
    // - control is returned to the caller
    Base base { 5 };

    // when derived is instantiated:
    // - memory is derived is set aside (both the Base and Derived portions)
    // - the appropriate Derived constructor is called
    // - the Base object is constructed first using the appropriate Base constructor; if no base constructor is specified, the default constructor will be used
    // - the member initializer list initializes variables
    // - the constructor body executes
    // - control is returned to the caller
    Derived derived { 1.3 };

    // we can't set Base's m_id using the current Derived constructor; this way won't work:
    /*
    Derived(double cost=0.0, int id=0)
        : m_cost { cost },
          m_id { id }
    {}
    */
    // this is disallowed because if the base class's member variables were const or references, they must be set when the variable is created, but then the derived class could change them; with this restriction, each variable will be initialized only once

    // we can set it in the body of the Derived constructor, but this is inefficient because they get set twice; and in any case, Base couldn't access the value since it wouldn't be set until after the Base constructor ran

    // but we do have the ability to tell Derived which Base constructor to use and consequently directly initialize its members in the constructor

    // when we initialize derived2:
    // - memory for derived2 is allocated
    // - Derived2(double, int) is called
    // - the compiler checks if we've asked for a particular Base constructor, and since we have, it calls Base(int)
    // - base class constructor member initializer list runs
    // - base class constructor body runs
    // - base class constructor returns
    // - derived class constructor member initializer runs
    // - derived class constructor runs
    // - derived class constructor returns

    Derived2 derived2 { 1.3, 5 };
    std::cout << "Id: " << derived2.get_id() << "\n";
    std::cout << "Cost: " << derived2.get_cost() << "\n";

    // given this, we can make base class members private and work with them through constructors and member functions; derived classes won't be able to access private base class members
    Derived3 derived3 { 1.3, 5 };
    std::cout << "Id: " << derived3.get_id() << "\n";
    std::cout << "Cost: " << derived3.get_cost() << "\n";

    // another example:
    BaseballPlayer pedro { "Pedro Cerrano", 32, 0.342, 42 };
    std::cout << pedro.get_name() << "\n";
    std::cout << pedro.get_age() << "\n";
    std::cout << pedro.get_batting_average() << "\n";
    std::cout << pedro.get_home_runs() << "\n";

    // an example of an inheritance chain:
    C c { 5, 4.3, 'R' };
    // C calls B, which calls A; C never directly calls A

    // destructors run in the reverse order of construction; when c is destroyed, the C destructor runs first, then B, then A
    // if the base class has virtual functions, then the destructor should also be virtual, otherwise undefined behavior can occur in certain cases (see 25.4)

    return 0;
}