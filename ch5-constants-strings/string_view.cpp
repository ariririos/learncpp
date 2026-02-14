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
    print_sv(name); // std::string will convert to std::string_view

    std::string_view sv2 { "sv2 = Jack" };
    // print_str(sv2); // can't print string_view as string
    std::string str2 { sv2 };
    print_str(str2); // fine
    print_str(static_cast<std::string>(sv2)); // same thing

    sv = "sv = John"; 
    print_sv(sv); // you can change what a string_view points at
    print_sv(name); // but the underlying string remains the same

    constexpr std::string_view s { "Constant" };
    print_sv(s);

    std::string_view sv3 {};
    {
        std::string s { "Hello world!" };
        sv = s;
    }

    std::cout << sv3 << "\n"; // undefined behavior, sv3 is dangling

    std::string_view sv4 { "dangling"s }; // a temporary std::string object is created and then destroyed
    std::string_view sv5 { "not dangling" };
    print_sv(sv4); // undefined behavior, sv4 is dangling
    print_sv(sv5); // fine if initialized without converting to std::string 

    std::string_view sv6 { get_dangling_str() };
    print_sv(sv6);

    std::string str3 { "Long out-of-date string contents" };
    std::string_view sv7 { str3 };

    str3 = "abc";
    print_sv(sv7);
    sv7 = str3;
    print_sv(sv7);

    return 0;
}