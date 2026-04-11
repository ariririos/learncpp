#include <iostream>

class Base {
protected:
    int m_value {};

public:
    Base(int value) : m_value { value } {}

    virtual ~Base() = default;
};

class Derived : public Base {
protected:
    std::string m_name {};

public:
    Derived(int value, std::string_view name)
        : Base { value }, m_name { name } {}

    const std::string &get_name() const { return m_name; }
};

Base *get_object(bool return_derived) {
    if (return_derived) {
        return new Derived { 1, "Apple" };
    } else {
        return new Base { 2 };
    }
}

namespace StaticCast {
    enum class ClassID { base, derived };

    class Base {
    protected:
        int m_value {};

    public:
        Base(int value) : m_value { value } {}

        virtual ~Base() = default;
        virtual ClassID get_class_id() const { return ClassID::base; }
    };

    class Derived : public Base {
    protected:
        std::string m_name {};

    public:
        Derived(int value, std::string_view name)
            : Base { value }, m_name { name } {}
        const std::string &get_name() const { return m_name; }
        ClassID get_class_id() const override { return ClassID::derived; }
    };

    Base *get_object(bool return_derived) {
        if (return_derived) {
            return new Derived { 1, "Apple" };
        } else {
            return new Base { 2 };
        }
    }
} // namespace StaticCast

int main() {
    Base *b { get_object(true) };

    // b can point to either a Base or Derived based on the return value of get_object; we can't call Derived::get_name() directly on b
    // we could provide a virtual function on Base that would dynamically resolve to Derived::get_name() but that's just cluttering Base with unrelated functionality (plus it wouldn't make any sense when called on Base)

    // c++ already lets us turn a Derived pointer into a Base pointer (that's what get_object() does) -- this is called upcasting

    // if we cast from a Base pointer to a Derived pointer, then we could call Derived::get_name() directly and not have to worry about virtual function resolution

    // dynamic_cast is used to turn base-class pointers into derived-class pointers -- this is called downcasting
    Derived *d { dynamic_cast<Derived *>(b) };

    // dynamic_cast will return a nullptr if it fails, so we should check the result to make sure it succeeded; otherwise we could end up dereferencing a nullptr on the "d->get_name()" line
    if (d) {
        std::cout << "The name of the Derived is: " << d->get_name() << "\n";
    }

    // dynamic_cast does some consistency checking at runtime so it incurs a runtime penalty
    // dynamic_cast won't work if:
    // - using protected or private inheritance
    // - for classes that don't declare or inherit any virtual functions (also thus lack a virtual table)
    // - when you use virtual base classes in a manner that creates ambiguity along the class hierarchy back to the base class

    // we can use static_cast to do downcasting as well, but it does no runtime type checking and can result in undefined behavior
    // we can use a virtual function to make sure we know what type of object we're pointing to
    StaticCast::Base *b2 { StaticCast::get_object(true) };
    if (b2->get_class_id() == StaticCast::ClassID::derived) {
        StaticCast::Derived *d2 { static_cast<StaticCast::Derived *>(b2) };
        std::cout << "The name of the StaticCast::Derived is: "
                  << d2->get_name() << "\n";
    }
    // but if we're gonna do all this and pay the cost of virtual function resolution we might as well just use dynamic_cast
    // also consider that if our object were actually some class derived from Derived (e.g. D2), then b2->get_class_id() will return, for example, ClassID::D2, which doesn't match ClassID::Derived; but dynamic_cast would work here since D2 is a Derived

    // dynamic_cast works with references as well, analogously to how it works with pointers
    Derived apple { 1, "Apple" };
    Base &b_apple { apple };
    Derived &d_apple { dynamic_cast<Derived &>(b_apple) };
    std::cout << "The name of the Derived is: " << d_apple.get_name() << "\n";
    // if a dynamic_cast of a reference fails, there's no "null reference" so it throws an exception of type std::bad_cast

    delete b;

    // overall: use static_cast unless you're downcasting, then use dynamic_cast; but also consider not casting at all and just using virtual functions

    // a dynamic_cast is sometimes considered bad design, but sometimes they have advantages over virtual functions:
    // - when you can't modify the base class to add a virtual function
    // - when you need access to something derived-class specific
    // - when adding a virtual function to the base class doesn't make sense (although using a pure virtual function may be an option if you don't need to instantiate the base class)

    // dynamic_cast doesn't work if RTTI (runtime type information) is turned off
    return 0;
}
