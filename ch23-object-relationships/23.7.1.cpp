#include <cassert>
#include <initializer_list>
#include <iostream>

class IntArray {
private:
    int m_length {};
    int *m_data {};

public:
    IntArray() = default;

    IntArray(int length)
        : m_length { length },
          m_data { new int[static_cast<std::size_t>(length)] {} } {}

    IntArray(std::initializer_list<int> list)
        : IntArray(static_cast<int>(list.size())) {
        std::copy(list.begin(), list.end(), m_data);
    }

    ~IntArray() { delete[] m_data; }

    IntArray(const IntArray &) = delete; // to avoid shallow copies
    IntArray &operator=(const IntArray &) = delete;
    IntArray &operator=(std::initializer_list<int> list) {
        if (static_cast<int>(list.size()) > m_length) {
            delete[] m_data;
            m_data = new int[list.size()];
        }
        m_length = static_cast<int>(list.size());

        std::copy(list.begin(), list.end(), m_data);

        return *this;
    }

    int &operator[](int index) {
        assert(index >= 0 && index < m_length);
        return m_data[index];
    }

    int get_length() const { return m_length; }
};

int main() {
    IntArray array { 5, 4, 3, 2, 1 }; // initializer list
    for (int count { 0 }; count < array.get_length(); ++count)
        std::cout << array[count] << ' ';

    std::cout << '\n';

    array = { 1, 3, 5, 7, 9, 11 };

    for (int count { 0 }; count < array.get_length(); ++count)
        std::cout << array[count] << ' ';

    std::cout << '\n';

    array = { 2, 4, 6, 8 };

    for (int count { 0 }; count < array.get_length(); ++count)
        std::cout << array[count] << ' ';

    std::cout << '\n';

    return 0;
}