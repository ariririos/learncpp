#ifndef RANDOM_MT_H
#define RANDOM_MT_H

#include <chrono>
#include <random>

// Self-seeding Mersenne Twister.
// Freely redistributable, courtesy of learncpp.com (https://www.learncpp.com/cpp-tutorial/global-random-numbers-random-h/)

namespace Random {
    // Returns a seeded Mersenne Twister
    inline std::mt19937 generate() {
        std::random_device rd {};
        std::seed_seq ss {
            static_cast<std::seed_seq::result_type>(std::chrono::steady_clock::now().time_since_epoch().count()), rd(), rd(), rd(), rd(), rd(), rd(), rd()
        };
        return std::mt19937 { ss };
    }

    // Here's our global std::mt19937 object.
    inline std::mt19937 mt { generate() };

    // Generate a random int in [min, max].
    inline int get(int min, int max) {
        return std::uniform_int_distribution{ min, max }(mt);
    }

    // Generate a random value in [min, max].
	// * min and max must have the same type
	// * return value has same type as min and max
	// * Supported types:
	// *    short, int, long, long long
	// *    unsigned short, unsigned int, unsigned long, or unsigned long long
	// Sample call: Random::get(1L, 6L);             // returns long
	// Sample call: Random::get(1u, 6u);             // returns unsigned int

    template <typename T>
    T get(T min, T max) {
        return std::uniform_int_distribution<T>{min, max}(mt);
    }

    // Generate a random value in [min, max].
	// * min and max can have different types
    // * return type must be explicitly specified as a template argument
	// * min and max will be converted to the return type
	// Sample call: Random::get<std::size_t>(0, 6);  // returns std::size_t
	// Sample call: Random::get<std::size_t>(0, 6u); // returns std::size_t
	// Sample call: Random::get<std::int>(0, 6u);    // returns int
    template <typename R, typename S, typename T>
    R get(S min, T max) {
        return get<R>(static_cast<R>(min), static_cast<R>(max));
    }
}

#endif