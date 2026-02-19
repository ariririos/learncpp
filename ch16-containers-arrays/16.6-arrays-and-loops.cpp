#include <iostream>
#include <vector>

template <typename T>
T calculate_average(const std::vector<T>& arr) {
    std::size_t length { arr.size() };
    T average { 0 }; // average should have same type as the elements
    for (std::size_t index { 0 }; index < length; index++) {
        average += arr[index];
    }
    average /= static_cast<int>(length);
    return average;
}

int main() {
    std::vector class1 { 84, 92, 76, 81, 56 };
    std::size_t length { class1.size() };

    int average { 0 };
    for (std::size_t index { 0 }; index < length; index++) {
        average += class1[index];
    }
    average /= static_cast<int>(length);

    std::cout << "The class 1 average is: " << average << "\n";
    std::cout << "The class 1 average is: " << calculate_average(class1) << "\n";

    
    std::vector class2 { 93.2, 88.6, 64.2, 81.0 };
    std::cout << "The class 2 average is: " << calculate_average(class2) << "\n";

    return 0;
}