#include <cstdlib>
#include <iostream>

void cleanup() { std::cout << "everybody clean up\n"; }

int main() {
    std::atexit(cleanup);
    std::cout << 1 << "\n";
    // std::exit(0); // cleanup executes here if uncommented
    std::cout << 2 << "\n";

    // cleanup executes here otherwise
    return 0;
}