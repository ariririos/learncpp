#include <iostream>
#include <string>
#include <string_view>

class Employee {
    std::string m_name {};

public:
    void set_name(std::string_view name) { m_name = name; }
    const std::string &get_name() const {
        return m_name;
    } // it's fine to return a (const) lvalue reference to a data member
    // because the lifetime of the data member matches the lifetime of the
    // object containing it and both of these lifetimes exist in the scope of
    // the caller. we shouldn't return a std::string_view because that would
    // require creating a new temporary every time the function was called (it
    // doesn't cause any dangling reference problems though). using auto helps
    // prevent unnecessary conversions:
    // 
    // const auto& get_name() const { return m_name; }
};

// code for rvalue implicit objects
Employee create_employee(std::string_view name) {
    Employee e;
    e.set_name(name);
    return e;
}

// returning non-const references to private data members allows circumventing access control:
class Foo {
private:
    int m_value { 4 };
public:
    int& value() { return m_value; }
};

int main() {
    Employee joe {};
    joe.set_name("Joe");
    std::cout << joe.get_name() << "\n";

    // when returning a reference to a member of an rvalue object, it is only
    // valid within the full expression where the rvalue object was created
    std::cout << create_employee("Frank")
               .get_name(); // fine, using reference within the same expression
    std::cout << "\n";

    const std::string &ref {
        create_employee("Garbo").get_name()
    }; // bad, the reference becomes dangling when the implicit object it refers
       // to is dropped at the end of this expression
    std::cout << ref << "\n"; // undefined behavior

    std::string val {
        create_employee("Hans").get_name()
    }; // fine, the referenced value is copied
    std::cout
        << val
        << "\n"; // okay because val is independent of the referenced member

    // Foo has private member m_value
    Foo f {};
    f.value() = 5; // i.e. m_value = 5 in class context
    std::cout << f.value() << "\n"; // 5, we just wrote to a private member through a non-const reference

    return 0;
}