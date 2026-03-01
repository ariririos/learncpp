#include "../print.h"
#include <algorithm>
#include <array>

bool contains_nut(std::string_view str) {
    // std::string_view::find returns the index of the substring otherwise npos
    return str.find("nut") != std::string_view::npos;
}

bool greater(int a, int b) { return a > b; }

void double_number(int &i) { i *= 2; }

int main() {
    // the stdlib includes algorithms for common tasks of three types:
    // - inspectors, for viewing data in a container, e.g. searching and counting
    // - mutators, for modifying data in a container, e.g. sorting and shuffling
    // - facilitators, for generating a result from container data, e.g. multiplying values, determining sort order

    // std::find() finds an element by value:
    std::array arr { 13, 90, 99, 5, 40, 80 };

    for (int i : arr) {
        std::cout << i << " ";
    }
    std::cout << "\n";

    std::cout << "Enter a value to search for and replace with: ";
    int search {};
    int replace {};
    std::cin >> search >> replace;

    // std::find() returns an iterator pointing to the found element, or the end of the container
    auto found { std::find(arr.begin(), arr.end(), search) };

    if (found == arr.end()) {
        std::cout << "Could not find " << search << "\n";
    } else {
        *found = replace;
    }

    for (int i : arr) {
        std::cout << i << " ";
    }
    std::cout << "\n";

    // std::find_if() uses a function to check for matches:
    std::array<std::string_view, 5> arr2 { "apple", "banana", "walnut", "lemon",
                                           "peanut" };

    auto found2 { std::find_if(arr2.begin(), arr2.end(), contains_nut) };
    if (found2 == arr2.end()) {
        std::cout << "No nuts\n";
    } else {
        std::cout << "Found " << *found2 << "\n";
    }

    // std::count and std::count_if count occurences of an element / an element fulfilling a condition
    auto nuts { std::count_if(arr2.begin(), arr2.end(), contains_nut) };
    std::cout << "Counted " << nuts << " nut(s)\n";

    // std::sort optionally takes a function that determines the sort order; we can use that for a descending sort:
    std::array<int, 6> backup_arr {};
    std::copy(arr.begin(), arr.end(), backup_arr.begin());
    for (int i : arr) {
        std::cout << i << " ";
    }
    std::cout << "\n";
    std::sort(arr.begin(), arr.end(), greater);
    for (int i : arr) {
        std::cout << i << " ";
    }
    std::cout << "\n";
    // <functional> provides a std::greater type that does the same thing but needs to be instantiated:
    for (int i : backup_arr) {
        std::cout << i << " ";
    }
    std::cout << "\n";
    std::sort(backup_arr.begin(), backup_arr.end(), std::greater {});
    for (int i : backup_arr) {
        std::cout << i << " ";
    }
    std::cout << "\n";

    // std::for_each() runs a function for every element in a container; normally not very useful but when combined with std::next(), can skip elements of a container
    std::array arr3 { 1, 2, 3, 4 };
    std::for_each(std::next(arr3.begin()), arr3.end(), double_number);
    for (auto &i : arr3) {
        std::cout << i << " ";
    }
    std::cout << "\n";
    // as of c++20, std::ranges::foreach would be called like:
    // std::ranges::for_each(arr3, double_number);
    // not requiring .begin() and .end()

    // many algorithms can be parallelized, e.g. std::for_each
    // only certain algorithms provide a guarantee of sequential execution: std::for_each, std::copy, std::copy_backward, std::move, and std::move_backward
    // others are implicitly sequential due to requiring a forward iterator

    // c++20 provides "ranges" which obviate the need for calling arr.begin() and arr.end() and allow just passing arr
    return 0;
}