#include <iostream>

int main() {
    int array[] { 30, 50, 20, 10, 40 };
    constexpr int length { static_cast<int>(std::size(array)) };

    // we can stop one before the end because the last swap will be the last element with itself
    for (int start_index { 0 }; start_index < length - 1; start_index++) {
        // largest_index is the largest value we've seen so far
        int largest_index { start_index };
        // look for a larger value
        for (int curr_index { start_index + 1 }; curr_index < length;
             curr_index++) {
            // if we found a larger one, store its index
            if (array[curr_index] > array[largest_index]) {
                largest_index = curr_index;
            }
        }
        // at this point largest_index holds the largest value
        // so we can do the swap
        std::swap(array[start_index], array[largest_index]);
    }

    // array now sorted!
    for (int index { 0 }; index < length; index++) {
        std::cout << array[index] << " ";
    }
    std::cout << "\n";

    return 0;
}