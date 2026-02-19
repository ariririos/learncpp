#include <iostream>
#include <vector>
#include <ranges> // for std::views::reverse

int main() {
    // range-based for loops (also called for-each loops) avoid off-by-one
    // errors and sign-based indexing problems; they work with the common array
    // types -- std::vector, std::array, and C-style arrays
    std::vector fibonacci { 0, 1, 1, 2, 3, 5, 8, 13, 21, 34, 55, 89 };
    // this variable declaration should have the same type as the array elements
    // to avoid type conversions
    for (int num : fibonacci) { // each element gets copied into num
        std::cout << num << " ";
    }
    std::cout << "\n";

    // if the array is empty, the body of the range-based for loop won't
    // execute, same as a regular for loop

    // using auto is a good idea here to avoid accidental type conversions:
    for (auto num : fibonacci) {
        std::cout << num << " ";
    }
    std::cout << "\n";

    // consider this version of this loop which copies each element:
    std::vector<std::string> words { "peter", "likes", "frozen", "yogurt" };
    for (auto word : words) {
        std::cout << word << " ";
    }
    std::cout << "\n";
    // it can be changed to use references instead like this:
    for (const auto &word : words) {
        std::cout << word << " ";
    }
    std::cout << "\n";
    // auto should be used with cheap-to-copy types, auto& when we need to modify the original elements, and const auto& otherwise, when we just need to view the elements

    // range-based for loops work with std::vector, std::array, linked lists, trees, maps, and non-decayed C-style arrays
    // they won't work with decayed C-style arrays because the loop needs to know the length of the array, and they won't normally work with enums (see 17.6)

    // there isn't a standard way to access the array index of the current element (because for example, std::list doesn't have indices), but if that's needed, a counter or regular for loop works

    // in c++20, we can loop in reverse with std::views::reverse
    for (const auto& word : std::views::reverse(words)) {
        std::cout << word << " ";
    }
    std::cout << "\n";
    
    return 0;
}