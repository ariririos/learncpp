#include <iostream>
#include <string>
#include <string_view>

class Car {
private:
    std::string m_make;
    std::string m_model;
public:
    Car(std::string_view make, std::string_view model)
        : m_make { make }, m_model { model }
    {}
    friend bool operator==(const Car &c1, const Car &c2);
    friend bool operator!=(const Car &c1, const Car &c2);

};

bool operator==(const Car &c1, const Car &c2) {
    return (c1.m_make == c2.m_make && c1.m_model == c2.m_model);
}

bool operator!=(const Car &c1, const Car &c2) {
    return (c1.m_make != c2.m_make || c1.m_model != c2.m_model);
}

class Cents {
private:
    int m_cents {};
public:
    Cents(int cents)
    : m_cents { cents }
    {}

    friend bool operator==(const Cents &c1, const Cents &c2) { return c1.m_cents == c2.m_cents; }
    friend bool operator!=(const Cents &c1, const Cents &c2) { return !(operator==(c1, c2)); }

    friend bool operator<(const Cents &c1, const Cents &c2) { return c1.m_cents < c2.m_cents; }
    friend bool operator>(const Cents &c1, const Cents &c2) { return operator<(c2, c1); }

    friend bool operator<=(const Cents &c1, const Cents &c2) { return !(operator>(c1, c2)); }
    friend bool operator>=(const Cents &c1, const Cents &c2) { return !(operator<(c1, c2)); }
};

int main()
{
    Car corolla{ "Toyota", "Corolla" };
    Car camry{ "Toyota", "Camry" };

    if (corolla == camry)
        std::cout << "a Corolla and Camry are the same.\n";

    if (corolla != camry)
        std::cout << "a Corolla and Camry are not the same.\n";

    // normally it wouldn't make sense to define operator< and operator> for a Car since it's not immediately intuitive what it means
    // but if we want to sort a list of Cars we'll need them defined
    // some of the stdlib container classes require operator< to be defined to keep their contents sorted
    
    // instead of defining each of the six (<, >, <=, >=, ==, !=) comparison operators separately,
    // we can define them in terms of each other:
    // operator!= is !(operator==)
    // operator> is operator< with the parameters flipped
    // operator>= is !(operator<)
    // operator<= is !(operator>)
    // meaning only operator== and operator< need logic and the other four can be implemented in terms of those two

    Cents dime{ 10 };
    Cents nickel{ 5 };

    if (nickel > dime)
        std::cout << "a nickel is greater than a dime.\n";
    if (nickel >= dime)
        std::cout << "a nickel is greater than or equal to a dime.\n";
    if (nickel < dime)
        std::cout << "a dime is greater than a nickel.\n";
    if (nickel <= dime)
        std::cout << "a dime is greater than or equal to a nickel.\n";
    if (nickel == dime)
        std::cout << "a dime is equal to a nickel.\n";
    if (nickel != dime)
        std::cout << "a dime is not equal to a nickel.\n";

    // c++20 adds the spaceship operator, operator<=>, reducing the number of comparison functions we need to 2 or sometimes 1
    return 0;
}