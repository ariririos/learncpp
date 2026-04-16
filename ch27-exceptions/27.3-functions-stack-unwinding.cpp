#include <cmath>
#include <iostream>

double my_sqrt(double x) {
    if (x < 0.0) {
        throw "Can't take sqrt of a negative";
    }
    return std::sqrt(x);
}

void D() {
    std::cout << "Start D\n";
    std::cout << "D throwing int exception\n";

    throw -1;

    std::cout << "End D\n";
}

void C() {
    std::cout << "Start C\n";
    D();
    std::cout << "End C\n";
}

void B() {
    std::cout << "Start B\n";
    try {
        C();
    } catch (double) {
        std::cerr << "B caught double exception\n";
    }

    try {
    } catch (int) {
        std::cerr << "B caught int exception\n";
    }
    std::cout << "End B\n";
}

void A() {
    std::cout << "Start A\n";
    try {
        B();
    } catch (int) {
        std::cerr << "A caught int exception\n";
    } catch (double) {
        std::cerr << "A caught double exception\n";
    }

    std::cout << "End A\n";
}

int main() {
    // try blocks will catch exceptions in functions called in the block not otherwise caught within that function
    std::cout << "Enter a number: ";
    double x {};
    std::cin >> x;
    try {
        double d { my_sqrt(x) };
        std::cout << "The sqrt of " << x << " is " << d << "\n";
    } catch (const char *exception) {
        std::cerr << "Error: " << exception << "\n";
    }

    // and exceptions will go all the way up the call stack looking for try blocks and matching catch blocks, then execution continues to the top of the matching catch block; the call stack is unwound, removing the current function from the call stack, as many times as necessary to make the function handling the exception the top function on the call stack
    // if no matching exception handler is found, the stack may or may not be unwound (see 27.4)
    // when the current function is removed from the call stack, all local variables are destroyed as usual (running their destructors), but no value is returned

    // stack unwinding example:
    /*
    for reference this prints:
    ```
    Start main
    Start A
    Start B
    Start C
    Start D
    D throwing int exception
    A caught int exception
    End A
    End main
    ```
    */
    std::cout << "Start main\n";
    try {
        A();
    } catch (int) {
        std::cerr << "main caught int exception\n";
    }
    std::cout << "End main\n";

    return 0;
}