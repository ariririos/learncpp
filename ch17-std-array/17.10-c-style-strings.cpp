#include <cstring>
#include <ios>
#include <iostream>
#include <limits>

void print(char ptr[]) { std::cout << ptr << "\n"; }
// void input(char rolls[]) { std::cin >> rolls; }

int main() {
    // C-style strings include a hidden null terminator:
    [[maybe_unused]] char str1[8] {};
    [[maybe_unused]] const char str2[] { "string" };    // 7
    [[maybe_unused]] constexpr char str3[] { "hello" }; // 6

    // C-style strings will decay, losing the length information, necessitating the null terminator
    char str[] { "string" };
    std::cout << str << "\n";
    print(str);
    // if the null terminator is missing, it will just keep printing until it finds one:
    // char str4[6] { "string" };
    // std::cout << str4 << "\n";

    // as of c++20, operator>> can only be used to input *non-decayed* C-style strings (and other data types), but not decayed C-style strings; the length information is used to prevent buffer overflow (see void input(char rolls[]) above)
    char rolls[10] {};
    std::cout << "Enter your rolls: ";
    std::cin >> rolls;
    std::cout << "You entered: " << rolls << "\n";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    // the preferred way is to use std::cin.getline():
    char rolls2[10] {};
    std::cout << "Enter your rolls: ";
    std::cin.getline(rolls2, std::size(rolls2));
    std::cout << "You entered: " << rolls2 << "\n";
    // no std::cin.ignore() needed here because .getline() does it for us

    // we can't assign to a C-style string, same as a C-style array, but we can change individual characters:
    char str4[] { "string" };
    std::cout << str4 << "\n";
    str4[1] = 'p';
    std::cout << str4 << "\n";

    // we can get the size of the underlying array of a C-style string with std::size
    char str5[255] { "string" };
    std::cout << "length = " << std::size(str5) << "\n";
    // won't work with decayed C-style strings:
    char *ptr5 { str5 };
    // std::cout << "length = " << std::size(ptr5) << "\n";
    // we can use strlen() to get the actual length of the string minus the null terminator; works on decayed C-style strings as well:
    std::cout << "length = " << std::strlen(str5) << "\n";
    std::cout << "length = " << std::strlen(ptr5) << "\n";

    // **avoid** non-const C-style strings in favor of std::string

    return 0;
}