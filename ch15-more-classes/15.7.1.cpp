#include <chrono>
#include <random>
#include <iostream>

class Random {
private:
    static std::mt19937 generate() {
        std::random_device rd {};
        std::seed_seq ss { static_cast<std::seed_seq::result_type>(std::chrono::steady_clock::now().time_since_epoch().count()), rd(), rd(), rd(), rd(), rd(), rd(), rd() };

        return std::mt19937 { ss };
    }
    static inline std::mt19937 mt { generate() };
public:
    // Generate a random int in [min, max]
    static int get(int min, int max) {
        return std::uniform_int_distribution{ min, max }(mt);
    }
};

int main() {
    for (int i { 0 }; i < 10; i++ ) {
        std::cout << Random::get(1, 6) << "\t";
    }

    std::cout << "\n";

    return 0;
}