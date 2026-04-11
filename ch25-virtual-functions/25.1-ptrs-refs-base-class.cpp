#include <array>
#include <iostream>
#include <string_view>

class Base {
protected:
    int m_value {};

public:
    Base(int value) : m_value { value } {}

    std::string_view get_name() const { return "Base"; }
    int get_value() const { return m_value; }
};

class Derived : public Base {
public:
    Derived(int value) : Base { value } {}

    std::string_view get_name() const { return "Derived"; }
    int get_value_doubled() const { return m_value * 2; }
};

class Animal {
protected:
    std::string m_name {};

    Animal(std::string_view name) : m_name { name } {}

    // to prevent slicing (covered later)
    Animal(const Animal &) = delete;
    Animal &operator=(const Animal &) = delete;

public:
    std::string_view get_name() const { return m_name; }
    std::string_view speak() const { return "???"; }
};

class Cat : public Animal {
public:
    Cat(std::string_view name) : Animal { name } {}
    std::string_view speak() const { return "Meow"; }
};

class Dog : public Animal {
public:
    Dog(std::string_view name) : Animal { name } {}

    std::string_view speak() const { return "Woof"; }
};

void report(const Animal &r_animal) {
    std::cout << r_animal.get_name() << " says " << r_animal.speak() << "\n";
}

template <typename T> void report2(const T &r_animal) {
    std::cout << r_animal.get_name() << " says " << r_animal.speak() << "\n";
}

int main() {
    // this chapter is about virtual functions and polymorphism; let's set the stage first

    // we can set pointers and references to Derived objects, of course:
    Derived derived { 5 };
    std::cout << "derived is a " << derived.get_name() << " and has value "
              << derived.get_value() << "\n";

    Derived &r_derived { derived };
    std::cout << "r_derived is a " << r_derived.get_name() << " and has value "
              << r_derived.get_value() << "\n";

    Derived *p_derived { &derived };
    std::cout << "p_derived is a " << p_derived->get_name() << " and has value "
              << p_derived->get_value() << "\n";

    // we can also set references and pointers to the Base part of a Derived object:
    Base &r_base { derived };
    Base *p_base { &derived };
    std::cout << "derived is a " << derived.get_name() << " and has value "
              << derived.get_value() << "\n";
    std::cout << "r_base is a " << r_base.get_name() << " and has value "
              << r_base.get_value() << "\n";
    std::cout << "p_base is a " << p_base->get_name() << " and has value "
              << p_base->get_value() << "\n";
    // pointers and references to Base objects can only see the Base part of a class (or any parts that Base itself inherited); so even though Derived::get_name() hides Base::get_name(), if a Base pointer/reference is used, it can only see the latter
    // we also can't call Derived::get_value_doubled() using this pointer or reference because they can't see it at all

    const Cat cat { "Fred" };
    std::cout << "cat is named " << cat.get_name() << ", and it says "
              << cat.speak() << "\n";

    const Dog dog { "Garbo" };
    std::cout << "dog is named " << dog.get_name() << ", and it says "
              << dog.speak() << "\n";

    const Animal *p_animal { &cat };
    std::cout << "p_animal is named " << p_animal->get_name()
              << ", and it says " << p_animal->speak() << "\n";

    p_animal = &dog;
    std::cout << "p_animal is named " << p_animal->get_name()
              << ", and it says " << p_animal->speak() << "\n";

    // if we want to pass objects of different derived classes that all have the same interface to a function, we can't do this using pointers/references to the base class due to this behavior; we'd need a bunch of overrides for each different derived class, or use templates and lose information about what the interface was supposed to be
    report(cat);  // only sees the Animal part
    report2(cat); // works but has no information about the desired interface

    // this also means we can't create arrays to derived objects related by the same base class, since they have different types
    // we need a separate array for each type of derived object
    /*
    //
    // this code won't actually compile because Cat and Dog have a deleted move constructor due to the deleted Animal copy constructor and I'm not sure if adding a move constructor to the derived classes is correct 
    const auto &cats { std::to_array<Cat>(
        { { "Fred" }, { "Misty" }, { "Zeke" } }) };

     const auto &dogs { std::to_array<Cat>(
        { { "Garbo" }, { "Pooky" }, { "Truffle" } }) };  
        
    for (const auto& cat: cats) {
        std::cout << cat.get_name() << " says " << cat.speak() << "\n";
    }

     for (const auto& dog: dogs) {
        std::cout << dog.get_name() << " says " << dog.speak() << "\n";
    }
    */

    // notwithstanding the move constructor issue, we can't correctly solve this problem using an array of pointers to Animal due to the same problem as before:
    const Cat fred { "Fred" };
    const Cat misty { "Misty" };
    const Cat zeke { "Zeke" };

    const Dog garbo { "Garbo" };
    const Dog pooky { "Pooky" };
    const Dog truffle { "Truffle" };

    const auto animals { std::to_array<const Animal *>(
        { &fred, &garbo, &misty, &pooky, &truffle, &zeke }) };

    for (const auto animal : animals) {
        std::cout << animal->get_name() << " says " << animal->speak()
                  << "\n"; // we get the right names but every animal says "???"
    }

    // virtual functions solve this problem by allowing pointers/references to a base class call the derived version of a function

    return 0;
}