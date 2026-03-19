int main() {
    // operator overload resolution rules:
    // - if all operands are fundamental types, the compiler will look for a built-in routine, and error if none exists
    // - if any operand is a program-defined type, the compiler will use the same rules as function overloads, including doing implicit conversions, and may involve implicit conversions of program-defined types into fundamental types via an overloaded typecast (covered later in the chapter); if no match or an ambiguous match is found, error

    // any existing operator except for conditional (:?), sizeof, scope (::), member selector (.), pointer member selector (.*), typeid, and the casting operators
    // new operators cannot be created and existing ones cannot be renamed
    // at least one of the operands in an overloaded operator must be a user-defined type, so operator+(int, MyString) is allowed but operator+(int, double) is not
    // this means that something like operator+(double, std::string) is technically allowed since standard library classes are considered user-defined, but remains a bad idea in case the operator is defined in the future
    // it is not possible to change the number of operands to an operator
    // and it is not possible to change the default precedence and associativity of an operator

    // overloaded operators should be as close to the original intent as possible, so defining an operator^ to do exponentiation is a bad idea (and has lower precedence than the arithmetic operators anyway)
    // operators with unclear intentions should be avoided, e.g. operator- on a string class
    // operators should return values in a way consistent with the original operators, e.g. the arithmetic operators should return by value, and prefix increment and assignment should return the leftmost operand by reference
}