#include <iostream>

class Base {
public:
    ~Base() { std::cout << "Calling ~Base()\n"; }
};

class Derived : public Base {
private:
    int *m_array {};

public:
    Derived(int length) : m_array { new int[length] } {}
    Derived(const Derived &) = delete;
    Derived operator=(const Derived &) = delete;
    ~Derived() {
        std::cout << "Calling ~Derived()\n";
        delete[] m_array;
    }
};

class Base2 {
public:
    virtual ~Base2() { std::cout << "Calling ~Base2()\n"; }
};

class Derived2 : public Base2 {
private:
    int *m_array {};

public:
    Derived2(int length) : m_array { new int[length] } {}
    Derived2(const Derived2 &) = delete;
    Derived2 operator=(const Derived2 &) = delete;
    virtual ~Derived2() {
        std::cout << "Calling ~Derived2()\n";
        delete[] m_array;
    }
};

class Base3 {
public:
    virtual ~Base3() = default;
    virtual std::string_view get_name() const { return "Base"; }
};

class Derived3 : public Base3 {
public:
    virtual std::string_view get_name() const { return "Derived"; }
};

int main() {
    // if you're dealing with inheritance, your destructors should *always* be virtual, otherwise derived class constructors won't be called
    Derived *derived { new Derived(5) };
    Base *base { derived };

    delete base; // because base is a pointer, the compiler checks to see if ~Base() is virtual; since it's not, it only calls the Base destructor

    Derived2 *derived2 { new Derived2(5) };
    Base2 *base2 { derived2 };

    delete base2; // this properly calls ~Derived2() then ~Base2()

    // ~Derived2() didn't actually need to be marked virtual, because it would match anyway
    // in fact if ~Derived2() were empty we wouldn't even have to explicitly declare it to make it virtual

    // virtual assignment is possible but is a more advanced topic

    // we can explicitly ignore virtualization by using the scope resolution operator:
    Derived3 derived3 {};
    const Base3 &base3 { derived3 };

    // calls Base3::get_name() instead of Derived3::get_name():
    std::cout << base3.Base3::get_name() << "\n";

    // so do we make all destructors virtual? this means we can use any class as a base class but also every instance of the class has an additional virtual pointer
    // otherwise if a class isn't designed to be a base class then it's better to have no virtual members and no virtual destructor
    // the conventional wisdom is that "a base class destructor should be either public and virtual or protected and non-virtual"
    // a base class with a protected destructor can't be deleted using a base class pointer, meaning a derived class object can't be deleted through a base class pointer either
    // but this unfortunately also prevents *any* use of the base class destructor by the public; so we shouldn't dynamically allocate base class objects since we can't delete them using any conventional means; and we can't even statically allocate them either because we can't call the destructor when it goes out of scope
    // this means the base class is practically unusable by itself, even though its derived classes are more safe:
    /*
    class Base4 {
        private:
        ~Base4() {}
    };

    Base4 base4 {}; // this line won't compile
    */

    // a better way is to use `final`:
    // - if you intend a class to be inherited from, make its destructor virtual and public
    // - if you intend a class to not be inherited from, mark it as final; the class will still be usable by itself

    return 0;
}