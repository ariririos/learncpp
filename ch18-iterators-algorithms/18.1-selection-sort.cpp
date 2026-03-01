#include "../print.h"
#include <iterator>
#include <utility>

int main() {
    int x { 2 };
    int y { 4 };
    std::cout << "Before swap: \n";
    print(x);
    print(y);
    std::swap(x, y);
    std::cout << "After swap: \n";
    print(x);
    print(y);

    // selection sort of an array:
    // 1. find the smallest value starting from index 0
    // 2. swap that value with the value at index 0
    // 3. repeat from the next index

    int array[] { 30, 50, 20, 10, 40 };
    constexpr int length { static_cast<int>(std::size(array)) };

    // we can stop one before the end because the last swap will be the last element with itself
    for (int start_index { 0 }; start_index < length - 1; start_index++) {
        // smallest_index is the smallest value we've seen so far
        int smallest_index { start_index };
        // look for a smaller value
        for (int curr_index { start_index + 1 }; curr_index < length;
             curr_index++) {
            // if we found a smaller one, store its index
            if (array[curr_index] < array[smallest_index]) {
                smallest_index = curr_index;
            }
        }
        // at this point smallest_index holds the smallest value
        // so we can do the swap
        std::swap(array[start_index], array[smallest_index]);
    }

    // array now sorted!
    for (int index { 0 }; index < length; index++) {
        std::cout << array[index] << " ";
    }
    std::cout << "\n";

    // std::sort() can do the same thing:
    int array2[] { 30, 50, 20, 10, 40 };
    std::sort(std::begin(array2), std::end(array2));

    for (int i { 0 }; i < static_cast<int>(std::size(array2)); i++) {
        std::cout << array2[i] << " ";
    }
    std::cout << "\n";

    return 0;
}