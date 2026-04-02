#include <iostream>
#include <string>

class Person {
private:
    std::string m_name {};
    int m_age {};

public:
    Person(std::string_view name, int age) : m_name { name }, m_age { age } {}
    const std::string &get_name() const { return m_name; }
    int get_age() const { return m_age; }
};

class Employee {
private:
    std::string m_employer {};
    double m_wage {};

public:
    Employee(std::string_view employer, double wage)
        : m_employer { employer }, m_wage { wage } {}
    const std::string &get_employer() const { return m_employer; }
    double get_wage() const { return m_wage; }
};

// Teacher publicly inherits from Person and Employee
class Teacher : public Person, public Employee {
private:
    int m_teaches_grade {};

public:
    Teacher(std::string_view name, int age, std::string_view employer,
            double wage, int teaches_grade)
        : Person { name, age }, Employee { employer, wage },
          m_teaches_grade { teaches_grade } {}
};

struct Point2D {
    int x {};
    int y {};
};

class Box { // mixin
public:
    void set_top_left(Point2D point) { m_top_left = point; }
    void set_bottom_right(Point2D point) { m_bottom_right = point; }

private:
    Point2D m_top_left {};
    Point2D m_bottom_right {};
};

class Label { // mixin
public:
    void set_text(const std::string_view str) { m_text = str; }
    void set_font_size(int font_size) { m_font_size = font_size; }

private:
    std::string m_text {};
    int m_font_size {};
};

class Tooltip { // mixin
public:
    void set_text(const std::string_view str) { m_text = str; }

private:
    std::string m_text {};
};

class Button : public Box, public Label, public Tooltip {};

class USBDevice {
private:
    long m_id {};

public:
    USBDevice(long id) : m_id { id } {}
    long get_id() const { return m_id; }
};

class NetworkDevice {
private:
    long m_id {};

public:
    NetworkDevice(long id) : m_id { id } {}
    long get_id() const { return m_id; }
};

class WirelessAdapter : public USBDevice, public NetworkDevice {
public:
    WirelessAdapter(long usb_id, long network_id)
        : USBDevice { usb_id }, NetworkDevice { network_id } {}
};

class PoweredDevice {};

class Scanner : public PoweredDevice {};

class Printer : public PoweredDevice {};

class Copier : public Scanner, public Printer {};

int main() {
    // c++ allows a class to inherit from multiple other classes
    Teacher t { "Mary", 45, "Boo", 14.3, 8 };

    // mixins are small classes meant to be inherited from to add properties to another class rather than instantiated on its own
    // for example we inherit from Box, Label, and Tooltip to create a new Button class
    Button button {};
    button.Box::set_top_left({ 1, 1 });
    button.Box::set_bottom_right({ 10, 10 });
    button.Label::set_text("Submit");
    button.Label::set_font_size(6);
    button.Tooltip::set_text("Submit the form to the server");
    // we use explicit Box::, Label::, and Tooltip:: here for a few reasons:
    // - we can't call button.set_text() directly because it's ambiguous (present in both Label and Tooltip)
    // - even if not ambiguous, the scope prefix documents which mixin we're referring to
    // - guards against future ambiguous calls if we inherit from more mixins with overlapping member names

    // aside: mixins typically don't use virtual functions because they're designed to add functionality, not to serve as an interface -- mixins are often templated so they can be customized to work in a particular way
    // a derived class can inherit from a mixin base class using the derived class as a template type parameter -- this is the Curiously Recurring Template Pattern (CRTP):
    /*
    template <typename T>
    class Mixin {
        // Mixin<T> can use template type parameter T
        // to access members of Derived via
        // static_cast<T*>(this)
    }

    class Derived: public Mixin<Derived> {};
    */
    // the CRTP allows implementing compile-time polymorphism -- providing an interface to a class where function calls are resolved at compile time rather than at runtime like virtual functions
    // for example:
    /*
    template <typename T>
    class Amount {
    public:
        double get_value() const {
            return static_cast<T const&>(*this).get_value();
        }
    }
    
    // say we have two implementations for this interface: one always returning a constant, and one where the value can be customized
    class Constant42: public Amount<Constant42> {
    public:
        double get_value() const { return 42; }
    };

    class Variable: public Amount<Variable> {
    public:
        explicit Variable(int value): m_value { value } {}
        double get_value() const { return m_value; }
    private:
        int m_value {};
    };

    // and a client for the interface:
    template<typename T>
    void print(Amount<T> const& amount) {
        std::cout << amount.get_value() << "\n";
    }

    // and this function can be called with either implementation:
    Constant42 c42;
    print(c42); // prints 42
    Variable v { 43 };
    print(v); // prints 43

    // what we've done is used Amount polymorphically but without any virtual functions, eliminating the runtime cost of virtual funcction dispatch

    // but this approach will be superseded by concepts which don't require inheriting from the interface but still specify requirements on types
    */

    // multiple inheritance presents several problems
    // first, we can get ambiguous functions calls when multiple base classes provide functions with the same name
    [[maybe_unused]] WirelessAdapter c54G { 5442, 181742 };
    // std::cout << c54G.get_id(); // won't work, ambiguous
    std::cout << c54G.USBDevice::get_id() << "\n"; // this is fine though

    // second, and more seriously, is the diamond problem, where a class multiply inherits from two classes which themselves inherit from a single base class
    [[maybe_unused]] Copier copier {};
    // we have to resolve whether Copier has one or two copies of PoweredDevice, and certain types of ambiguous references; we can address most of these issues through explicit scoping; see 25.8 for more info

    // **avoid multiple inheritance unless alternatives lead to more complexity**
    return 0;
}