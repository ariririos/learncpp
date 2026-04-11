#include <iostream>

template <typename T, long unsigned int size> class StaticArray {
private:
    T m_array[size] {};

public:
    T *get_array();
    T &operator[](int index) { return m_array[index]; }
};

template <typename T, long unsigned int size>
T *StaticArray<T, size>::get_array() {
    return m_array;
}

int main() {
    // a template non-type parameter is a template parameter where the type of the parameter is predefined and the actual parameter is substituted for a constexpr value passed in as an argument
    // they can be any of: an integral type, an enum, pointer/reference to a class object, pointer/reference to a function, pointer/reference to a class member function, std::nullptr_t, and (since c++20) a floating point type
    StaticArray<int, 12> int_array;
    for (int count { 0 }; count < 12; ++count) {
        int_array[count] = count;
    }

    for (int count { 11 }; count >= 0; --count) {
        std::cout << int_array[count] << " ";
    }
    std::cout << "\n";

    StaticArray<double, 4> double_array;
    for (int count { 0 }; count < 4; ++count) {
        double_array[count] = 4.4 + 0.1 * count;
    }

    for (int count { 0 }; count < 4; ++count) {
        std::cout << double_array[count] << " ";
    }
    std::cout << "\n";

    // StaticArray allows us to not have to dynamically allocate the m_array member variable -- the size must be constexpr so the compiler will be able to figure out the array to allocate statically
    // this is exactly what std::array does
    return 0;
}