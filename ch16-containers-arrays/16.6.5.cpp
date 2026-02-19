#include <iostream>
#include <vector>

template <typename T>
T find_max(const std::vector<T>& vec) {
    std::size_t length { vec.size() };
    if (length == 0) {
        return {};
    }
    T max { vec[0] }; // if we did value initialization here (probably setting it to 0) then it would return the wrong result for arrays with only negative elements
    // if length == 1 then we skip to the return at the bottom of this function
    for (std::size_t i { 1 }; i < length; i++) {
        if (vec[i] > max) {
            max = vec[i];
        }
    }
    return max;
}

int main() {
    std::vector data1 { 84, 92, 76, 81, 56 };
    std::cout << find_max(data1) << "\n";

    std::vector data2 { -13.0, -26.7, -105.5, -14.8 };
    std::cout << find_max(data2) << "\n";

    std::vector<int> data3 {};
    std::cout << find_max(data3) << "\n";

    return 0;
}