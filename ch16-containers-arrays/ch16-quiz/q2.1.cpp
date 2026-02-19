#include <vector>
#include <cassert>
#include <iostream>

namespace Items {
    enum Type {
        health_potion,
        torch,
        arrow,
        max_item
    };
}

int sum_items(const std::vector<int>& items) {
    int sum {};
    for (const auto& item : items) {
        sum += item;
    }
    return sum;
}

int main() {
    std::vector inventory { 1, 5, 10 };
    assert(inventory.size() == Items::max_item);
    std::cout << "You have total " << sum_items(inventory) << " items\n";

    return 0;
}