#include <iostream>
#include <string_view>
#include <vector>

class Base {
protected:
    int m_value {};

public:
    Base(int value) : m_value { value } {}

    virtual ~Base() = default;

    virtual std::string_view get_name() const { return "Base"; }
    int get_value() const { return m_value; }
};

class Derived : public Base {
public:
    Derived(int value) : Base { value } {}

    std::string_view get_name() const override { return "Derived"; }
};

void print_name(const Base base) {
    std::cout << "I am a " << base.get_name() << "\n";
}

void print_name2(const Base &base) {
    std::cout << "I am a " << base.get_name() << "\n";
}

int main() {
    // we can use a Derived object like normal:
    Derived derived { 5 };
    std::cout << "derived is a " << derived.get_name() << " and has value "
              << derived.get_value()
              << "\n"; // derived is a Derived and has value 5

    // or through a reference or pointer:
    Base &ref { derived };
    std::cout << "ref is a " << ref.get_name() << " and has value "
              << ref.get_value() << "\n"; // ref is a Derived and has value 5

    Base *ptr { &derived };
    std::cout << "ptr is a " << ptr->get_name() << " and has value "
              << ptr->get_value() << "\n"; // ptr is a Derived and has value 5

    // but if instead of using a Base reference or pointer to a Derived object, we just assign a Derived object to a Base object, only the Base portion of the Derived object gets copied:
    Base base { derived };
    std::cout << "base is a " << base.get_name() << " and has value "
              << base.get_value() << "\n"; // base is a Base and has value 5
    // this is called "object slicing" (the Derived portion has been "sliced off")
    // base was and is still just a Base, so Base's virtual pointer points to Base, so base.get_name() resolves to Base::get_name()
    // object slicing is benign in this case but it can cause unexpected results

    // object slicing is more common with functions where we can accidentally use pass by value rather than pass by reference/pointer, meaning virtual function resolution won't work:
    print_name(derived); // I am a Base
    // we can fix this by using a reference:
    print_name2(derived); // I am a Derived

    // another place where object slicing comes into play is when trying to do polymorphism with std::vector:
    std::vector<Base> v {};
    v.push_back(Base { 5 });
    v.push_back(Derived { 6 });

    std::cout << "std::vector<Base>:\n";
    for (const auto &element : v) {
        std::cout << "I am a " << element.get_name() << " with value "
                  << element.get_value() << "\n";
    } // prints "I am a Base" for both elements

    // we can't fix this by using a std::vector<Base&> because vector elements must be assignable, and references aren't; we can use pointers instead:
    std::vector<Base *> v2 {};
    // if we're using pointers we can't use anonymous objects:
    Base b { 5 };
    Derived d { 6 };
    v2.push_back(&b);
    v2.push_back(&d);

    std::cout << "std::vector<Base*>:\n";
    for (const auto *element : v2) {
        std::cout << "I am a " << element->get_name() << " with value "
                  << element->get_value() << "\n";
    } // this works properly without doing any slicing
    // but now we have to deal with pointer semantics, and nullptr is a valid element; but we can put dynamically allocated objects into the vector now, as long as we remember to delete them

    // we could also use std::reference_wrapper, which mimics an assignable reference:
    std::vector<std::reference_wrapper<Base>> v3 {};
    Base b2 { 5 };
    Derived d2 { 6 };

    v3.push_back(b2);
    v3.push_back(d2);

    std::cout << "std::vector<std::reference_wrapper<Base>>:\n";
    for (const auto &element : v3) {
        std::cout << "I am a " << element.get().get_name() << " with value "
                  << element.get().get_value() << "\n";
    }

    // the Frankenobject: object slicing can create objects with parts of different objects combined into one

    Derived d3 { 5 };
    Derived d4 { 6 };
    Base &b3 { d4 };
    b3 =
        d3; // this invokes the Base operator= and copies the Base portion of d3 into d4; so now d4 has the Base portion of d3 and the Derived portion of d4
    // this happens because the operator= that C++ provides for classes by default isn't virtual
    // there's no easy way to prevent this other than by avoiding assignments like this
    // if Base isn't meant to be instantiated by itself, this can be avoided by making Base non-copyable (delete Base copy constructor and Base assignment operator)

    // overall, try to avoid slicing, make sure function parameters are references/pointers, and try to avoid any pass-by-value for derived classes

    return 0;
}