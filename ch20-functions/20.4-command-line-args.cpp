#include <iostream>
#include <sstream>

int main(int argc, char *argv[]) {
    std::cout << "There are " << argc << " arguments:\n";
    for (int i { 0 }; i < argc; i++) {
        std::cout << i << " " << argv[i] << "\n";
    }

    if (argc <= 1) {
        if (argv[0]) {
            std::cout << "Usage: " << argv[0] << " <number>\n";
        } else {
            std::cout << "Usage: <program name> <number>\n";
        }
    }

    // converting string to int:
    std::stringstream convert { argv[1] };
    int my_int {};
    if (!(convert >> my_int)) {
        my_int = 0; // set to default if conversion fails
    }

    std::cout << "Got integer: " << my_int << "\n";

    return 0;
}