#include <chrono>
#include <iostream>
#include <random>

unsigned int random_state { 0 };

void seed_prng(unsigned int seed) { random_state = seed; }

unsigned int LCG16() {
    random_state = 8253729 * random_state + 2396403;
    return random_state % 32768;
}

int main() {
    unsigned int x;
    std::cout << "Enter seed: ";
    std::cin >> x;
    seed_prng(x);
    int count = 21;
    std::cout << "LCG16 randoms\n";
    for (int i { 1 }; i < count; i++) {
        std::cout << LCG16() << "\t";

        if (i % 5 == 0) {
            std::cout << "\n";
        }
    }

    std::cout << "MT randoms: \n";
    std::mt19937 mt {};

    for (int i { 1 }; i < count; i++) {
        std::cout << mt() << "\t";
        if (i % 5 == 0) {
            std::cout << "\n";
        }
    }

    std::cout << "MT random uniform_int_distribution {1, 6}:\n";
    std::uniform_int_distribution die6 { 1, 6 };

    for (int i { 1 }; i < count; i++) {
        std::cout << die6(mt) << "\t";
        if (i % 5 == 0) {
            std::cout << "\n";
        }
    }

    std::mt19937 mt_seeded { static_cast<std::mt19937::result_type>(
        std::chrono::steady_clock::now().time_since_epoch().count()) };

    std::cout << "Seeded MT {1, 6}\n";
    std::uniform_int_distribution die6_seeded { 1, 6 };

    for (int i { 1 }; i < count; i++) {
        std::cout << die6_seeded(mt_seeded) << "\t";
        if (i % 5 == 0) {
            std::cout << "\n";
        }
    }

    std::mt19937 mt_seeded2 {std::random_device{}()};


}