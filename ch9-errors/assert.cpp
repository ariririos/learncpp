//#define NDEBUG
#include <iostream>
#include <cassert>

int main(int argc, char** argv) {
    const int test = 2;
    static_assert(test == 2);
    assert(argc == 1 && "No arguments should be provided");
}