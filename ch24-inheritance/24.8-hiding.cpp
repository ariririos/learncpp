#include <iostream>

class Base {
private:
    int m_value {};

public:
    Base(int value) : m_value { value } {}

protected:
    void print_value() const { std::cout << m_value << "\n"; }
};

class Derived : public Base {
public:
    Derived(int value) : Base { value } {}

    // Base::print_value was inherited as protected, so the public has no access, but we're changing it to public via this using declaration
    using Base::print_value;
};

class Base2 {
public:
    int m_value {};
};

class Derived2 : public Base2 {
private:
    // make Base's m_value private
    using Base2::m_value;

public:
    Derived2(int value) : Base2 { value } {}
};

class Base3 {
public:
    int m_value {};

    int get_value() const { return m_value; }
    int get_value(int) const { return m_value; }
};

class Derived3 : public Base3 {
private:
    using Base3::get_value; // make all get_value overloads private
public:
    Derived3(int value) : Base3 { value } {}
};

class Derived4 : public Base3 {
public:
    Derived4(int value) : Base3 { value } {}

    int get_value() const = delete;
};

int main() {
    // we can change the access specifiers of public and protected inherited members in derived classes;
    Derived derived { 7 };
    derived
        .print_value(); // we made print_value public in Defined so this is allowed

    // private members in the base class remain inaccessible and can't be exposed via this process

    // we can't remove or restrict functionality that exists in a base class but we can hide functionality from a base class in a derived class simply by changing the relevant access specifier
    Derived2 derived2 { 7 };
    // std::cout << derived2.m_value; // won't work, m_value is private in Derived

    Base2 &base2 { derived2 };
    std::cout << base2.m_value
              << "\n"; // this is fine, m_value is public in Base2
    // we can encapsulate Base2 within Derived2, but we can subvert that encapsulation by casting to Base& and directly accessing the member

    // aside: this means if a Base class has a public virtual function, and a Derived class changes the access specifier to private, the public can still access the private Derived function by casting a Derived to a Base& and calling the virtual function; this is allowed because the function is public in Base -- but since the object is actually a Derived, virtual function resolution will resolve to the private Derived version of the function
    // access controls aren't enforced at runtime
    /*
    class A {
    public:
        virtual void fun() {
            std::cout << "public A::fun()\n";
        }
    };

    class B: public A {
    private:
        virtual void fun() {
            std::cout << "private B::fun()\n";
        }
    };

    int main() {
        B b {};
        // b.fun(); // this won't work, B::fun() is private
        static_cast<A&>(b).fun(); // this is fine because A::fun() is public, but resolves to private B::fun() at runtime

        return 0;
    }
    */

    // given a set of overloaded functions in the base class, we can't change the access specifier for only a single overload, only all of them
    [[maybe_unused]] Derived3 derived3 { 7 };
    // neither of these will work because both are private in Derived3:
    // std::cout << derived.get_value();
    // std::cout << derived.get_value(5);

    // we can also delete functions in a derived class to make them inaccessible from the derived object
    Derived4 derived4 { 7 };
    // std::cout << derived4.get_value(); // won't work, deleted
    // but Base3::get_value() is still accessible:
    std::cout << derived4.Base3::get_value() << "\n";
    std::cout
        << static_cast<Base3 &>(derived4).get_value()
        << "\n"; // we cast to Base3& rather than Base3 to avoid making a copy of the Base3 portion of derived4

    return 0;
}