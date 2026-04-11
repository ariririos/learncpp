#include <iostream>
#include <memory>
#include <type_traits>

namespace DoubleSpecialization {
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
} // namespace DoubleSpecialization

namespace PointerSpecialization {
    template <typename T> class Storage {
    private:
        T m_value {};

    public:
        Storage(T value) : m_value { value } {}

        void print() { std::cout << m_value << "\n"; }
    };

    template <typename T> class Storage<T *> {
    private:
        T *m_value {};

    public:
        Storage(T *value) : m_value { value } {}

        void print();
    };

    // this could've been part of the class definition if we wanted
    template <typename T> void Storage<T *>::print() {
        if (m_value) {
            std::cout << std::scientific << *m_value << "\n";
        }
    }
} // namespace PointerSpecialization

namespace NoPointerSpecialization {
    template <typename T> class Storage {
        static_assert(!std::is_pointer_v<T> && !std::is_null_pointer_v<T>,
                      "Storage<T*> and Storage<nullptr> disallowed");

    private:
        T m_value {};

    public:
        Storage(T value) : m_value { value } {}

        void print() { std::cout << m_value << "\n"; }
    };
} // namespace NoPointerSpecialization

namespace HeapAllocation {
    template <typename T> class Storage {
        static_assert(!std::is_pointer_v<T> && !std::is_null_pointer_v<T>,
                      "Storage<T*> and Storage<nullptr> disallowed");

    private:
        T m_value {};

    public:
        Storage(T value) : m_value { value } {}

        void print() { std::cout << m_value << "\n"; }
    };

    template <typename T> class Storage<T *> {
    private:
        std::unique_ptr<T>
            m_value {}; // use std::unique_ptr to handle the object lifetime

    public:
        Storage(T *value)
            : m_value { std::make_unique<T>(value ? *value : 0) } {
        } // this throws an exception if there's no value

        void print() { std::cout << *m_value << "\n"; }
    };
} // namespace HeapAllocation

int main() {
    DoubleSpecialization::Storage i { 5 };
    DoubleSpecialization::Storage d { 6.7 };

    i.print();
    d.print();

    // our current Storage malfunctions when using a pointer however:
    double e { 1.2 };
    double *ptr { &e };

    DoubleSpecialization::Storage s { ptr };
    s.print(); // prints a memory address

    // we could create a specialization for double* which dereferences m_value in the print() function but then we'd have to create a specialization for each pointer type; and even then we could never cover every possible type, since users can pass program-defined type pointers

    // instead we create a specialization of the class (we still use `template <typename T>`) and use T* wherever we need a pointer to T; then we create a partial specialization Storage<T*> after defining Storage<T>

    double f { 1.2 };
    double *ptr2 { &f };
    PointerSpecialization::Storage t { ptr2 };
    t.print(); // prints 1.200000e+00

    // Storage<T*> can be left dangling if the object it's pointing to is destroyed before the Storage<T*> object is
    // this is basically due to the fact that Storage<T> has copy semantics (it makes a copy of its initializer) but Storage<T*> has reference semantics (it's a reference to its initializer)
    // we can deal with this inconsistency a couple ways:
    // - make it clear to users of the class that Storage<T*> is a view class with reference semantics, so it's on the caller to keep the referenced object valid as long as the Storage<T*>; we can't change the name of the class to something like StorageView to reflect this unfortunately
    // - prevent use of Storage<T*> altogether, since the caller can just dereference T and put it into a regular Storage<T>, making a copy
    // as of c++23, there's no way to delete a class (unlike deleting a function), so the best option is to static_assert in the Storage<T> that T isn't a pointer or std::nullptr_t (which doesn't count as a pointer type)
    double g { 1.2 };
    NoPointerSpecialization::Storage s1 { g };
    s1.print();
    // now these two won't compile:
    // NoPointerSpecialization::Storage s2 { &d };
    // s2.print();
    // NoPointerSpecialization::Storage s3 { nullptr };
    // s3.print();

    // alternatively we can have Storage<T*> make a copy of the object on the heap and use std::unique_ptr to handle the memory (otherwise we'd have to overload the constructor, copy constructor, copy assignment, and destructor)
    double h { 1.2 };
    HeapAllocation::Storage s4 { h };
    s4.print();
    HeapAllocation::Storage s5 { &h };
    s5.print();

    return 0;
}