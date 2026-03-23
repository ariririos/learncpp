#include <iostream>

class Fraction {
private:
    int m_numerator { 0 };
    int m_denominator { 1 };

public:
    Fraction(int numerator = 0, int denominator = 1)
        : m_numerator { numerator }, m_denominator { denominator } {}

    friend std::ostream &operator<<(std::ostream &out, const Fraction &f) {
        out << f.m_numerator << '/' << f.m_denominator;
        return out;
    }
};

void fun(const int &lref) {
    std::cout << "l-value reference to const: " << lref << "\n";
}

void fun(int &&rref) { std::cout << "r-value reference: " << rref << "\n"; }

int main() {
    /*
    l-value references can only be initialized with modifiable l-values:
    +-------------------------|------------------|-------------+
    | l-value reference       | can init with    | can modify  |
    |-------------------------|------------------|-------------|
    | modifiable l-values     | yes              | yes         |
    | non-modifiable l-values | no               | no          |
    | r-values                | no               | no          |
    +-------------------------|------------------|-------------+
    const l-value references can bind to both modifiable and non-modifiable l-values as well as r-values:
    +----------------------------|------------------|-------------+
    | l-value reference to const | can init with    | can modify  |
    |----------------------------|------------------|-------------|
    | modifiable l-values        | yes              | yes         |
    | non-modifiable l-values    | yes              | no          |
    | r-values                   | yes              | no          |
    +----------------------------|------------------|-------------+
    */
    // c++11 adds r-value references:
    int x { 5 };
    [[maybe_unused]] int &lref { x };
    [[maybe_unused]] int &&rref { 5 };
    /*
    r-value references cannot be initialized with lvalues:
    +-------------------------|------------------|-------------+
    | r-value reference       | can init with    | can modify  |
    |-------------------------|------------------|-------------|
    | modifiable l-values     | no               | no          |
    | non-modifiable l-values | no               | no          |
    | r-values                | yes              | yes         |
    +-------------------------|------------------|-------------+
    r-value references to const:
    +----------------------------|------------------|-------------+
    | r-value reference to const | can init with    | can modify  |
    |----------------------------|------------------|-------------|
    | modifiable l-values        | no               | no          |
    | non-modifiable l-values    | no               | no          |
    | r-values                   | yes              | no          |
    +----------------------------|------------------|-------------+
    */

    // r-value references extend the lifespan of the object they're initialized with to the lifespan of the r-value reference (same as an l-value reference to const)
    // non-const r-value references allow you to modify the rvalue
    auto &&rref2 { Fraction { 3, 5 } };
    std::cout
        << rref2
        << "\n"; // the parameter to operator<< binds to the temporary so no copies are made

    int &&rref3 { 5 }; // temporary with value 5 created here
    rref3 = 10;
    std::cout << rref3 << "\n";

    // but the main use of r-value references isn't like these two examples, but as function parameters
    int y { 5 };
    fun(y); // l-value overload called
    fun(5); // r-value overload called

    // r-value reference variables are l-values:
    int &&rref4 { 5 };
    fun(rref4); // l-value overload called
    // the *type* of rref4 is int&&, an r-value reference, but when used in an expression, its *value category* is l-value
    return 0;
}