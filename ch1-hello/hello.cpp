// #include <stdio.h>
#include <iostream>
// using namespace std;

int main(void) {
    int a { 5 };
    int b;
    int c = 4.5; // compiler will narrow this to `4` NOLINT
    // int d { 4.5 }; // will not compile
    int e = (4.5); // this will also narrow NOLINT
    printf("Hello world\n");
    std::cout << "Hello world again" << std::endl;
    std::cout << "a is " << a << std::endl;
    std::cout << "b is " << b << std::endl;
    std::cout << "c is " << c << std::endl;
    std::cout << "e is " << e << std::endl;
    a = 4.5; // this will also narrow despite using list-initialization NOLINT
    std::cout << "a is now " << a << std::endl;
    int f {}; // value/zero-initialization
    std::cout << "f is " << f << std::endl;
    [[maybe_unused]] double pi { 3.14159 };
    std::cout
        << "this line does nothing\n"; // this doesn't force a buffer flush
    std::cout << 1 / 0; // NOLINT
    return 0;
}