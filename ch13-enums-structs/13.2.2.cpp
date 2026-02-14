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

namespace MonsterType {
    enum MonsterType {
        orc,
        goblin,
        troll,
        ogre,
        skeleton,
    };
}

int main() {
    MonsterType::MonsterType bones { MonsterType::skeleton };

    print(bones);

    return 0;
}

