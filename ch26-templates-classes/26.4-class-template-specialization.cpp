#include <ios>
#include <iostream>

namespace Nonspecialized {
    template <typename T> class Storage8 {
    private:
        T m_array[8];

    public:
        void set(int index, const T &value) { m_array[index] = value; }

        const T &get(int index) const { return m_array[index]; }
    };

} // namespace Nonspecialized

namespace Specialized {
    template <typename T> class Storage8 {
    private:
        T m_array[8];

    public:
        void set(int index, const T &value) { m_array[index] = value; }

        const T &get(int index) const { return m_array[index]; }
    };

    template <> class Storage8<bool> {
    private:
        std::uint8_t m_data;

    public:
        void set(int index, bool value) {
            auto mask {
                1 << index
            }; // this puts a 1 into the bit we're interested in turning on/off
            if (value) {                              // if we're setting a bit
                m_data |= static_cast<uint8_t>(mask); // turn that bit on
            } else { // if we're turning a bit off
                m_data &= ~static_cast<uint8_t>(mask); // turn that bit off
            }
        }

        bool get(int index) {
            auto mask { 1 << index };
            return (
                m_data &
                mask); // gets the bit we're looking for and implicitly casts it to bool
        }
    };
} // namespace Specialized

namespace Duplication {
    template <typename T> class Storage {
    private:
        T m_value {};

    public:
        Storage(T value) : m_value { value } {}

        void print() { std::cout << m_value << "\n"; }
    };

    template <> class Storage<double> {
    private:
        double m_value {};

    public:
        Storage(double value) : m_value { value } {}

        void print();
    };

    void Storage<double>::print() {
        std::cout << std::scientific << m_value << "\n";
    }
} // namespace Duplication

namespace Deduplication {
    template <typename T> class Storage {
    private:
        T m_value {};

    public:
        Storage(T value) : m_value { value } {}

        void print() { std::cout << m_value << "\n"; }
    };

    template <> void Storage<double>::print() {
        std::cout << std::scientific << m_value << "\n";
    }
} // namespace Deduplication

int main() {
    Nonspecialized::Storage8<int> int_storage {};

    for (int count { 0 }; count < 8; ++count) {
        int_storage.set(count, count);
    }

    for (int count { 0 }; count < 8; ++count) {
        std::cout << int_storage.get(count) << "\n";
    }

    Nonspecialized::Storage8<bool> bool_storage;

    std::cout << std::boolalpha;
    for (int count { 0 }; count < 8; ++count) {
        std::cout << bool_storage.get(count) << "\n";
    }

    // Storage8<bool> wastes a ton of space -- only one bit is needed to actually store the bool, and Storage8<bool> contains 8 bools, so there's only one byte of actual information and seven bytes of wasted space
    // we can use class template specialization to create a different implementation for Storage8<bool> instead of using a completely different class with a different name

    // class template specializations are treated as completely independent classes even though they're instantiated in the same way as the templated class; we can change the way it's implemented and even the functions it makes public

    Specialized::Storage8<int> int_storage2 {};

    for (int count { 0 }; count < 8; ++count) {
        int_storage2.set(count, count);
    }

    for (int count { 0 }; count < 8; ++count) {
        std::cout << int_storage2.get(count) << "\n";
    }

    Specialized::Storage8<bool> bool_storage2;

    std::cout << std::boolalpha;
    for (int count { 0 }; count < 8; ++count) {
        std::cout << bool_storage2.get(count) << "\n";
    }

    // when specializing a class member function, one way we can do it is to specialize the class and change the member function definition (we kept it outside of the class but we could've put it inside the class definition)
    Duplication::Storage i { 5 };
    Duplication::Storage d { 6.7 };

    i.print();
    d.print();

    // but we can specialize just Storage<double>::print() without specializing the rest of Storage<double> (the compiler will implicitly specialize the rest of Storage<double>):
    Deduplication::Storage i2 { 5 };
    Deduplication::Storage d2 { 6.7 };
    // explicit function specializations aren't implicitly inline (see 26.3), so we need to make it inline if putting it in a header file

    i2.print();
    d2.print();

    // if the compiler can only see the definition of the non-specialized class, it will use that instead of the specialization; for this reason, a single header file usually includes both the non-specialized class and any specializations so they can always be seen together
    // if a specialization is only required in a single translation unit, we can define it only in the source file for that translation unit; other translation units won't be able to see the specialization and will continue to use the non-specialized version
    // be wary of putting a specialization in a header file, because if we forget to include the header file then we'll use the non-specialized version; if we intended to use the non-specialized version, but a header file we included transitively includes the specialization, we'll use the specialization anyway
}