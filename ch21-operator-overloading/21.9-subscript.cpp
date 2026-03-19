#include <iostream>
// #include <utility>
#include <cassert>

class IntList {
private:
    int m_list[10] {};

public:
    // int &operator[](int index) { return m_list[index]; }
    // const int &operator[](int index) const { return m_list[index]; }

    // int &operator[](int index) {
    //     // std::as_const gives us a const version of `this` (as a reference)
    //     // so we can call the const version of operator[]
    //     // and then use const_cast to discard the const on the returned reference
    //     return const_cast<int &>(std::as_const(*this)[index]);
    // }
    // const int &operator[](int index) const { return m_list[index]; }

    auto &&operator[](this auto &&self, int index) {
        if (!(index >= 0 &&
              static_cast<std::size_t>(index) < std::size(self.m_list))) {
            std::cerr << "Bad index\n";
            std::exit(1);
        }

        return self.m_list[index];
    }
};

class Stupid {
private:
public:
    void operator[](std::string_view index);
};

void Stupid::operator[](std::string_view index) { std::cout << index << "\n"; }

int main() {
    IntList list {};

    // to access the elements of m_list, we could have a function that returns a pointer to the list but the syntax would look something like:
    // list.get_list()[2] = 3;

    // the syntax looks better if we overload operator[]
    list[2] = 3;
    std::cout << list[2] << "\n";

    // operator[] needs to return a reference here because otherwise we wouldn't be able to assign to it

    // we need a separate operator[] for const objects (or there's some other options, see below)
    const IntList clist {};
    std::cout << clist[2] << "\n";

    // to remove duplicate code from const and non-const overloaded operator[] we have two options: one using const_cast and one using an explicit object parameter + auto&& (c++23)
    // it's probably not worth it to deduplicate the code unless there's substantial logic e.g. checking indices for validity; but we normally can't call the non-const version from the const version, and calling the const version from the non-const version returns a const reference when we need a non-const one

    // this is one case where using const_cast is fine because if we're in the non-const overload, we know we're working with a non-const object

    // in c++23, we can use an explicit object parameter (self) and auto&& to differentiate const vs non-const

    // we can also check index validity to make using our operator[] safer than accessing an array directly
    // std::cout << list[10] << "\n"; // this will exit with code 1

    // pointers to objects and overloaded operator[] don't mix -- the compiler will treat operator[] on a pointer to an object as trying to index an array of objects of that type
    IntList *list2 { new IntList {} };
    // list2[2] = 3; // won't work, we're trying to assign an int to an IntList
    (*list2)[2] = 3;
    delete list2;

    // indexes to an overloaded operator[] don't have to be an integral type
    Stupid stupid {};
    stupid["Hello world"];

    return 0;
}