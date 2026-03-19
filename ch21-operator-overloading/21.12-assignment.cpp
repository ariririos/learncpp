#include "../print.h"
#include <algorithm>
#include <cassert>

class Fraction {
private:
    int m_numerator { 0 };
    int m_denominator { 1 };

public:
    // default constructor
    Fraction(int numerator = 0, int denominator = 1)
        : m_numerator { numerator }, m_denominator { denominator } {
        assert(denominator != 0);
    }
    // copy constructor
    Fraction(const Fraction &copy)
        : m_numerator { copy.m_numerator },
          m_denominator { copy.m_denominator } {
        // we don't need to check denominator != 0 here because copy is already a valid Fraction
        std::cout << "Copy constructor called\n";
    }
    Fraction &operator=(const Fraction &fraction);
    friend std::ostream &operator<<(std::ostream &out, const Fraction &f1);
};

std::ostream &operator<<(std::ostream &out, const Fraction &f1) {
    out << f1.m_numerator << "/" << f1.m_denominator;
    return out;
}

// a first implementation with self-assignment problems
Fraction &Fraction::operator=(const Fraction &fraction) {
    // copy
    m_numerator = fraction.m_numerator;
    m_denominator = fraction.m_denominator;
    // allow chaining
    return *this;
}

class MyString {
private:
    char *m_data {};
    int m_length {};

public:
    MyString(const char *data = nullptr, int length = 0)
        : m_length { std::max(length, 0) } {
        if (length) {
            m_data = new char[static_cast<std::size_t>(length)];
            std::copy_n(data, length,
                        m_data); // copy `length` elements of data into m_data
        }
    }
    ~MyString() { delete[] m_data; }
    MyString(const MyString &) =
        default; // avoids a warning about pointer members but no copy constructor
    MyString &operator=(const MyString &str);
    friend std::ostream &operator<<(std::ostream &out, const MyString &s);
};

std::ostream &operator<<(std::ostream &out, const MyString &s) {
    out << s.m_data;
    return out;
}

// flawed implementation of operator=
MyString &MyString::operator=(const MyString &str) {
    // deallocate existing backing data
    if (m_data)
        delete[] m_data;
    m_length = str.m_length;
    m_data = nullptr;

    if (m_length) {
        m_data = new char[static_cast<std::size_t>(str.m_length)];
    }
    // copy new string data over from still valid str
    std::copy_n(str.m_data, m_length, m_data);
    return *this;
}

class MyString2 {
private:
    char *m_data {};
    int m_length {};

public:
    MyString2(const char *data = nullptr, int length = 0)
        : m_length { std::max(length, 0) } {
        if (length) {
            m_data = new char[static_cast<std::size_t>(length)];
            std::copy_n(data, length,
                        m_data); // copy `length` elements of data into m_data
        }
    }
    ~MyString2() { delete[] m_data; }
    MyString2(const MyString2 &) =
        default; // avoids a warning about pointer members but no copy constructor
    MyString2 &operator=(const MyString2 &str);
    friend std::ostream &operator<<(std::ostream &out, const MyString2 &s);
};

std::ostream &operator<<(std::ostream &out, const MyString2 &s) {
    out << s.m_data;
    return out;
}

MyString2 &MyString2::operator=(const MyString2 &str) {
    if (this == &str) {
        return *this;
    }
    // deallocate existing backing data
    if (m_data)
        delete[] m_data;
    m_length = str.m_length;
    m_data = nullptr;

    if (m_length) {
        m_data = new char[static_cast<std::size_t>(str.m_length)];
    }
    // copy new string data over from still valid str
    std::copy_n(str.m_data, m_length, m_data);
    return *this;
}

class MyString3 {
private:
    // flipped these two declarations to allow the copy constructor below to use m_length in the initialization of m_data
    int m_length {};
    char *m_data {};

public:
    MyString3(const char *data = nullptr, int length = 0)
        : m_length { std::max(length, 0) } {
        if (length) {
            m_data = new char[static_cast<std::size_t>(length)];
            std::copy_n(data, length,
                        m_data); // copy `length` elements of data into m_data
        }
    }
    ~MyString3() { delete[] m_data; }
    MyString3(const MyString3 &s)
        : m_length { s.m_length },
          m_data { m_length ? new char[static_cast<std::size_t>(m_length)]
                            : nullptr } {
        std::copy_n(s.m_data, s.m_length, m_data);
    }
    MyString3 &operator=(MyString3 str);
    friend std::ostream &operator<<(std::ostream &out, const MyString3 &s);
    friend void swap(MyString3 &s1, MyString3 &s2);
};

void swap(MyString3 &s1, MyString3 &s2) {
    std::swap(s1.m_length, s2.m_length);
    std::swap(s1.m_data, s2.m_data);
}

std::ostream &operator<<(std::ostream &out, const MyString3 &s) {
    out << s.m_data;
    return out;
}

MyString3 &MyString3::operator=(MyString3 str) {
    swap(*this, str);

    return *this;
}

int main() {
    // operator= is the copy assignment operator and copies values from one object to another already existing object
    // (move assignment also exists, covered in 22.3)

    // the copy constructor does something similar, but creates a new object, and is used when a new object is required, such as when passing or returning objects by value
    // the copy assignment operator is used when a new object is not required

    // operator= must be overloaded as a member function
    Fraction five_thirds { 5, 3 };
    Fraction f;
    f = five_thirds;
    print(f);

    // chaining allowed:
    Fraction f1 { 5, 3 };
    Fraction f2 { 7, 2 };
    Fraction f3 { 9, 5 };
    f1 = f2 = f3;
    print(f1);
    print(f2);
    print(f3); // all 9/5

    // self-assignment is allowed:
    f1 = f1;
    print(f1); // 9/5
    // in this case it's fine and just wastes time, but when dealing with dynamically allocated memory it can cause problems

    // for example:
    MyString alex("Alex", 5);
    MyString employee;
    employee = alex;
    print(employee);
    // but if we do:
    alex = alex;
    print(alex); // prints garbage
    // this happens because when self-assigning, *this and str are the same object, so the delete[] m_data in our implementation also deletes the implicit object and leaves m_data and str.m_data dangling
    // so when we allocate new memory and copy into it from this deallocated memory, we get garbage

    // handling this problem is as simple as checking whether `this == &str` and returning *this if so (i.e. checking if the addresses of the implicit object and the parameter are the same)
    MyString2 alex2("Alex", 5);
    alex2 = alex2;
    print(alex2); // fine
    // self-assignment checks aren't needed for copy constructors because the object being copy constructed is newly created, so the only time you'd encounter self-assignment is if initializing a newly defined object with itself:
    // MyString c { c }; // but the compiler should warn about c being uninitialized here
    // they're also not needed for classes like Fraction where self-assignment doesn't pose a problem

    // aside: copy and swap idiom
    // our current implementation of operator= basically duplicates the work of the copy constructor (which needs to be implemented correctly, not just defaulted) and could be simplified by passing by value (to create a copy) and doing a swap between *this and the pass-by-value parameter
    // if swap is implemented well, it becomes only a couple pointer swaps and the self-assignment check becomes unnecessary
    MyString3 alex3("Alex", 5);
    MyString3 employee3;
    employee3 = alex3;
    print(employee3);
    alex3 = alex3;
    print(alex3);

    // unlike other operators, the compiler will provide a default for operator=, the implicit public copy assignment operator, which does memberwise assignment
    // you can delete this implicit operator= or make it private like any other operator
    // the compiler will delete it for you if any data members are const, since they can't be assigned, so it will assume the class isn't assignable; you'll have to manually implement it and assign each non-const member if you want an operator=

    return 0;
}