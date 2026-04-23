#include <iostream>
#include <sstream>

int main() {
    // stream classes for strings allow you to work with strings using the stream opreators
    // there are six stream classes for strings (<sstream>): istringstream (derived from istream), ostringstream (derived from ostream), and stringstream (derived from iostream) read and write normal character width strings; wistringstream, wostringstream, and wstringstream read and write wide character strings

    // data can be inserted into a stringstream using either << or .str(string)
    std::stringstream os {};
    os << "en garde!\n";
    os.str("en garde!");

    // data can be extracted from a stringstream with either .str() or >>
    // str() always extracts the whole value of the stream, even if >> has already been used on the stream
    std::cout << os.str() << "\n"; // prints "en garde!"

    std::string str_value {};
    os >> str_value;

    std::string str_value2 {};
    os >> str_value2;

    // << iterates through the string and returns the next extractable value in the stream
    std::cout << str_value << " - " << str_value2
              << "\n"; // prints "en - garde!"

    // we can convert numbers into a string using stringstream:
    std::stringstream os_num {};
    constexpr int n_value { 12345 };
    constexpr double d_value { 67.89 };
    os_num << n_value << " " << d_value;

    std::string str_num1, str_num2;
    os_num >> str_num1 >> str_num2;

    std::cout << str_num1 << " " << str_num2 << "\n"; // prints 12345 67.89

    // and convert strings into numbers:
    std::stringstream os_str {};
    os_str << "12345 67.89";
    int n_value2 {};
    double d_value2 {};
    os_str >> n_value2 >> d_value2;
    std::cout << n_value2 << " " << d_value2 << "\n"; // prints 12345 67.89

    // clearing a stringstream can be done by setting it to an empty string using .str() with either a blank C-style string or a blank std::string object:
    std::stringstream os2 {};
    os2 << "Hello ";
    os2.str("");
    os2 << "World\n";
    std::cout << os2.str();

    os2.str(std::string {});

    os2 << "World\n";
    std::cout << os2.str();

    // when clearing out a stringstream it's a good idea to also call .clear() to reset any error flags and return the stream back to the ok state
    std::stringstream os3 {};
    os3 << "Hello ";
    os3.str("");
    os3.clear();
    os3 << "World!\n";
    std::cout << os3.str();

    return 0;
}