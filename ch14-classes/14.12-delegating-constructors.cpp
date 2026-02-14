#include <iostream>
#include <string>
#include <string_view>

class Employee {
private:
    static constexpr int default_id {
        0
    }; // to not have to repeat ourselves in the default member initializer and
       // the default argument for the constructor
    std::string m_name { "???" };
    int m_id { default_id };
    bool m_is_manager { false };

public:
    Employee(std::string_view name)
        : Employee { name, default_id }
    // delegate initialization to Employee(std::string_view, int) constructor
    // can't do any member initialization here
    {
        /* if instead of delegating the constructor, we were to do
         * `Employee(name, id)` here, it would create and direct-initialize a
         * temporary object with the given arguments, which would print out the
         * message below, but have no effect on *this* object, which would keep
         * the default values from above
         */
        // control returns to this block after the delegated constructor runs
        std::cout << "Back to original from delegated constructor\n";
    }

    Employee(std::string_view name, int id) : m_name { name }, m_id { id } {
        std::cout << "Employee " << m_name << " created\n";
    }

    /* aside from the print statements, these two constructors could be combined
     * using a default argument like: */
    //   Employee(std::string_view name, int id = 0)
    //     : m_name { name }, m_id { id }
    //   {}
};

int main() {
    Employee james { "James" };
    Employee dave { "Dave", 42 };
}