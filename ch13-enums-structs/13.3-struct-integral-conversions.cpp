#include <iostream>
#include <cstdint>
#define print(x, ...) { std::cout << #x << " = " << x; __VA_OPT__(std::cout , __VA_ARGS__;) std::cout << std::endl; }

template <typename T>
std::ostream& operator,(std::ostream& out, const T& t) {
    out << " " << t;
    return out;
}

std::ostream& operator,(std::ostream& out, std::ostream&(*f)(std::ostream&)) {
    out << f;
    return out;
}

enum Animal {
    cat = -3,
    dog, // -2
    pig, // -1
    // there's no zero here
    horse = 5,
    giraffe = 5, // same value as horse
    chicken, // 6
};

enum SixteenBitColor: std::int16_t {
    black,
    red,
    blue
};

int main() {
    print(cat);
    print(dog);
    print(pig);
    print(horse);
    print(giraffe);
    print(chicken);

    Animal a {};
    print(a); // meaningless 

    // Animal test { 5 }; // won't compile, int doesn't convert to enum
    Animal pet { static_cast<Animal>(5) };
    pet = static_cast<Animal>(6);
    print(pet);

    SixteenBitColor c { red };
    print(c);
    print(sizeof(c));

    SixteenBitColor d { 0 }; // fine for enums with explicitly specified base
    print(d);
    // SixteenBitColor e (1); // won't compile, can't direct-initialize with int
    // SixteenBitColor f = 2; // won't compile, can't assign with int

    return 0;
}