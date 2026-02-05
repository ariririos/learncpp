#include <algorithm>
#include <iostream>

void sort2(int& x, int& y) {
    if (x > y) {
        std::swap(x, y);
    }
}

int main() {
    int x { 7 };
    int y { 5 };

    std::cout << x << " " << y << "\n";
    sort2(x, y);
    std::cout << x << " " << y << "\n";
    sort2(x, y);
    std::cout << x << " " << y << "\n";
}