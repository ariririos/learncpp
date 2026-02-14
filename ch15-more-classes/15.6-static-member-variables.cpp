#include <iostream>

struct Something {
    static int s_value;
};

int Something::s_value { 1 }; // static member variables must be initialized outside of their class, like globals

struct Something2 {
    static int s_value;
};

int Something2::s_value { 1 }; // btw: static member variables are zero-initialized if no initializer is provided

class Whatever {
private:
    static int w_value;
public:
    static const int s_value { 4 }; // constant integral types and const enums can be initialized in the class definition
    static inline int t_value { 5 }; // as can inline variables
    static constexpr double u_value { 2.2 }; // constexpr variables are implicitly inline as of c++17
    static constexpr std::string_view s_view { "hello" }; // any class that supports constexpr initialization works
};
int Whatever::w_value { 3 }; // private static variable can be initialized outside of the class definition -- definitions are separate from access controls

class Counter {
private:
    static inline int s_id_generator { 1 };
    int m_id {};
public:
    Counter()
    : m_id { s_id_generator++ }
    {}
    int get_id() const { return m_id; }
};

class Foo {
private:
    // auto m_x { 5 }; // auto not allowed for non-static members
    // std::pair m_v { 1, 2.3 }; // neither is CTAD
    static inline auto s_x { 5 };
    static inline std::pair s_v { 1, 2.3 };
public:
    Foo() {}
};

int main() {
    Something first {};
    Something second {};

    first.s_value = 2;

    // both of these will print 2, s_value is shared
    std::cout << first.s_value << "\n";
    std::cout << second.s_value << "\n";

    // static member variables can be accessed even if no instances of the class are constructed:
    Something2::s_value = 2;
    std::cout << Something::s_value << "\n";

    Counter one {};
    Counter two {};
    Counter three {};
    std::cout << one.get_id() << "\n";
    std::cout << two.get_id() << "\n";
    std::cout << three.get_id() << "\n";

    Foo foo {};

    return 0;
}