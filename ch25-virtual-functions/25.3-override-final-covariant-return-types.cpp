#include <iostream>
#include <string_view>

class A {
public:
    virtual std::string_view get_name1(int) { return "A"; }
    virtual std::string_view get_name2(int) { return "A"; }
    virtual std::string_view get_name3(int) { return "A"; }
    virtual ~A() = default;
};

class B : public A {
public:
    // std::string_view get_name1(short int) override { return "B"; } // won't work, parameters don't match
    // std::string_view get_name2(int) const override { return "B"; } // won't work, constness doesn't match
    std::string_view get_name3(int) override { return "B"; }
};

class C {
public:
    virtual std::string_view get_name() const { return "C"; }
    virtual ~C() = default;
};

class D : public C {
public:
    std::string_view get_name() const override final {
        return "B";
    } // a `final` function can itself be an override but can't be overriden
};

class E : public D {
public:
    // std::string_view get_name() const override { return "E"; } // won't compile, trying to override a `final` function
};

class F {
public:
    virtual std::string_view get_name() const { return "A"; }
    virtual ~F() = default;
};

class G final : public F {
public:
    std::string_view get_name() const override { return "G"; }
};

// won't compile, can't inherit from a base final class
// class H: public G {
// public:
//     std::string_view get_name() const override {
//         return "H";
//     }
// }

class Base {
public:
    virtual Base *get_this() {
        std::cout << "called Base::get_this()\n";
        return this;
    }
    void print_type() { std::cout << "returned a Base\n"; }
    virtual ~Base() = default;
};

class Derived : public Base {
public:
    Derived *get_this() override {
        std::cout << "called Derived::get_this()\n";
        return this;
    }
    void print_type() { std::cout << "returned a Derived\n"; }
};

int main() {
    // we can mark derived class overrides with the `override` specifier to have the compiler check that it matches a base class virtual function; if a member function is both const and override, the const comes before the override
    // `override` is checked at compile time and should be applied to all derived function overrides (including destructors); `virtual` is implied and as such is unnecessary on derived overrides

    // the `final` specifier blocks overrides of virtual base functions and inheriting from classes

    // there is one special case where the return type of base and derived virtual functions can differ and still be considered a match -- when the return type is covariant, meaning the virtual function returns a pointer or reference to some class, override functions can return a pointer or reference to a derived class
    Derived d {};
    Base *b { &d };
    d.get_this()
        ->print_type(); // calls Derived::get_this(), returns a Derived*, calls Derived::print_type()
    b->get_this()
        ->print_type(); // calls Derived::get_this(), returns a Base*, calls Base::print_type()
    // what's happening here:
    // - d.get_this() is a regular function call to Derived::get_this(), which returns a Derived*, then non-virtual function Derived::print_type() is called on that
    // - b->get_this() is a virtual function call; it's called on a Base* but virtual function resolution gives us Derived::get_this(); even though Derived::get_this() returns a Derived*, the Base version returns a Base*, so the Derived* gets upcast to a Base*; and finally, since Base::print_type() is non-virtual, Base::print_type() is called
    // => you only get a Derived* if you call get_this() on an object with Derived type in the first place
    // if print_type() had been virtual, we would've resolved it down back to Derived::print_type()
    // this is usually used when a virtual member function returns a pointer/reference to its containing class, but this isn't necessary, and works for any two covariant types
    return 0;
}