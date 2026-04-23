#include <iostream>

int main() {
    // the extraction operator (`>>`) reads information from an input stream

    // to prevent overwriting a buffer when using >>, we can use a "manipulator"; manipulators modify a stream when applied with >> or <<
    // std::endl is a manipulator that prints a newline and flushes any buffered output
    // std::setw (<iomanip>) can be used to limit the number of characters read in from a stream
    /*
    char buf[10] {};
    std::cout << "Enter up to 9 characters: ";
    std::cin >> std::setw(10) >>
        buf; // this only reads the first 9 characters out of the stream (leaving room for a terminator); the remainder will be left in the stream until the next extraction
    std::cout << "You entered: " << buf << "\n";
    */

    // the extraction operator skips whitespace:
    // if you enter below "hello my name is ari", the output will be "hellomynameisari"
    /*
    char ch {};
    while (std::cin >> ch && !std::cin.eof()) {
        std::cout << ch;
    }
    */

    // we can use other functions that don't discard whitespace, like .get(), which gets a single character from the stream:
    /*
    char ch2 {};
    while (std::cin.get(ch2) && ch2 != '~') {
        std::cout << ch2;
    }
    */

    /*
    // .get() has a string version that takes the maximum number of characters to read:
    std::cout << "Enter up to 10 characters: ";
    char str_buf[11] {};
    std::cin.get(str_buf, 11);
    std::cout << str_buf << "\n";

    // .get() doesn't read a newline character, so if we get more input from the user after calling .get() once, it'll be a newline and immediately stop
    std::cout << "Enter up to 10 characters: ";
    char str_buf2[11] {};
    std::cin.get(str_buf2, 11);
    std::cout << str_buf2 << "\n";
    */

    /*
    // we can use .getline() instead which will read then discard the newline:
    std::cout << "Enter up to 10 characters: ";
    char str_buf3[11] {};
    std::cin.getline(str_buf3, 11);
    std::cout << str_buf3 << "\n";

    std::cout << "Enter up to 10 more characters: ";
    std::cin.getline(str_buf3, 11);
    std::cout << str_buf3 << "\n";
    */

    // if we want to know how many characters were extracted by the last call of .getline(), use .gcount():
    char str_buf4[100] {};
    std::cout << "Enter up to 100 characters: ";
    std::cin.getline(str_buf4, 100);
    std::cout << str_buf4 << "\n";
    std::cout << std::cin.gcount() << " characters were read\n";
    // gcount() includes any extracted and discarded delimiters

    // there's a special version of getline that lives outside the istream class that is used for reading in std::string variables; it lives in <string>
    std::string str_buf {};
    std::cout << "Enter a string: ";
    std::getline(std::cin, str_buf);
    std::cout << str_buf << "\n";

    // there's a few more useful input functions:
    // - ignore() discards the first character in the stream
    // - ignore(int n_count) discards the first n_count characters
    // - peek() allows you to read a character from the stream without removing it from the stream
    // - unget() returns the last character read back into the stream so it can be read again
    // - putback(char ch) allows you to put any character back into the stream to be read again

    return 0;
}