#include <iostream>

class Base {
public:
    virtual std::string_view get_name() const { return "Base"; }
    virtual ~Base() = default; // to prevent warnings (see 25.4)
};

class Derived : public Base {
public:
    virtual std::string_view get_name() const { return "Derived"; }
};

class A {
public:
    virtual std::string_view get_name() const { return "A"; }
    virtual ~A() = default;
};

class B : public A {
public:
    virtual std::string_view get_name() const { return "B"; }
};

class C : public B {
public:
    virtual std::string_view get_name() const { return "C"; }
};

class D : public C {
public:
    virtual std::string_view get_name() const { return "D"; }
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

    virtual std::string_view speak() const { return "???"; }

    virtual ~Animal() = default;
};

class Cat : public Animal {
public:
    Cat(std::string_view name) : Animal { name } {}

    virtual std::string_view speak() const { return "Meow"; }
};

class Dog : public Animal {
public:
    Dog(std::string_view name) : Animal { name } {}

    virtual std::string_view speak() const { return "Woof"; }
};

void report(const Animal &animal) {
    std::cout << animal.get_name() << " says " << animal.speak() << "\n";
}

int main() {
    // virtual functions are a special type of member function that resolve to the most-derived version of the function for the actual object being referred or pointed to
    // a derived function is a match if it has the same signature and return type as the base version of the function and is called on override
    Derived derived {};
    Base &r_base { derived };
    std::cout << "r_base is a " << r_base.get_name()
              << "\n"; // this calls the derived version

    C c {};
    A &r_base2 { c };
    std::cout
        << "r_base2 is a " << r_base2.get_name()
        << "\n"; // calls C::get_name() because that's the most-derived match on the actual object being called, even if D::get_name() would've been more derived on a D object

    // virtual function resolution only works when a virtual member function is called through a pointer or reference, so that the compiler can differentiate between the type of the pointer/reference and the type of the object being pointed to or referred to
    // virtual functions called directly on an object resolve normally:
    std::cout << c.get_name() << "\n"; // C::get_name()
    A a { c };                         // don't do this
    std::cout << a.get_name() << "\n"; // A::get_name()

    // virtual function resolution is runtime polymorphism

    Cat cat { "Fred" };
    Dog dog { "Garbo" };

    // these now work properly:
    report(cat);
    report(dog);

    // and now we can use these objects in an array and the function calls will work properly:
    const Cat fred { "Fred" };
    const Cat misty { "Misty" };
    const Cat zeke { "Zeke" };

    const Dog garbo { "Garbo" };
    const Dog pooky { "Pooky" };
    const Dog truffle { "Truffle" };

    const Animal *animals[] { &fred, &garbo, &misty, &pooky, &truffle, &zeke };

    for (const auto *animal : animals) {
        std::cout << animal->get_name() << " says " << animal->speak() << "\n";
    }

    // derived class signatures must exactly match the base class virtual function signature to resolve properly; they will compile fine but fail to resolve otherwise (see next lesson for how to guard against this)
    // if a function is marked as virtual, all matching overrides in derived functions are implicitly virtual even if not marked `virtual`; but the reverse isn't true, base functions aren't implicitly virtual if derived functions are
    // under normal circumstances (?), the return type of a virtual function and its override must match
    // you shouldn't call virtual functions from constructors or destructors; if you were to call a virtual function from a Base constructor, the Derived part wouldn't have been constructed yet, and the compiler wouldn't see it, so it would call the Base version; in a Base destructor, it will always call the Base version because the Derived portion of the class will have already been destroyed

    // virtual functions incur a runtime lookup cost as well as a memory cost of an extra pointer for each object of a class with virtual functions
    return 0;
}