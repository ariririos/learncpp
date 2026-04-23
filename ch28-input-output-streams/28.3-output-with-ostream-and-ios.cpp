#include <iostream>

int main() {
    // the insertion operator (`<<`) puts information into an output stream

    // both istream and ostream derive from a class called ios; one of the jobs of ios and ios_base is to control formatting for output

    // formatting is controlled one of two ways: flags and manipulators; flags are like boolean variables that can be turned on and off, while manipulators are objects placed in a stream that affect input and output

    // flags are turned on via .setf() with the flag as a parameter; e.g. to put a + sign in front of positive numbers:
    std::cout.setf(std::ios::showpos);
    std::cout << 27 << "\n"; // prints +27

    // bitwise OR can be used to enable multiple flags:
    std::cout.setf(std::ios::showpos | std::ios::uppercase);
    std::cout << 1234567.89f << "\n"; // prints +1.23457E+06

    // flags are turned off via .unsetf:
    std::cout.unsetf(std::ios::showpos);
    std::cout << 27 << "\n"; // prints 27

    // many flags belong to groups called "format groups", which perform similar, sometimes mutually exclusive, formatting options
    // for example the "basefield" formatting group controls the base of integral values via the flags "oct", "dec", and "hex"
    // if we try to change the flag from the default "dec" to "hex", it won't work because setf() isn't smart enough to disable mutually exclusive flags:
    std::cout.setf(std::ios::hex);
    std::cout << 27 << "\n"; // still prints 27

    // we can get around this by either manually turning dec off:
    std::cout.unsetf(std::ios::dec);
    std::cout.setf(std::ios::hex);
    std::cout << 27 << "\n"; // now prints 1B
    // or by using an alternate form of setf which takes the formatting group as a second argument and turns off all flags in the group except for the first argument:
    std::cout.setf(std::ios::hex, std::ios::basefield);
    std::cout << 27 << "\n"; // prints 1B

    // manipulators, however, are smart enough to turn on and off the appropriate flags:
    std::cout << std::hex << 27 << "\n"; // prints 1B
    std::cout << 28 << "\n";             // prints 1C because we're still in hex
    std::cout << std::dec << 29 << "\n"; // back to decimal, prints 29

    /*
    # Some useful formatters:
    
    ## boolalpha (boolean formatting)
    - flag: std::ios::boolalpha (no group)
    - manipulators: std::boolalpha / std::noboolalpha (default)

    ## showpos (positive sign)
    - flag: std::ios::showpos (no group)
    - manipulators: std::showpos / std::noshowpos

    ## uppercase (using uppercase for scientific notation, hex notation, etc.)
    - flag: std::ios::uppercase (no group)
    - manipulators: std::uppercase / std::nouppercase

    ## basefield (base to print numbers in)
    - flags (std::ios::basefield group): std::ios::dec, std::ios::hex, std::ios::oct; if no flag then numbers are printed according to their leading characters
    - manipulators: std::dec, std::hex, std::oct

    ## floatfield (notation to use for floating point numbers)
    - flags (std::ios::floatfield group): std::ios::fixed, std::ios::scientific, std::ios::showpoint (whether to always show decimal point and trailing zeroes); if no flag then fixed is used for numbers with few digits, scientific otherwise
    - manipulators: std::fixed, std::scientific, std::showpoint, std::noshowpoint, std::setprecision(int)
    - member functions: std::ios_base::precision (returns current precision), std::ios_base::precision(int) (sets current precision and returns old precision)
    // note that precision means the number of digits after the decimal point, and if precision is less than the number of significant digits then the number will be rounded; if neither fixed nor scientific is used, then precision determines how many significant digits will be displayed (subject to rounding) and showpoint can be used to force the decimal point (even if no digits are display after the point) and trailing zeroes

    ## adjustfield (width/fill characters/justification)
    - flags (std::ios::adjustfield group): std::ios::internal (left-justify sign, right-justify value), std::ios::left, std::ios::right (default)
    - manipulators: std::internal, std::left, std::right, std::fill(char) (set fill character), std::setw(int) (set field width for input and output)
    - member functions: std::basic_ostream::fill (return current fill character), std::basic_ostream::fill (set current fill and return old), std::ios::width (return current field width), std::ios::width(int) (set current width and return old)
    // note that width must be set before using the justification/fill formatters, and that setw() and width() only affect the next output statement
    */
}
