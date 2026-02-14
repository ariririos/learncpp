#include "14.13-print_string.h"
#include <string>
#include <string_view>

int main() {
    // void print_string(const std::string& s)
    // sv can't be passed directly to print_string
    std::string_view sv { "Hello" };
    print_string(static_cast<std::string>(sv)); // case 1: static_cast returns a temporary std::string direct-initialized with sv
    print_string(std::string { sv }); // case 2: explicitly create a temporary std:string list-initialized with sv
    print_string(std::string ( sv )); // case 3: C-style cast returns temporary std::string direct initialized with sv (avoid C-style casts in general)
}