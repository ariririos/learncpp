#include <algorithm>
#include <functional>
#include <iostream>

// case 1: use std::function (has some overhead)
void repeat1(int count, const std::function<void(int)> &fn) {
    for (int i { 0 }; i < count; i++) {
        fn(i);
    }
}

// case 2: function template
template <typename T> void repeat2(int count, const T &fn) {
    for (int i { 0 }; i < count; i++) {
        fn(i);
    }
}

// case 3: abbreviated function template (preferred)
void repeat3(int count, const auto &fn) {
    for (int i { 0 }; i < count; i++) {
        fn(i);
    }
}

// case 4: function pointer (only for lambda with no captures)
void repeat4(int count, void fn(int)) {
    for (int i { 0 }; i < count; i++) {
        fn(i);
    }
}

int main() {
    // lambdas are anonymous functions, syntax:
    // [ capture_clause ] ( parameters ) -> return_type { statements; }
    // capture_clause can be empty if none are needed; parameters can be empty if none are required and can be omitted entirely unless return type is specified; return type can be omitted and will be `auto` if so
    [] {}; // NOLINT // minimal lambda
    constexpr std::array<std::string_view, 4> arr { "apple", "banana", "walnut",
                                                    "lemon" };

    auto found { std::find_if(arr.begin(), arr.end(), [](std::string_view str) {
        return str.find("nut") != std::string_view::npos;
    }) };
    if (found == arr.end()) {
        std::cout << "No nuts\n";
    } else {
        std::cout << "Found " << *found << "\n";
    }

    // each lambda has a unique type; if the lambda has no capture clause, we can use a regular function pointer; if it does, std::function or auto works

    [[maybe_unused]] double (*add_numbers1)(
        double, double) { [](double a, double b) { return a + b; } };

    std::cout << add_numbers1(1, 2) << "\n";

    std::function add_numbers2 { [](double a, double b) { return a + b; } };

    std::cout << add_numbers2(3, 4) << "\n";

    auto add_numbers3 { [](double a, double b) { return a + b; } };

    std::cout << add_numbers3(5, 6) << "\n";

    auto lambda = [](int i) { std::cout << i << "\n"; };

    repeat1(3, lambda);
    repeat2(3, lambda);
    repeat3(3, lambda);
    repeat4(3, lambda);

    constexpr std::array months { "January", "February", "March",
                                  "April",   "May",      "June",
                                  "July",    "August",   "September",
                                  "October", "November", "December" };

    // find two consecutive months starting with the same letter using a generic lambda; this works because all of the string types work with operator[]
    const auto same_letter { std::adjacent_find(
        months.begin(), months.end(),
        [](const auto &a, const auto &b) { return a[0] == b[0]; }) };

    if (same_letter != months.end()) {
        std::cout << *same_letter << " and " << *std::next(same_letter)
                  << " starts with the same letter\n";
    }

    // but this wouldn't work with a lambda like the one below where we access a specific member function:
    constexpr auto five_letter_months { std::count_if(
        months.begin(), months.end(),
        [](std::string_view str) { return str.length() == 5; }) };

    std::cout << "There are " << five_letter_months
              << " months with 5 letters\n";

    // lambdas can be constexpr if it has no captures, or all captures are constexpr, and all functions called by the lambda are constexpr

    // lambdas work with static variables the same way as regular functions -- a unique lambda will be generated for each different type that auto resolves to:
    auto print { [](auto value) {
        static int call_count { 0 };
        std::cout << call_count++ << ": " << value << "\n";
    } };

    print("hello"); // 0: hello
    print("world"); // 1: world

    print(1); // 0: 1
    print(2); // 1: 2

    print("ding dong"); // 2: ding dong

    // when doing type deduction, the return types in all branches must match (same as a regular function)
    // auto divide([](int x, int y, bool int_division) {
    //     if (int_division) {
    //         return x / y;
    //     } else {
    //         return static_cast<double>(x) / y;
    //     }
    // });
    // if we specify a return type the compiler can do implicit conversions
    auto divide([](int x, int y, bool int_division) -> double {
        if (int_division) {
            return x / y; // NOLINT
        } else {
            return static_cast<double>(x) / y;
        }
    });

    std::cout << divide(3, 2, true) << "\n";
    std::cout << divide(3, 2, false) << "\n";

    // the stdlib provides lambdas in <functional>, for example std::greater
    // it also provides parallelism which a simple for-loop won't provide

    return 0;
}