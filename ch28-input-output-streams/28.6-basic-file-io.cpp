#include <fstream>
#include <iostream>

int main() {
    // there are 3 basic file i/o classes in c++ (<fstream>): ifstream (derived from istream), ofstream (derived from ostream), fstream (derived from iostream)
    // file streams need to be set up explicitly with the name of the file as a parameter, then use << or >> to write to/read from the file, and finally close it by either using .close() or by letting it go out of scope

    // file output:
    {
        std::ofstream outf { "Sample.txt" };

        if (!outf) {
            std::cerr << "Uh oh Sample.txt could not be opened for writing\n";
            return 1;
        }

        outf << "This is line 1\n";
        outf << "This is line 2\n";
        // we can also use .put() to write a single character to the file
    }

    // file input:
    {
        // ifstream returns a 0 if we're reached EOF
        std::ifstream inf { "Sample.txt" };
        if (!inf) {
            std::cerr << "Uh oh Sample.txt could not be opened for reading\n";
            return 1;
        }

        std::string str_input {};
        while (inf >> str_input) { // while there's still file left to read
            std::cout << str_input << "\n";
        }
        // but this will print the file with newlines between every word
    }
    {
        std::ifstream inf { "Sample.txt" };
        if (!inf) {
            std::cerr << "Uh oh Sample.txt could not be opened for reading\n";
            return 1;
        }
        // to read in entire lines we can use std::getline instead:
        std::string str_input {};
        while (std::getline(inf, str_input)) {
            std::cout << str_input << "\n";
        }
    }

    // output in c++ may be buffered; we can flush the buffer using ostream::flush(), by sending std::flush to the output stream, by using std::endl, or by using the destructor on the file object
    // this can become an issue if we exit the program early whether by crashing or by calling exit(), so the destructors for the file classes won't run, and the files are never closed, so their buffers are never flushed
    // overusing std::endl can cause performance problems since the buffer will be flushed on each one, so '\n' is often used for performance

    // file modes allow us to change the default behavior of overwriting the file each time; we set them using a second parameter to the file constructor
    // the modes live in std::ios and are:
    // app: open in append mode
    // ate: seeks to the end of the file before reading/writing
    // binary: open in binary mode (instead of text mode)
    // in: open in read mode (default for ifstream)
    // out: open in write mode (default for ofstream)
    // trunc: erase the file if it already exists

    // multiple flags can be specified by bitwise ORing them together; ifstream defaults to std::ios::in, ofstream defaults to std::ios::out, and fstream defaults to std::ios::in | std::ios::out
    // fstream may fail if std::ios::in is used and the file being opened doesn't exist; if we need to create a new file using fstream, we'll need to use std::ios::out mode only

    // example of appending to an existing file:
    std::ofstream outf {
        "Sample.txt", std::ios::app
    }; // std::ios::out doesn't need to be passed because ofstream defaults to it

    if (!outf) {
        std::cerr << "Uh oh Sample.txt could not be opened for writing\n";
        return 1;
    }

    outf << "This is line 3\n";
    outf << "This is line 4\n";

    // a file stream can also be opened with open() the same way it can be closed with close(); it has the same signature as the constructor, taking a filename and file mode
    outf.close();

    outf.open("Sample.txt", std::ios::app);
    outf << "This is line 5\n";
    outf.close();

    return 0;
}