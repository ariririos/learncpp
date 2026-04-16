#include <cmath>
#include <iostream>

int main() {
    // c++ implements exceptions with `throw`, `try`, and `catch`

    // we can throw any data type we want

    // we use try to observe for throws

    // we use catch to handle specific exception types

    try {
        throw -1;
    } catch (int x) {
        std::cerr << "We caught an int exception with value " << x << "\n";
    }

    // try blocks must be followed by catch blocks and can have multiple catch blocks
    // once an exception has been caught in the try block and handled by a matching catch block, the exception is considered handled, and execution continues after the last catch block
    // exceptions of fundamental types can be caught by value, but non-fundamental types should be caught by const reference to prevent unnecessary copies and slicing

    try {
    }
    // we can omit the parameter name if it won't be used
    catch (double) {
    }

    // no type conversion is done for exceptions (so an int exception won't be converted to match a catch block with a double parameter)

    try {
        throw -1;
    } catch (double) {
        std::cerr << "Caught exception of type double\n";
    } catch (int x) {
        std::cerr << "Caught exception of type int with value: " << x << "\n";
    } catch (const std::string &) {
        std::cerr << "Caught exception of type std::string\n";
    }
    std::cout << "Execution continues here\n";

    // exceptions will be caught by the nearest enclosing try block (propogating up the stack if necessary), and then the catch blocks attached to that try block will be checked; if no appropriate catch blocks can be found, then the next enclosing try block is checked in the same way
    // if no appropriate catch handler can be found before the end of the program, the program will fail with a runtime exception

    // normally no conversions/promotions will be performed to find a matching catch block, except for casts from a derived class to one of its parent classes

    // exceptions are handled immediately:
    try {
        throw 4.5;
        std::cout << "This never prints\n";
    } catch (double) {
        std::cerr << "Caught a double\n";
    }

    // a more realistic example:
    std::cout << "Enter a number: ";
    double x {};
    std::cin >> x;

    try {
        if (x < 0.0) {
            throw "Can't take sqrt of a negative";
        }
        std::cout << "The sqrt of " << x << " is " << std::sqrt(x) << "\n";
    } catch (const char *exception) {
        std::cerr << "Error: " << exception << "\n";
    }

    // catch blocks typically do one of four things:
    // - print an error and proceed
    // - return a value or error code back to the caller
    // - throw another exception, which will be caught by the next enclosing try block, not the preceding try block we just came from
    // - if in main(), can catch fatal errors and terminate the program cleanly
    return 0;
}