#include <iostream>

class Base {
public:
    virtual void print() const { std::cout << "Base"; }

    friend std::ostream &operator<<(std::ostream &out,
                                    [[maybe_unused]] const Base &b) {
        out << "Base";
        return out;
    }
    virtual ~Base() {}
};

class Derived : public Base {
public:
    void print() const override { std::cout << "Derived"; }

    friend std::ostream &operator<<(std::ostream &out,
                                    [[maybe_unused]] const Derived &d) {
        out << "Derived";
        return out;
    }
};

namespace Virtual {
    class Base {
    public:
        friend std::ostream &operator<<(std::ostream &out, const Base &b) {
            out << b.identify();
            return out;
        }
        virtual std::string identify() const { return "Base"; }
        virtual ~Base() {}
    };

    class Derived : public Base {
    public:
        std::string identify() const override { return "Derived"; }
    };
} // namespace Virtual

namespace Flexible {
    class Base {
    public:
        friend std::ostream &operator<<(std::ostream &out, const Base &b) {
            return b.print(out);
        }
        virtual std::ostream &print(std::ostream &out) const {
            out << "Base";
            return out;
        }
        virtual ~Base() {}
    };

    struct Employee {
        std::string name {};
        int id {};

        friend std::ostream &operator<<(std::ostream &out, const Employee &e) {
            out << "Employee(" << e.name << ", " << e.id << ")";
            return out;
        }
    };

    class Derived : public Base {
    private:
        Employee m_e {};

    public:
        Derived(const Employee &e) : m_e { e } {}
        std::ostream &print(std::ostream &out) const override {
            out << "Derived: ";
            out << m_e;
            return out;
        }
    };
} // namespace Flexible

int main() {
    std::cout << "Regular:\n";
    // printing using a regular function:
    Derived d {};
    Base &b { d };
    b.print(); // Derived
    std::cout << "\n";
    // but this gets ugly if we need to print something before/after the print() call

    // we can add operator<< the regular way:
    Base b2 {};
    std::cout << b2 << "\n"; // Base

    Derived d2 {};
    std::cout << d2 << "\n"; // Derived

    // but if we try to use operator<< on a derived class it doesn't use virtual function resolution by default:
    Derived d3 {};
    Base &bref { d3 };
    std::cout << bref << "\n"; // Base

    // we can't simply make operator<< virtual for a few reasons:
    // - only member functions can be virtualized and operator<< can't be a member function because it has to be added as a member of its left operand (std::ostream) and that isn't possible in this case
    // - even if we could virtualize operator<< as a member function, the function parameters will still be different between Base::operator<< and Derived::operator<< (the Base version takes a Base parameter and the Derived version takes a Derived parameter), so the Derived version wouldn't be considered an override of the Base version

    // our solution is to just have operator<< on the base class call a normal member function that can be virtualized
    std::cout << "\n\nVirtualized:\n";
    Virtual::Base b4 {};
    std::cout << b4 << "\n"; // Base

    Virtual::Derived d4 {};
    std::cout << d4 << "\n"; // Derived

    Virtual::Base &bref2 { d4 };
    std::cout << bref2 << "\n"; // Derived

    // this solution works but has two shortcomings:
    // - it assumes the desired output can be represented as a single std::string
    // - identify() has no access to the stream object (this becomes an issue if we need to print the value of a member variable that itself has an overloaded operator<<)
    // we can fix this by creating a print() function and delegating responsibility for printing to that function
    // a more flexible solution:
    std::cout << "\n\nFlexible:\n";
    Flexible::Base b5 {};
    std::cout << b5 << "\n";

    Flexible::Derived d5 { Flexible::Employee { "Jim", 4 } };
    std::cout << d5 << "\n";

    Flexible::Base &bref3 { d5 };
    std::cout << bref3 << "\n";

    return 0;
}