#include <cassert>
#include <iostream>
#include <string>

class MyString {
private:
    std::string m_string {};

public:
    MyString(std::string_view str = {}) : m_string { str } {}
    friend std::ostream &operator<<(std::ostream &out, const MyString &str);
    MyString operator()(std::size_t index, std::size_t length) {
        assert((index + length) <= m_string.length());
        return { m_string.substr(index, length) };
    }
};

std::ostream &operator<<(std::ostream &out, const MyString &str) {
    out << str.m_string;
    return out;
}

int main() {
    MyString s { "Hello, world!" };
    std::cout << s(7, 5) << "\n";

    return 0;
}