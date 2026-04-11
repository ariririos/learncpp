#include <iostream>

namespace Unspecialized {
    template <typename T, int size> class StaticArray {
    private:
        T m_array[static_cast<std::size_t>(size)] {};

    public:
        T *get_array() { return m_array; }
        const T &operator[](int index) const { return m_array[index]; }
        T &operator[](int index) { return m_array[index]; }
    };

    template <typename T, int size>
    void print(const StaticArray<T, size> &array) {
        for (int count { 0 }; count < size; ++count) {
            std::cout << array[count] << " ";
        }
        std::cout << "\n";
    }
} // namespace Unspecialized

namespace TemplateSpecialization {
    template <typename T, int size> class StaticArray {
    private:
        T m_array[static_cast<std::size_t>(size)] {};

    public:
        T *get_array() { return m_array; }
        const T &operator[](int index) const { return m_array[index]; }
        T &operator[](int index) { return m_array[index]; }
    };

    template <typename T, int size>
    void print(const StaticArray<T, size> &array) {
        for (int count { 0 }; count < size; ++count) {
            std::cout << array[count] << " ";
        }
        std::cout << "\n";
    }

    // override print() for fully specialized StaticArray<char, 14>
    template <> void print(const StaticArray<char, 14> &array) {
        for (int count { 0 }; count < 14; ++count) {
            std::cout << array[count];
        }
        std::cout << "\n";
    }
} // namespace TemplateSpecialization

namespace PartialSpecialization {
    template <typename T, int size> class StaticArray {
    private:
        T m_array[static_cast<std::size_t>(size)] {};

    public:
        T *get_array() { return m_array; }
        const T &operator[](int index) const { return m_array[index]; }
        T &operator[](int index) { return m_array[index]; }
    };

    template <typename T, int size>
    void print(const StaticArray<T, size> &array) {
        for (int count { 0 }; count < size; ++count) {
            std::cout << array[count] << " ";
        }
        std::cout << "\n";
    }

    template <int size> void print(const StaticArray<char, size> &array) {
        for (int count { 0 }; count < size; ++count) {
            std::cout << array[count];
        }
        std::cout << "\n";
    }
} // namespace PartialSpecialization

namespace PartialFunctionSpecialization {
    template <typename T, int size> class StaticArray {
    private:
        T m_array[static_cast<std::size_t>(size)] {};

    public:
        T *get_array() { return m_array; }
        const T &operator[](int index) const { return m_array[index]; }
        T &operator[](int index) { return m_array[index]; }
        void print() const;
    };

    template <typename T, int size> void StaticArray<T, size>::print() const {
        for (int i { 0 }; i < size; ++i) {
            std::cout << m_array[i] << " ";
        }
        std::cout << "\n";
    }

    // won't compile, partial specification of a function isn't allowed:

    // template <int size> void StaticArray<double, size>::print() const {
    //     for (int i { 0 }; i < size; ++i) {
    //         std::cout << std::scientific << m_array[i] << " ";
    //     }
    //     std::cout << "\n";
    // }
} // namespace PartialFunctionSpecialization

namespace PartialClassSpecialization {
    template <typename T, int size> class StaticArray {
    private:
        T m_array[static_cast<std::size_t>(size)] {};

    public:
        T *get_array() { return m_array; }
        const T &operator[](int index) const { return m_array[index]; }
        T &operator[](int index) { return m_array[index]; }
        void print() const;
    };

    template <typename T, int size> void StaticArray<T, size>::print() const {
        for (int i { 0 }; i < size; ++i) {
            std::cout << m_array[i] << " ";
        }
        std::cout << "\n";
    }

    template <int size> class StaticArray<double, size> {
    private:
        double m_array[static_cast<std::size_t>(size)] {};

    public:
        double *get_array() { return m_array; }
        const double &operator[](int index) const { return m_array[index]; }
        double &operator[](int index) { return m_array[index]; }
        void print() const;
    };

    template <int size> void StaticArray<double, size>::print() const {
        for (int i { 0 }; i < size; ++i) {
            std::cout << std::scientific << m_array[i] << " ";
        }
        std::cout << "\n";
    }
} // namespace PartialClassSpecialization

namespace BaseClass {
    template <typename T, int size> class StaticArray_Base {
    protected:
        T m_array[static_cast<std::size_t>(size)] {};

    public:
        T *get_array() { return m_array; }
        const T &operator[](int index) const { return m_array[index]; }
        T &operator[](int index) { return m_array[index]; }
        void print() const {
            for (int i { 0 }; i < size; ++i) {
                std::cout << m_array[i] << " ";
            }
            std::cout << "\n";
        }
    };

    template <typename T, int size>
    class StaticArray : public StaticArray_Base<T, size> {};

    template <int size>
    class StaticArray<double, size> : public StaticArray_Base<double, size> {
    public:
        void print() const {
            for (int i { 0 }; i < size; ++i) {
                std::cout << std::scientific << this->m_array[i] << " ";
                // `this->` is necessary above because the compiler doesn't look up "nondependent" names in "dependent" base classes; where dependency means dependency on the template type T
                // due to this, a bare `m_array` in this context would be considered a global variable
                // `this` is always considered dependent so the compiler will accept it and defer the lookup until the template is actually instantiated, and all base classes are considered
                // another workaround is to insert a `using StaticArray_Base<double, size>::m_array` right before the m_array usage
                // one more possible workaround is to directly use `StaticArray_Base<double, size>::m_array`; but if this were a function call, it could participate in virtual function resolution
                // see https://isocpp.org/wiki/faq/templates#nondependent-name-lookup-members
            }
            std::cout << "\n";
        }
    };
} // namespace BaseClass

int main() {
    Unspecialized::StaticArray<int, 4> int4 {};
    int4[0] = 0;
    int4[1] = 1;
    int4[2] = 2;
    int4[3] = 3;

    Unspecialized::print(int4);

    Unspecialized::StaticArray<char, 14> char14 {};
    constexpr std::string_view hello { "Hello, world!" };
    std::copy_n(hello.begin(), hello.size(), char14.get_array());

    Unspecialized::print(char14); // this prints "H e l l o ,   w o r l d !"

    // to fix this issue for char arrays specifically, we might first try to use template specialization:
    TemplateSpecialization::StaticArray<char, 14> char14_2 {};
    std::copy_n(hello.begin(), hello.size(), char14_2.get_array());

    print(char14_2); // this prints "Hello, world!"
    // but this only works for StaticArray<char, 14>:
    TemplateSpecialization::StaticArray<char, 12> char12 {};
    constexpr std::string_view hello2 { "Hello, mom!" };
    std::copy_n(hello2.begin(), hello2.size(), char12.get_array());

    TemplateSpecialization::print(
        char12); // this prints "H e l l o ,   m o m !"

    // we can solve the problem of needing specializations for every single type-size combination by using partial template specialization, which allows us to specialize classes (but not individual functions!)
    PartialSpecialization::StaticArray<char, 14> char14_3 {};
    std::copy_n(hello.begin(), hello.size(), char14_3.get_array());
    PartialSpecialization::print(char14_3);

    PartialSpecialization::StaticArray<char, 12> char12_2 {};
    std::copy_n(hello2.begin(), hello2.size(), char12_2.get_array());
    PartialSpecialization::print(char12_2);

    // partial template specialization only works with classes, not template functions; the `void print(const StaticArray<char, size> &array)` above works because the print function isn't itself partially specialized -- it's just an overloaded template function that happens to have a partially-specialized class _parameter_

    // we aren't able to create a partially specialized member function, only a partially specialized class (see namespace PartialFunctionSpecialization above)

    // we have to specialize the entire class and then the member function is just a non-specialized member of a partially specialized class
    PartialClassSpecialization::StaticArray<int, 6> int_array {};
    for (int count { 0 }; count < 6; ++count) {
        int_array[count] = count;
    }
    int_array.print();

    PartialClassSpecialization::StaticArray<double, 4> double_array {};
    for (int count { 0 }; count < 4; ++count) {
        double_array[count] = (4.0 + 0.1 * count);
    }
    double_array.print();
    // but this solution duplicates a bunch of code; a better solution is to use inheritance
    // we might try to do this:

    // template <int size>
    // class StaticArray<double, size> : public StaticArray<T, size>

    // but it doesn't make sense, because we can't use T without defining it; even if we could, the only type that makes sense is double, so this class would inherit from itself

    // so we can use a common base class:
    BaseClass::StaticArray<int, 6> int_array2 {};
    for (int count { 0 }; count < 6; ++count) {
        int_array2[count] = count;
    }
    int_array2.print();

    BaseClass::StaticArray<double, 4> double_array2 {};
    for (int count { 0 }; count < 4; ++count) {
        double_array2[count] = (4.0 + 0.1 * count);
    }
    double_array2.print();

    return 0;
}