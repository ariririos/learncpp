#include <iostream>
#include <vector>

int main() {
    std::vector<int> empty {};

    std::vector<int> primes {
        2, 3, 5, 7, 11
    }; // list construction uses the list constructor
    std::vector vowels { 'a', 'e', 'i', 'o',
                         'u' }; // uses CTAD to deduce element type char

    // container types usually have a special "list constructor" that:
    // - allocates enough memory for the initialization values, if needed
    // - sets the length of the container to the number of elements in the
    // initializer, if needed
    // - initializes the elements to the values in the initializer list, in
    // sequential order a list constructor takes a std::initializer_list
    // (see 23.7)
    std::cout << "The first prime number is: " << primes[0] << "\n";
    std::cout << "The second prime number is: " << primes[1] << "\n";
    std::cout << "Sum of the first 5 primes is: "
              << primes[0] + primes[1] + primes[2] + primes[3] + primes[4]
              << "\n";
    // arrays are stored contiguously:
    std::cout << "An int is " << sizeof(int) << " bytes\n";
    // these are sizeof(int) bytes apart:
    std::cout << &(primes[0]) << "\n";
    std::cout << &(primes[1]) << "\n";
    std::cout << &(primes[2]) << "\n";

    // if we want a specific number of elements, we could do:
    std::vector<int> data { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
    // but std::vector has an explicit constructor `explicit
    // std::vector<T>(std::size_t)` that is used by direct-initialization
    std::vector<int> data2(
        10); // each of the created elements are value-initialized -- for int
             // this is zero-initialization, for class types this is the default
             // constructor

    // this wouldn't work with an initializer like `{ 10 }` because C++ has a
    // rule that when an initializer list is non-empty, a matching list
    // constructor will be selected over other matching constructors (if it were
    // empty, the default constructor would be preferred)

    // std::vector<int> v1 = 10; // won't work, just `10` by itself isn't an
    // initializer list and can't be copied into v1 (copy-initialization doesn't
    // match explicit constructors, i.e. the one used above with data2)
    std::vector<int> v2(
        10); // direct initialization with a non-initializer list, matches the
             // explicit single-argument constructor used with data2 above
    std::vector<int> v3 {
        10
    }; // list initialization with an initializer list, matching the list
       // constructor over the explicit constructor from above
    std::vector<int> v4 = {
        10
    }; // copy-initialization with an initializer list, matches list constructor
       // (since it's non-explicit)
    std::vector<int> v5({ 10 }); // copy list initialization with an initializer
                                 // list, matches list constructor
    std::vector<int>
        v6 {}; // empty initializer lits matches default constructor
    std::vector<int>
        v7 = {}; // empty initializer list matches default constructor

    // basically, `{ 10 }` will match a list constructor if one exists, or a
    // single-argument constructor otherwise

    // direct initialization is disallowed for member default initializers, only
    // copy initialization or list initialization (whether direct or copy) are
    // allowed; CTAD is also disallowed

    // we will have to create a vector with direct initialization and then use
    // that as the initializer:
    struct Foo {
        std::vector<int> v { std::vector<int>(8) };
    };

    // const is fine on std::vector:
    const std::vector<int> prime {
        2, 3, 5, 7, 11
    }; // the container itself can be const but the elements cannot, so
       // std::vector<const int> is invalid

    // constexpr is *not* allowed on std::vector but it's fine on std::array (17.1)

    return 0;
}