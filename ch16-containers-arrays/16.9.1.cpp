#include <cassert>
#include <iostream>
#include <vector>

namespace Animals {
    enum Type { chicken, dog, cat, elephant, duck, snake, max_animal };
    const std::vector legs = { 2, 4, 4, 4, 2, 0 };
} // namespace Animals

int main() {
    // max_animal won't be initialized so it should be one more than the size of
    // legs:
    assert(std::size(Animals::legs) == Animals::max_animal);
    std::cout << "An elephant has " << Animals::legs[Animals::elephant]
              << " legs\n";

    return 0;
}