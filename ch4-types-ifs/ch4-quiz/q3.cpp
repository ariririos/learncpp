#include <iostream>


int get_height() {
    std::cout << "Enter the height of the tower in meters: ";
    int h {};
    std::cin >> h;
    return h;
}

double distance_fallen(int secs) {
    double g = 9.8;
    return g * secs * secs / 2;
}

void print_height(int secs, double meters) {
    if (meters > 0.0) {
        std::cout << "At " << secs << " seconds, the ball is at height: " << meters << " meters\n";
    }
    else {
        std::cout << "At " << secs << " seconds, the ball is on the ground.\n";
    }
}

int main() {
    int h { get_height() };
    print_height(0, h);
    print_height(1, h - distance_fallen(1));
    print_height(2, h - distance_fallen(2));
    print_height(3, h - distance_fallen(3));
    print_height(4, h - distance_fallen(4));
    print_height(5, h - distance_fallen(5));

    return 0;
}