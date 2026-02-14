#include <iostream>

// friend declarations allow another class or function access to private and protected members. they allow a class to grant accessg on a case-by-case basis:
class Accumulator {
private:
    int m_value { 0 };
public:
    void add(int value) { m_value += value; }
    // can declare friend functions outside the class definition:
    friend void print(const Accumulator& acc);
    // or inside, without making it a member function:
    friend void print2(const Accumulator& acc) {
        std::cout << acc.m_value;
    } // this is defined in the same namespace as the class, in this case, globally
};

void print(const Accumulator& acc) {
    // we can access private members of Accumulator without being a member function:
    std::cout << acc.m_value;
}

// a friend function might be preferable when providing functions that can either be called like `a.add(b)` or `add(a, b)`. most prevalent with operator overloading

class Value {
private:
    int m_value {};
public:
    explicit Value(int v): m_value { v } {};
    bool is_equal_to_member(const Value& v) const;
    friend bool is_equal_to_nonmember(const Value& v1, const Value& v2);
};

bool Value::is_equal_to_member(const Value& v) const {
    return m_value == v.m_value;
}

bool is_equal_to_nonmember(const Value& v1, const Value& v2) {
    return v1.m_value == v2.m_value;
}

// a function can be a friend of multiple classes simultaneously:
class Humidity; // forward declaration

class Temperature {
private:
    int m_temp { 0 };
public:
    explicit Temperature(int temp): m_temp { temp } {}
    friend void print_weather(const Temperature& temperature, const Humidity& humidity); // forward declaration needed because of this line
};

class Humidity {
private:
    int m_humidity { 0 };
public:
    explicit Humidity(int humidity): m_humidity { humidity } {}
    friend void print_weather(const Temperature& temperature, const Humidity& humidity);
};

void print_weather(const Temperature& temperature, const Humidity& humidity) {
    std::cout << "The temperature is " << temperature.m_temp << " degrees and the humidity is " << humidity.m_humidity << "%.";
}

int main() {
    Accumulator acc {};
    acc.add(5);
    print(acc);
    std::cout << "\n";
    print2(acc);
    std::cout << "\n";

    Humidity hum { 10 };
    Temperature temp { 12 };
    print_weather(temp, hum); // this makes sense to have as a friend since it doesn't really belong to either class

    // prefer to make a friend function a regular non-member function using only the public interface whenever possible

    return 0;
}