#include <cassert>
#include <iostream>
#include <string>

class MyString {
private:
    std::string m_string {};

public:
    MyString(std::string_view str = {}) : m_string { str } {}
    friend std::ostream &operator<<(std::ostream &out, const MyString &str);
    std::string_view operator()(std::size_t index, std::size_t length) {
        assert((index + length) <= m_string.length());
        return std::string_view { m_string }.substr(index, length);
    }
};

std::ostream &operator<<(std::ostream &out, const MyString &str) {
    out << str.m_string;
    return out;
}

int main() {
    MyString s { "Hello, world!" };
    MyString s2 { s(7, 5) };
    std::cout << s2 << "\n";

    return 0;
}