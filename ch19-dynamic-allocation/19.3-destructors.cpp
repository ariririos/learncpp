#include <cassert>
#include <cstddef>
#include <iostream>

// Destructors can be used to manage dynamic memory resources
class IntArray {
private:
    int *m_array {};
    int m_size {};

public:
    IntArray(int length) {
        assert(length > 0);
        m_array = new int[static_cast<std::size_t>(length)] {};
        m_size = length;
    }
    ~IntArray() { delete[] m_array; }
    // these two avoid a -Weffc++ warning
    IntArray(const IntArray &) = delete;
    IntArray &operator=(const IntArray &) = delete;
    void set_value(int index, int value) { m_array[index] = value; }
    int get_value(int index) { return m_array[index]; }
    int get_length() { return m_size; }
};

class Simple {
private:
    int m_n_id {};

public:
    Simple(int n_id) : m_n_id { n_id } {
        std::cout << "Constructing Simple " << n_id << "\n";
    }
    ~Simple() { std::cout << "Destructing Simple " << m_n_id << "\n"; }
    int get_id() { return m_n_id; }
};

int main() {
    IntArray ar(
        10); // we use direct initialization here to stay consistent with other containers when initializing with a length rather than an initializer list
    for (int count { 0 }; count < ar.get_length(); count++) {
        ar.set_value(count, count + 1);
    }
    std::cout << "The value of element 5 is " << ar.get_value(5) << "\n";

    // allocating a Simple on the stack
    Simple simple { 1 };
    std::cout << simple.get_id() << "\n";

    // allocating a Simple dynamically
    Simple *p_simple { new Simple { 2 } };
    std::cout << p_simple->get_id() << "\n";

    delete p_simple; // Simple 2 destructor runs here

    // RAII (Resource Acquisition is Initialization) means tying resource use to the lifetime of objects with automatic duration; we implement this using constructors and destructors
    // IntArray implements RAII, as do std::string and std::vector
    // but if std::exit is used, destructors will not be called!

    return 0;
}