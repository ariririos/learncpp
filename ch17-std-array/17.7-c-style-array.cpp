#include <algorithm>
#include <iostream>

template <typename T, std::size_t N>
constexpr std::size_t length(const T (&)[N]) noexcept {
    return N;
}

int main() {
    [[maybe_unused]] int test_score
        [30] {}; // define a C-style array with 30 value-initialized ints

    int arr[5];
    arr[1] = 7;
    std::cout << arr[1] << "\n";

    // the index of a C-style array can be a value of any integral type, not just size_t
    const int arr2[] { 9, 8, 7, 6, 5 };
    int s { 2 };
    std::cout << arr2[s] << "\n";
    unsigned int u { 2 };
    std::cout << arr2[u] << "\n";

    // aggregate initialization is allowed:
    [[maybe_unused]] int fibonacci[6] = {
        0, 1, 1, 2, 3, 5
    }; // copy-list initialization
    [[maybe_unused]] int prime[5] { 2, 3, 5, 7,
                                    11 }; // list initialization (preferred)

    [[maybe_unused]] int
        arr3[5]; // members default initialized, int members left uninitialized
    [[maybe_unused]] int arr4
        [5] {}; // members value initialized, int members are zero-initialized (preferred)

    // int a[4] { 1, 2, 3, 4, 5 }; // excess elements in initializer list
    [[maybe_unused]] int b[4] { 1, 2 }; // b[2] and b[3] are value initialized

    // auto squares[5] { 1, 4, 9, 16, 25 }; // won't work, CTAD won't work because C-style arrays aren't templates

    // we can omit the length:
    [[maybe_unused]] const int primes[] { 2, 3, 5, 7, 11 };
    [[maybe_unused]] int bad
        [] {}; // but if we omit the initializers we end up with a zero-length array deduced (avoid!)

    // const and constexpr are fine:
    [[maybe_unused]] constexpr int squares[] { 1, 4, 9, 16, 25 };
    const int primes2[] { 2, 3, 5, 7, 11 };
    // primes2[0] = 17; // won't compile

    // a C-style array has zero overhead:
    std::cout << sizeof(primes2) << "\n"; // 4 * 5 = 20

    // getting length (no .size()):
    std::cout << "size: " << std::size(primes2) << "\n";
    std::cout << "size: " << std::ssize(primes2) << "\n";
    // pre-c++17:
    std::cout << "size: " << length(primes2) << "\n";
    // c-style method:
    std::cout << "size: " << sizeof(primes2) / sizeof(primes2[0]) << "\n";
    //but the C-style method will fail when passed a decayed array (17.8)

    // assignment won't work:
    int arr5[] { 1, 2, 3 };
    arr5[0] = 4;
    // arr5 = { 5, 6, 7 };
    // but element-by-element assignment is fine, as is using std::copy
    int src[] { 5, 6, 7 };
    // copy src into arr
    std::copy(std::begin(src), std::end(src), std::begin(arr5));
    std::cout << arr5[0] << "\n";

    return 0;
}