#include <array>
#include <iostream>
#include <iterator>
#include <vector>

int main() {
    // under the hood, range-based for loops use "iterators"
    // iterators are objects that traverse a container and provide access to each element along the way
    // iterators can work in forwards and reverse and work with a variety of container types

    // pointers are the most basic type of iterator:
    std::array arr { 0, 1, 2, 3, 4, 5, 6 };
    auto begin { &arr[0] };
    auto end {
        begin + std::size(arr)
    }; // this couldn't be initialized with `&arr[std::size(arr)]` because this dereferences the element one past the end of the array
    for (auto ptr { begin }; ptr != end; ptr++) {
        std::cout << *ptr << " ";
    }
    std::cout << "\n";

    // the standard library containers provide .begin() and .end():
    auto begin2 { arr.begin() };
    auto end2 { arr.end() };
    for (auto p { begin2 }; p != end2; p++) {
        std::cout << *p << " ";
    }
    std::cout << "\n";
    // std::begin() and std::end() in <iterator> do the same thing (just call the corresponding member functions)

    // we use operator!= instead of operator< because some iterator types do not have a total ordering

    // .begin() and .end() work on C-style arrays as well (defined as arr and arr + N respectively where N is the non-type template parameter containing the length) but not on dynamic or decayed C-style arrays, which lack the length info

    // iterators can become invalidated/dangling if the elements being iterated over change address or are destroyed, e.g. std::vector's .push_back() will invalidate existing iterators
    std::vector v { 0, 1, 2, 3 };
    for (auto num : v) {
        if (num % 2 == 0) {
            v.push_back(
                num + 1); // this invalidates iterators of v, undefined behavior
        }
    }
    for (auto num : v) {
        std::cout << num << " ";
    }
    std::cout << "\n";

    std::vector v2 { 1, 2, 3, 4, 5, 6, 7 };
    auto it { v2.begin() };
    it++; // move to 2nd element
    std::cout << *it << "\n";
    v2.erase(it); // erases the iterator's current element
    // erase() invalidates iterators pointing to the erased element and anything after it, so `it` is now invalidated
    it++;                     // undefined behavior
    std::cout << *it << "\n"; // undefined behavior
    // we can just assign a new iterator to variable to revalidate it; .erase() returns an iterator to the element one past the erased element or .end() if the last element was removed, so we can just use that:
    std::vector v3 { 1, 2, 3, 4, 5, 6, 7 };
    auto it2 { v3.begin() };
    it2++;
    std::cout << *it2 << "\n";
    it2 = v3.erase(it2);
    std::cout << *it2 << "\n";

    return 0;
}