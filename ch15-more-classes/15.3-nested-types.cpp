#include <iostream>

class Fruit {
public:
    enum Type { // class definitions can have associated types, putting this
                // enum here instead of outside the class solidifies the
                // connection between the two
        // enum rather than enum class since the class definition already
        // provides an enclosing scope
        apple,
        banana,
        cherry
    };
    // nested types must be fully defined before they can be used

private:
    Type m_type {};
    int m_percentage_eaten { 0 };

public:
    Fruit(Type type) : m_type { type } {}

    Type get_type() { return m_type; }
    int get_percentage_eaten() { return m_percentage_eaten; }
    bool is_cherry() { return m_type == cherry; // fully qualified name is not necessary inside the class definition
    }
};

class Employee {
public:
    // nested typedefs are fine and are exposed if public
    using IDType = int;

    class Printer {
    public:
        void print(const Employee& e) const {
            // Printer can't access Employee's this pointer so it can't be printed directly (without the Employee parameter)
            // however since Printer is a member of Employee, we can access its private members directly
            std::cout << e.m_name << " has id: " << e.m_id << "\n";
        }
    };
private:
    std::string m_name {};
    IDType m_id {};
    double m_wage {};
public:
    Employee(std::string_view name, IDType id, double wage)
        : m_name { name }
        , m_id { id }
        , m_wage { wage }
    {}

    const std::string& get_name() { return m_name; }
    IDType get_id() { return m_id; }
};

class outer {
public:
    class inner1; // fine, forward definition in an enclosing clsas
    class inner1 {}; // this defines the forward declared type in this enclosing class
    class inner2; // fine, forward definition in an enclosing class
};

class inner2 {}; // here's the definition of the forward declared type, outside the enclosing class

class outer2;
// class outer2::inner; // not allowed because class must be defined before nested types are forward declared
class outer2 {
public:
    class inner {};
};

// class outer2::inner; // this is okay but redundant since type has already been declared in class outer2 { ... } // errors with clangd for some reason

int main() {
    Fruit apple { Fruit::apple };

    if (apple.get_type() == Fruit::apple) {
        std::cout << "I'm an apple\n";
    }
    else {
        std::cout << "I'm not an apple\n";
    }

    Employee john { "John", 1, 45000 };
    Employee::IDType id { john.get_id() };

    std::cout << john.get_name() << " has id: " << id << "\n";

    const Employee jack { "Jack", 2, 60000 };
    const Employee::Printer p {};
    p.print(john);

    return 0;
}