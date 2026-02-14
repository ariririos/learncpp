#include <ios>
#include <iostream>

template <typename T> class Pair {
private:
    T m_first {};
    T m_second {};

public:
    // inside the class definition, this is the same T as above
    Pair(const T &first, const T &second)
        : m_first { first }, m_second { second } {}

    bool is_equal(const Pair<T> &pair);
};

// a member function definition outside the class definition requires
// resupplying the template parameter declaration
template <typename T>
// the Pair type for the pair parameter doesn't need `<T>` because the fully
// templated name is "injected" in the scope of a class
bool Pair<T>::is_equal(const Pair &pair) {
    return m_first == pair.m_first && m_second == pair.m_second;
}

// if this were in a header file, the template member functions should be
// defined immediately below the class definition to be visible anywhere the
// class is visible those template member functions will be implicitly inline
// (like any other functions implicitly instantiated from templates) and not
// cause ODR violations

int main() {
    Pair p1 { 5, 6 };
    std::cout << std::boolalpha
              << "is_equal(5, 6): " << p1.is_equal(Pair { 5, 6 }) << "\n";
    std::cout << std::boolalpha
              << "is_equal(5, 7): " << p1.is_equal(Pair { 5, 7 }) << "\n";

    return 0;
}