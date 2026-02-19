#include <vector>
#include <iostream>

int main() {
    std::vector v { 'h', 'e', 'l', 'l', 'o' };
    
    std::cout << "The array has " << v.size() << " elements.\n";
    std::cout << v[1] << v.at(1) << "\n";

    return 0;
}