#include <fstream>
#include <iostream>

int main() {
    // each file stream class contains a file pointer with the current read/write position within the file; by default, when opening a file for reading/writing, the pointer is set to the beginning, unless opened in append mode, when it is set to the end

    // we can use seekg() ("get" for input) and seekp() ("put" for output) to manipulate the file pointer; for some types of streams, seekg() and seekp() operate independently, but with file streams, the read and write position are always identical, so seekg() and seekp() are interchangeable
    // they take two parameters, the first is an offset for how many bytes to move the file pointer, and the second is an ios flag for where to offset from:
    // - beg: beginning of the file (default)
    // - cur: current location of the file pointer
    // - end: end of the file
    // a positive offset moves the file pointer towards the end, negative towards the beginning
    {
        std::fstream inf { "Sample.txt" };
        inf.seekg(14, std::ios::cur);  // move forward 14 bytes
        inf.seekg(-18, std::ios::cur); // move back 18 bytes
        inf.seekg(22, std::ios::beg);  // move to 22nd byte
        inf.seekg(24);                 // move to 24th byte
        inf.seekg(-28, std::ios::end); // move to 28th byte before end
        inf.seekg(0, std::ios::beg);   // move to beginning
        inf.seekg(0, std::ios::end);   // move to end
        // *warning*: for text, seeking to a position other than the beginning may break up a newline
        // newlines are abstractions over Windows encoding them as CRLF (2 bytes) vs Unix encoding them as LF (1 byte), so seeking past a newline will take a variable number of bytes depending on how the file was encoded
        // also some OSes pad the end of files with trailing zero bytes, so seeking to the end of the file, or an offset based off the end of the file, will produce different results on those files
    }
    {
        // example of using seekg() with a 4-line Sample.txt:
        std::ifstream inf { "Sample4.txt" };
        if (!inf) {
            std::cerr << "Uh oh Sample4.txt could not be opened for reading!\n";
            return 1;
        }

        std::string str_data {};
        inf.seekg(5); // move to 5th character
        std::getline(
            inf,
            str_data); // gets the rest of the line and reads it into the string, moving to line 2
        std::cout << str_data << "\n"; // prints "is line 1"

        inf.seekg(8, std::ios::cur); // move 8 more bytes into file
        std::getline(inf, str_data);
        std::cout << str_data << "\n"; // prints "line 2"

        inf.seekg(-14, std::ios::end); // move 14 bytes before end of the file
        std::getline(inf, str_data);
        std::cout << str_data
                  << "\n"; // undefined behavior depending on newline encoding
    }
    {
        // seekg and seekp work better on binary files; to open a file in binary mode use the appropriate flag:
        std::ifstream inf { "Sample.txt", std::ifstream::binary };
    }
    {
        // tellg() and tellp() return the absolute position of the file pointer; they can be used to determine the size of a file:
        std::ifstream inf { "Sample4.txt" };
        inf.seekg(0, std::ios::end);
        std::cout << "Sample4.txt file size: " << inf.tellg()
                  << "\n"; // should print 60 on unix
    }
    {

        // an fstream can both read or write at the same time, but once a read or write has taken place, the only way to switch between the two is to perform an operation that modifies the file position, e.g. a seek; if we don't want to actually move the file pointer, we can just seek to the current position using `iofile.seekg(iofile.tellg(), std::ios::beg)`
        // `inf.seekg(0, std::ios::cur)` might work but might be optimized away by certain compilers

        // unlike ifstream, where `while (inf)` can be used to read to the end of the file, fstream requires using something like `while (iofile.get(char))`

        // this example turns any vowels it finds into "#":
        std::fstream iofile { "Sample4.txt", std::ios::in | std::ios::out };
        if (!iofile) {
            std::cerr << "Uh oh, Sample4.txt could not be opened\n";
            return 1;
        }

        char ch_char {};

        while (iofile.get(ch_char)) {
            switch (ch_char) {
            case 'a':
            case 'e':
            case 'i':
            case 'o':
            case 'u':
            case 'A':
            case 'E':
            case 'I':
            case 'O':
            case 'U':
                iofile.seekg(-1, std::ios::cur); // back up one character
                iofile
                    << '#'; // since we did a seek now we can safely do a write
                iofile.seekg(
                    iofile.tellg(),
                    std::ios::
                        beg); // this switches us back to read mode so the next call to get() will work properly
                break;
            }
        }
    }
    // to delete a file, use remove()
    // is_open() will return true if the stream is currently open and false otherwise

    // *warning*: you can't write a pointer out to disk and expect it to point to the same data when you read it back in; a variable's address may differ from execution to execution, so addresses
    return 0;
}