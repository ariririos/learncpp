#include <iostream>

template <typename T> void print(const T &t) { std::cout << t << "\n"; }

template <typename T> void print2(const T &t) { std::cout << t << "\n"; }

void print2(double d) { std::cout << std::scientific << d << "\n"; }

template <typename T> void print3(const T &t) { std::cout << t << "\n"; }

// this is a full specialization of print<T> for type double
// full specializations aren't implicitly inline, so mark this inline if putting it in a header file
template <> void print3<double>(const double &d) {
    std::cout << std::scientific << d << "\n";
}

template <typename T> class Storage {
private:
    T m_value {};

public:
    Storage(T value) : m_value { value } {}

    void print() { std::cout << m_value << "\n"; }
};

int main() {
    // function templates will all have the same implementation details for any given type
    print(5);
    print(6.7);

    // but sometimes we want a specific type to have a different implementation (e.g. printing doubles in scientific notation)
    print2(5);
    print2(6.7);
    // the non-template function doesn't have to have the same signature as the function template

    // we can also use explicit template specialization to explicitly define different implementations of a template for specific types or values; when all template parameters are specialized, then it is a full specialization, otherwise, it is a partial specialization
    print3(5);
    print3(6.7);
    // the signature of the template specialization must match the primary template
    // if a matching non-template function and a matching template function specialization both exist, the non-template function will take precedence
    // full template specializations aren't implicitly inline and need to be marked inline if placed in a header file; partial template specializations are implicitly inline
    // function template specializations can be deleted using `= delete` to produce a compile error

    // overall, avoid function template specifications in favor of non-template functions whenever possible

    // if we wanted to create specializations for class member functions, function template specialization is the wrong tool; class template specialization is what we're looking for
    Storage i { 5 };
    Storage d { 6.7 };

    i.print();
    d.print();
    // i.print() calls Storage<int>::print() and d.print() calls Storage<double>::print() -- if we want to change the behavior of this function when T is a double, we need to specialize Storage<double>::print(), which is a class template specialization

    return 0;
}