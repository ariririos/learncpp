#include <cmath>
#include <iostream>

class Base {
public:
    std::string_view say_hi() const { return "Hi"; }
    virtual std::string_view get_name() const { return "Base"; }
    virtual int get_value() const = 0; // pure virtual function
    // int do_something() = 0; // won't compile
    virtual ~Base() {}
};

class Animal {
protected:
    std::string m_name {};

public:
    Animal(std::string_view name) : m_name { name } {}
    const std::string &get_name() const { return m_name; }
    virtual std::string_view speak() const = 0;
    virtual ~Animal() = default;
};

class Cow : public Animal {
public:
    Cow(std::string_view name) : Animal { name } {}
    // we forgot to redefine speak
};

class Cow2 : public Animal {
public:
    Cow2(std::string_view name) : Animal { name } {}
    virtual std::string_view speak() const { return "Moo"; }
};

class Animal2 {
protected:
    std::string m_name {};

public:
    Animal2(std::string_view name) : m_name { name } {}
    const std::string &get_name() const { return m_name; }
    virtual std::string_view speak() const = 0;
    // virtual ~Animal2() = 0; // this will cause a linker failure in derived classes, pure virtual destructors are allowed but must have a definition
    virtual ~Animal2() {}
};

std::string_view Animal2::speak() const { return "buzz"; }

class Dragonfly : public Animal2 {
public:
    Dragonfly(std::string_view name) : Animal2 { name } {}
    std::string_view speak() const override { return Animal2::speak(); }
};

class IErrorLog {
public:
    virtual bool open_log(std::string_view filename) = 0;
    virtual bool close_log() = 0;
    virtual bool write_error(std::string_view error_message) = 0;
    virtual ~IErrorLog() {}
};

double my_sqrt(double value, IErrorLog &log) {
    if (value < 0.0) {
        log.write_error("No imaginary numbers allowed!");
        return 0.0;
    }

    return std::sqrt(value);
}

class FileErrorLog : public IErrorLog {
public:
    bool open_log([[maybe_unused]] std::string_view filename) override {
        return true;
    };
    bool close_log() override { return true; };
    bool write_error([[maybe_unused]] std::string_view error_message) override {
        return true;
    };
};

class ScreenErrorLog : public IErrorLog {
public:
    bool open_log([[maybe_unused]] std::string_view filename) override {
        return true;
    };
    bool close_log() override { return true; };
    bool write_error(std::string_view error_message) override {
        std::cout << error_message << "\n";
        return true;
    };
};

int main() {
    // pure virtual functions (or abstract functions) are functions with no body, which are placeholders meant to be overriden; they are defined by setting a virtual function to 0
    // a class with any pure virtual functions (even one) becomes an abstract base class, which cannot be instantiated (what would Base::get_value() resolve to?)
    // any derived class must define a body for its inherited pure virtual functions or it will become abstract as well

    // our Animal class from before had a virtual function speak() which simply returned "???", but a better solution to ensure speak() gets overriden is to make it pure
    // (this also means the constructor can become public rather than protected if we want, since we can't instantiate Animal anyway)
    // if we defined Cow as above where we forgot to redefine speak, Cow becomes abstract and this code fails to compile:
    // Cow cow { "Betsy" };
    // std::cout << cow.get_name() << " says " << cow.speak() << "\n";
    // but once we redefine speak() it's fine:
    Cow2 cow { "Betsy" };
    std::cout << cow.get_name() << " says " << cow.speak() << "\n";

    // pure virtual functions can be called using a reference/pointer to a base class, same as regular virtual functions:
    Animal &a { cow };
    std::cout << a.speak() << "\n"; // resolves to Cow::speak(), prints "Moo"

    // pure virtual functions can be given a definition, so that derived classes can call that default definition if they want:
    Dragonfly dfly { "Sally" };
    std::cout << dfly.get_name() << " says " << dfly.speak()
              << "\n"; // Sally says buzz

    // a destructor can be made pure virtual but must be given a definition so it can be called when a derived object is destructed (for example, if ~Animal2() is pure virtual, compilation fails at linking with "in function Dragonfly::~Dragonfly(): undefined reference to Animal2::~Animal2()")

    // interface classes have no member variables and all functions are pure virtual; they are used to define which functions derived classes should implement but leave that implementation completely up to the derived class; they are typically named beginning with capital I
    FileErrorLog my_log {};
    ScreenErrorLog my_log2 {};
    my_sqrt(-2, my_log);
    my_sqrt(-2, my_log2);

    // for consistency, abstract classes still have virtual tables, since the constructor or destructor of an abstract class can call a virtual function, and it needs to resolve to a proper function in the same class (derived classes either won't have been created yet or will have already been destroyed)
    // the virtual table entry for a class with a pure virtual function will usually either be a nullptr or a generic function that prints an error (sometimes called __purecall)

    return 0;
}