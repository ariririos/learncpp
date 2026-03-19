#include <cassert>
#include <iostream>

class IntArray {
private:
    std::size_t m_size { 0 };
    int *m_array { nullptr };

public:
    explicit IntArray(std::size_t size) : m_size { size } {
        assert(m_size > 0 && "length should be greater than zero");
        m_array = new int[m_size];
    }

    ~IntArray() { delete[] m_array; }

    int &operator[](std::size_t index) {
        assert(
            index < m_size &&
            "index should be greater or equal to than zero and less than size");
        return m_array[index];
    }

    friend std::ostream &operator<<(std::ostream &out, const IntArray &arr) {
        for (std::size_t i { 0 }; i < arr.m_size; i++) {
            out << arr.m_array[i] << " ";
        }
        return out;
    }

    void deep_copy(const IntArray &other) {
        m_size = other.m_size;

        if (other.m_array) {
            m_array = new int[m_size] {};
            std::copy_n(other.m_array, m_size, m_array);
        } else {
            m_array = nullptr;
        }
    }

    IntArray(const IntArray &other) { deep_copy(other); }

    IntArray &operator=(IntArray &other) {

        if (this != &other) {
            delete[] m_array;

            deep_copy(other);
        }

        return *this;
    }
};

IntArray fill_array() {
    IntArray a(5);

    a[0] = 5;
    a[1] = 8;
    a[2] = 2;
    a[3] = 3;
    a[4] = 6;

    return a;
}

int main() {
    IntArray a { fill_array() };

    std::cout << a << '\n';

    auto &ref {
        a
    }; // we're using this reference to avoid compiler self-assignment errors
    a = ref;

    IntArray b(1);
    b = a;

    a[4] = 7;

    std::cout << b << '\n';

    return 0;
}