#include <iostream>
#include <vector>

template <typename T>
void print_element(const std::vector<T>& arr, int idx) {
    // int size = static_cast<int>(arr.size());
    if (idx < 0 || idx >= std::ssize(arr)) {
        std::cout << "Invalid index\n";
        return;
    }
    std::cout << "The element has value " << arr[static_cast<std::size_t>(idx)] << "\n";
}

int main() {
    std::vector v1 { 0, 1, 2, 3, 4 };
    print_element(v1, 2);
    print_element(v1, 5);

    std::vector v2 { 1.1, 2.2, 3.3 };
    print_element(v2, 0);
    print_element(v2, -1);

    return 0;
}