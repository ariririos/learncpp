#include <cassert> // for assert()
#include <initializer_list>
#include <iostream>
#include <vector>

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

    // IntArray(const IntArray &) = delete; // to avoid shallow copies
    // IntArray &
    // operator=(const IntArray &list) = delete; // to avoid shallow copies

    int &operator[](int index) {
        assert(index >= 0 && index < m_length);
        return m_data[index];
    }

    int get_length() const { return m_length; }
};

int main() {
    // we can't initialize our IntArray from the previous lesson with an initializer array:
    // IntArray array { 5, 4, 3, 2, 1 }; // won't compile without changes

    // we need a constructor that takes a std::initializer_list (<initializer_list>) to be able to do that; it takes a template type parameter unless you can CTAD it (not in function parameters)
    // .size() gives you the number of elements in the list
    // it's usually passed by value because it's a view; copying it doesn't copy the elements in the list
    IntArray array { 5, 4, 3, 2, 1 };

    for (int count { 0 }; count < 5; ++count) {
        std::cout << array[count] << ' ';
    }

    // std::initializer_list doesn't have an operator[] to access elements of the list, but we can use either a range-based for loop or .begin() to get an iterator; the iterator can be indexed:
    // (given std::initializer_list<int> list)
    // for (std::size_t count {}; count < list.size(); ++count) {
    //      m_data[count] = list.begin()[count]
    // }

    // list initialization prefers list constructors over non-list constructors:
    IntArray a1(5); // IntArray(int), allocates an array of size 5
    IntArray a2 {
        5
    }; // IntArray(std::initializer_list<int>), allocates an array of size 1

    // this is the reason the list constructor above is written using direct initialization:
    // IntArray(std::initializer_list<int> list)
    // : IntArray(static_cast<int>(list.size()))
    // otherwise it would delegate to itself, which won't compile

    // this is the same reason std::vector and other container classes can have both a list constructor and a constructor with a parameter with the same type:
    std::vector<int> array1(5);
    std::vector<int> array2 { 5 };

    // adding list constructors to an existing class can be dangerous; consider a class like:
    class Foo {
    public:
        Foo(int, int) { std::cout << "Foo(int, int)\n"; }
    };

    Foo f1 { 1, 2 };
    // if we then add a list initializer then the meaning of the line above changes:
    class Foo2 {
    public:
        Foo2(int, int) { std::cout << "Foo(int, int)\n"; }
        Foo2(std::initializer_list<int>) {
            std::cout << "Foo(std::initializer_list<int>)\n";
        }
    };

    Foo2 f2 { 1, 2 }; // this now calls the list constructor

    // we can also use operator= to assign new values to a class using an initializer list

    // if we have a list constructor, we should have at least one of:
    // - an overloaded list assignment operator
    // - a deep-copying copy assignment operator
    // - a deleted copy assignment operator

    // if we fail to do any of these, when we do a list assignment to an existing object, the compiler will run through these steps:
    // - an assignment function taking a std::initializer_list doesn't exist, so it'll look for other assignment functions
    // - the implicit copy assignment operator exists but it will only work if the initializer list is convertible to an IntArray
    // - a temporary IntArray is created using the list constructor
    // - the implicit assignment operator will shallow copy the temporary into our array object
    // - at this point the temporary's m_data and our existing object's m_data point at the same address
    // - the temporary goes out of scope and is destroyed, ~IntArray() runs, the temporary's m_data is deallocated, and our object's m_data is dangling
    // - and finally anytime we try to use array3->m_data, including in the destructor, we get undefined behavior
    // for example:
    /*
    IntArray array3 {};
    array3 = { 1, 3, 5, 7, 9, 11 };

    for (int count { 0 }; count < 5; ++count) {
        std::cout << array3[count] << ' ';
    }
    */

    return 0;
}