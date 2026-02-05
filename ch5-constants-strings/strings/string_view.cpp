#include <iostream>
#include <string_view>

void print_sv(std::string_view str) { std::cout << str << "\n"; }
void print_str(std::string str) { std::cout << str << "\n"; }
std::string get_dangling_str() {
    std::string str { "dangling" };
    return str;
}

int main() {
    using namespace std::string_literals;

    std::string name { "name = Alex" };
    std::string_view sv { name };
    print_sv(name);

    std::string_view sv2 { "sv2 = Jack" };
    // print_str(sv2);
    std::string str2 { sv2 };
    print_str(str2);
    print_str(static_cast<std::string>(sv2));

    sv = "sv = John";
    print_sv(name);
    print_sv(name);

    constexpr std::string_view s { "Constant" };
    print_sv(s);

    std::string_view sv3 { "dangling"s };
    std::string_view sv4 { "not dangling" };
    print_sv(sv3);
    print_sv(sv4);

    std::string_view sv5 { get_dangling_str() };
    print_sv(sv5);

    std::string str3 { "Long out-of-date string contents" };
    std::string_view sv6 { str3 };

    str3 = "abc";
    print_sv(sv6);
    sv6 = str3;
    print_sv(sv6);

    return 0;
}