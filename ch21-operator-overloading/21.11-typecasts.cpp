#include <iostream>

class Cents {
private:
    int m_cents {};

public:
    Cents(int cents = 0) : m_cents { cents } {}
    // overloaded typecasts must be non-static members and should be const
    // they don't have explicit parameters (implicitly they still have *this) and no return type
    operator int() const { return m_cents; }
    int get_cents() const { return m_cents; }
    void set_cents(int cents) { m_cents = cents; }
};

class Cents2 {
private:
    int m_cents {};

public:
    Cents2(int cents = 0) : m_cents { cents } {}
    // overloaded typecasts must be non-static members and should be const
    // they don't have explicit parameters (implicitly they still have *this) and no return type
    explicit operator int() const { return m_cents; }
    int get_cents() const { return m_cents; }
    void set_cents(int cents) { m_cents = cents; }
};

void print_int(int value) { std::cout << value << "\n"; }

class Dollars {
private:
    int m_dollars {};

public:
    Dollars(int dollars = 0) : m_dollars { dollars } {}
    operator Cents() const { return Cents { m_dollars * 100 }; }
};

void print_cents(Cents cents) {
    std::cout << cents << "\n"; // cents will implicitly cast to an int here
}

int main() {
    // C++ knows how to convert fundamental types to program-defined types (all constructors do this by default) but not the other way around, or program-defined to program-defined
    // we could use a member function to do this but it doesn't mean anything to the compiler and it won't be called for implicit conversions
    // the solution is to override a typecast

    Cents cents { 7 };
    // implicit conversion to int
    print_int(cents);
    // explicit conversion
    std::cout << static_cast<int>(cents) << "\n";

    Dollars dollars { 9 };
    print_cents(dollars); // dollars will implicitly cast to cents here
    // but in this case it's preferable to have a Dollars(Cents) constructor

    // it's possible to make an overloaded typecast explicit so it can only be used via static_cast or direct initialization (parentheses or braces); it will not be considered when doing copy-initialization
    // print_int(Cents2 {}); // won't work
    print_int(static_cast<int>(Cents2 { 2 }));
    // overloaded typecasts should generally be marked as explicit unless it's a cheap conversion to a similar user-defined type
    // so for example Dollars::operator Cents() can be left non-explicit because they're interchangeable
    // (same as how single-parameter converting constructors should be marked explicit)

    // overloaded typecasts and converting constructors are similar:
    // converting constructor is a member function of class type B that defines how B is created from A
    // overloaded typecast is a member function of class type A that defines how A is converted to B
    // both cases go from A to B but differ in whether A or B "owns" the conversion
    // both require access to B or A respectively to implement; but if both B and A are modifiable, **it is preferable to use a converting constructor** so a class type can own its own construction rather than rely on another class to create and initialize it
    // but overloaded typecasts still are preferred for:
    // - conversion to a fundamental type, e.g. bool like std::cin does
    // - when conversion returns a (const) reference
    // - conversion *to* a nonmodifiable type like std::vector (conversion *from* is covered by a converting constructor)
    // - when the type being constructed to shouldn't be aware of the type it's being converted from, to avoid circular dependencies

    // circular dependency example: std::string can be created from std::string_view but not the other way around, otherwise both would #include each other
    // std::string uses an overloaded typecast to handle conversion from std::string_view and std::string_view doesn't know about std::string at all

    // if both a converting constructor and overloaded typecast are present for the same conversion, both are considered for overload resolution, and which is called depends on the constness of the overloaded typecast, the object being converted, and what type of cast or initialization is being used; either one might be called or it might be ambiguous
    // for this reason, **avoid defining an overloaded typecast and converting constructor for the same conversion**

    return 0;
}