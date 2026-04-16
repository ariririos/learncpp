#include <iostream>

double divide(int x, int y, bool &out_success) {
    if (y == 0) {
        out_success = false;
        return 0.0;
    }

    out_success = true;
    return static_cast<double>(x) / y;
}

int main() {
    // error handling using error codes is cryptic and subject to overlap with the range of possible return values; the other option using an in-out parameter to return a success/failure flag borders on unusable:
    bool success {};
    double result { divide(5, 3, success) };
    if (!success) {
        std::cerr << "An error occurred\n";
    } else {
        std::cout << "The answer is " << result << "\n";
    }
    // if we had multiple possible failure modes, then each one has to be checked in sequence, and that obscures the actual operation being done

    // error handling in constructors is even worse: constructors have no return value, so we have to use an in-out parameter, and even if construction does fail, the object still gets created and must be disposed of properly

    // finally, if the caller isn't equipped to handle the error, then it'll have to ignore it and lose it forever, or return the error up the stack to its own caller (leading to the same repetitive code as with multiple failure modes)
}