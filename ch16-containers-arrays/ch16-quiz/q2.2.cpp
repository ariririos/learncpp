#include <cassert>
#include <iostream>
#include <vector>

namespace Items {
    enum Type { health_potion, torch, arrow, max_item };
}

int sum_items(const std::vector<int> &items) {
    int sum {};
    for (int item : items) {
        sum += item;
    }
    return sum;
}

void print_inventory(const std::vector<int> &items) {
    for (std::size_t i { 0 }; i < Items::max_item; i++) {
        std::cout << "You have " << items[i] << " ";
        switch (i) {
        case Items::health_potion:
            std::cout << "health potion";
            break;
        case Items::torch:
            std::cout << "torch";
            break;
        case Items::arrow:
            std::cout << "arrow";
            break;
        default:
            std::cout << "???";
            break;
        }
        if (items[i] != 1) {
            if (i == Items::torch) {
                std::cout << "es";
            } else {
                std::cout << "s";
            }
        }
        std::cout << "\n";
    }
}

int main() {
    std::vector inventory { 1, 5, 10 };
    assert(std::size(inventory) == Items::max_item);
    print_inventory(inventory);
    std::cout << "You have total " << sum_items(inventory) << " items\n";

    return 0;
}