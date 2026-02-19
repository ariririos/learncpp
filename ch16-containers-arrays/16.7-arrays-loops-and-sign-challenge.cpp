#include "16.7-SignedArrayView.h"
#include <cstddef>
#include <iostream>
#include <type_traits>
#include <vector>

template <typename T> void print_reverse(const std::vector<T> &arr) {
    for (std::size_t index { arr.size() - 1 }; index >= 0;
         index--) { // loop will never terminate, `index >= 0` will always be
                    // true // -Wtype-limits
        std::cout << arr[index] << " ";
    }
    std::cout << "\n";
}

template <typename T> void print_reverse2(const std::vector<T> &arr) {
    for (int index { static_cast<int>(arr.size()) - 1 }; index >= 0;
         index--) { // borderline unreadable
        std::cout << arr[static_cast<std::size_t>(index)] << " "; // ridiculous
    }
    std::cout << "\n";
}

template <typename T> void print_templated(const std::vector<T> &arr) {
    // any name that depends on a type containing a template parameter is called
    // a "dependent name" and needs a `typename` to be used as a type
    // std::vector<T> is the type with a template parameter, so
    // std::vector<T>::size_type is the dependent name
    for (typename std::vector<T>::size_type i { 0 }; i < arr.size(); i++) {
    }
}

template <typename T> void print_templated2(const std::vector<T> &arr) {
    // `decltype` returns the type of its parameter
    // this would work if `arr` wasn't a reference:
    // for (decltype(arr)::size_type i { 0 }; i < arr.size(); i++) {}
    // but since it is we have to remove the reference first:
    for (typename std::remove_reference_t<decltype(arr)>::size_type i { 0 };
         i < arr.size(); i++) { // :(((
    }
}

// UZ is the suffix for literals of type std::size_t
template <typename T> constexpr std::size_t toUZ(T value) {
    // make sure T is an integral type
    static_assert(std::is_integral<T>() || std::is_enum<T>());
    return static_cast<std::size_t>(value);
}

int main() {
    std::vector arr { 4, 6, 7, 3, 8, 2, 1, 9 };
    // print_reverse(arr); // infinite loop that prints the array then undefined
    // behavior
    print_reverse2(arr); // this works fine but it's atrocious

    // ways to fix this from worst to best:
    // 1. leave sign conversion warnings off since every array index operation
    // with a signed int will cause a warning => miss warnings for legitimately
    // buggy sign conversions
    // 2. use an unsigned loop variable => fine but shouldn't use the loop
    // variable for anything other than array indexing we could use size_t but
    // in the extremely rare case that the nested typedef size_type isn't
    // defined as size_t, you can use size_type directly:
    for (std::vector<int>::size_type i { 0 }; i < arr.size(); i++) {
    }
    // and when used inside a template requires a `typename` prefix (see
    // print_templated() above)
    // or you can use `decltype` (see print_templated2() above)
    // but unless we're using a custom allocator, size_t is fine
    // 3. use a signed loop variable => more difficult but more consistent with
    // the rest of our code int is probably best unless working with very large
    // arrays, then std::ptrdiff_t is best if it's possible to derive the type
    // of the loop variable from the initializer, we can use auto:
    for (auto i { static_cast<std::ptrdiff_t>(arr.size()) - 1 }; i >= 0; i--) {
    }
    // in c++23, we can use the Z suffix to define a literal of the type that is
    // the signed counterpart to size_t, probably ptrdiff_t:
    for (auto i { 0Z }; i < static_cast<std::ptrdiff_t>(arr.size()); i--) {
    }
    // to get the length of an array as a signed value, two options:
    // pre-c++20, static_cast .size() or std::size() to a signed type:
    for (auto i { static_cast<std::ptrdiff_t>(arr.size()) - 1 }; i >= 0; i--) {
        // std::ignore just discards whatever is assigned to it
        std::ignore = arr[static_cast<std::size_t>(
            i)]; // need to cast back to an unsigned type when indexing
    }
    // c++20 introduces std::ssize():
    for (auto i { std::ssize(arr) - 1 }; i >= 0; i--) {
        std::ignore =
            arr[static_cast<std::size_t>(i)]; // but still need to cast back
    }
    // but converting back to an unsigned index remains a problem; we can keep
    // static_casting every time we index, or we have two other options: a
    // conversion function, or a wrapper class conversion function: (see toUZ()
    // above)
    auto length { std::ssize(
        arr) }; // or pre-c++20 use a static_cast on arr.size()
    for (auto i { length - 1 }; i >= 0; i--) {
        std::ignore = arr[toUZ(i)];
    }
    // wrapper class (custom view): (see 16.7-SignedArrayView.h)
    SignedArrayView sarr { arr };
    for (auto index { sarr.ssize() - 1 }; index >= 0; index--) {
        std::ignore = sarr[index];
    }

    // 4. index the underlying C-style array instead:
    for (auto i { length - 1 }; i >= 0; i--) {
        std::ignore = arr.data()[i]; // C-style arrays can be indexed with
                                     // signed or unsigned types
    }
    // 5. but the best choice is to avoid indexing with integral values altogether
    // range-based for loops (16.8) and iterators (18.2) are good choices here

    return 0;
}