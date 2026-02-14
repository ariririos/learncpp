#include <iostream>
#include <string>

class Employee {
    std::string m_name {};

public:
    Employee(std::string_view name) : m_name { name } {}
    void set_name(std::string_view name) { m_name = name; }
    const std::string &get_name() const { return m_name; }
    // & overloads function to match only lvalue implicit objects
    const std::string &get_name_qualified() const & { return m_name; }
    // && overloads function to match only rvalue implicit objects
    std::string get_name_qualified() const && { return m_name; }
    // this "moves" the member rather than returning a copy when called on a non-const temporary (22.4):
    std::string get_name_qualified() && { return std::move(m_name); }
    // a function can either have non-ref qualified overloads or ref-qualified overloads but not both
    // if only a const lvalue-qualified function exists, it will accept either lvalue or rvalue implicit objects (analagously to how a const lvalue reference can bind to an rvalue)
    // either ref-qualified overload can be deleted and prevent use of the function with that type of implicit object
};

Employee create_employee(std::string_view name) {
    Employee e { name };
    return e;
}

int main() {
    // recall from 14.7 that functions that return a reference to a member of an
    // rvalue class object can cause problems:
    std::cout << create_employee("Frank").get_name()
              << "\n"; // fine, the reference is used in the same expression
    const std::string &ref {
        create_employee("Garbo").get_name()
    }; // reference becomes dangling at the end of this expression when the
       // return value of create_employee() is destroyed
    std::cout << ref << "\n"; // undefined behavior

    // both options for get_name() are undesirable:
    // - returning by value is fine when the implicit object is an rvalue but
    // creates an unnecessary expensive copy every time if the object is an
    // lvalue
    // - returning by const reference is efficient when called on lvalues but
    // undefined behavior on rvalues

    // "ref-qualifiers" allow overloading a member function based on whether it
    // is being called on an lvalue or rvalue implicit object

    Employee joe { "Joe" };
    std::cout << joe.get_name_qualified()
              << "\n"; // joe is an lvalue so this calls std::string& get_name()
                       // &, returning a reference
    std::cout << create_employee("Frank").get_name_qualified()
              << "\n"; // frank is an rvalue so this calls std::string
                       // get_name() &&, making a copy

    // downsides of ref qualifiers:
    // - extra clutter for every getter on a class for a case that can be prevented with proper use of references
    // - in the case where the returned reference would've been used within the same expression, an rvalue overload with return by value creates an unnecessary copy
    // - most developers don't know what this is
    // - standard library doesn't really use it either
    return 0;
}