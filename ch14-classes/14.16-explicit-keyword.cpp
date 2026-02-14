#include <iostream>
#include <string>
#include <string_view>

class Foo {
private:
    int m_x {};

public:
    Foo(int x) : m_x { x } {}

    int get_x() const { return m_x; }
};

void print_foo(Foo f) { std::cout << "Foo(" << f.get_x() << ")\n"; }

class Employee {
private:
    std::string m_name {};

public:
    Employee(std::string_view name) : m_name { name } {}
    // this would work with a C-style string literal if an Employee(const char*)
    // constructor were provided
    const std::string &get_name() const { return m_name; }
};

class Dollars {
private:
    int m_dollars {};

public:
    explicit Dollars(int d) : m_dollars { d } {}
    int get_dollars() const { return m_dollars; }
};

void print(Dollars d) { std::cout << "$" << d.get_dollars() << "\n"; }

void print_employee(Employee e) { std::cout << e.get_name() << "\n"; }

class Bar {
public:
    explicit Bar() {}
    explicit Bar(int x) {}
};

Bar get_bar() {
    // interaction with return by value:
    return Bar {}; // fine
    // return {}; // error: can't implicit;y convert initializer list to Bar
    // return 5; // error: can't implicitly convert int to Bar
    return Bar { 5 }; // fine
    // return { 5 }; // error: can't implicitly convert initializer list to Bar
}

int main() {
    print_foo(5); // works even though we supplied an int - copy initializes
                  // function parameter f with the Foo(int) constructor
                  // (mandatorily elided by c++17, previously created a
                  // temporary Foo then copy constructed it into parameter f)

    // all constructors are "converting constructors" like this by default

    // print_employee("Joe"); // won't compile because only one user-defined
    // conversion may be applied (this requires 2: const char* ->
    // std::string_view -> Employee)

    // this will work with:
    using namespace std::literals;
    print_employee(
        "Joe"sv); // string_view literal, only one conversion required
    print_employee(Employee { "Joe" });

    // print(5); // this implicitly calls the Dollars(int) constructor and is
    // disallowed when it's marked `explicit`

    // direct and direct-list initialization is still fine:
    Dollars d1(5);
    Dollars d2 { 5 };

    // and we can still call print with an explicit constructor:
    print(Dollars { 5 });
    // also fine because static_cast returns an object that is
    // direct-initialized, meaning it will consider explicit constructors when
    // performing the conversion:
    print(static_cast<Dollars>(5));

    // see Bar above for interaction with return by value

    // best practice is to make constructors taking a single argument explicit by default, including constructors with multiple parameters mostly or all with default values
    // do not make copy and move constructors explicit (no conversions are performed)
    // typically don't make explicit: default constructors (converting {}), constructors with multiple required arguments (rarely a candidate for conversions anyway)

    // if the constructed object is semantically equivalent to the argument value, and the conversion is performant, it's usually okay to make a single-argument constructor non-explicit
    // e.g. std::string_view takes a C-style string argument
    // e.g. std::string constructor that takes a std::string_view is marked explicit because it's non-performant

    return 0;
}