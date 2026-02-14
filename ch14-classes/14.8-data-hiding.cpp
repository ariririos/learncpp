#include <iostream>
#include <string>
#include <string_view>

class Employee {
    std::string m_name { "John" };

public:
    void set_name(std::string_view name) {
        m_name = name;
    }

    // this will cause undefined behavior (or in debug, an assertion failure) if the string is empty
    char first_initial() const { return m_name.front(); }

    void print() const {
        std::cout << "Employee " << m_name << " has first initial " << first_initial() << "\n";
    }
};

class Yogurt {
    std::string m_flavor { "Vanilla" };
public:
    void set_flavor(std::string_view flavor) {
        m_flavor = flavor;
    }

    const std::string& get_flavor() const { return m_flavor; }
};

// making this a non-member function requires it to use the public interface of the class
// and improves encapsulation by reducing the API surface
void print(const Yogurt& y) {
    std::cout << "The yogurt has flavor " << y.get_flavor() << "\n";
}

int main() {
    Employee e {};
    e.set_name("John");
    e.print();

    e.set_name("Mark");
    e.print();

    // undefined behavior:
    // e.set_name("");
    // e.print();

    Yogurt y {};
    y.set_flavor("cherry");
    print(y);

    return 0;
}