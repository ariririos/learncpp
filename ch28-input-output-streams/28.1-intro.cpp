int main() {
    // I/O in c++ is implemented with streams, which are at their most basic just a (potentially infinite) sequence of bytes that can be accessed sequentially
    // input and output streams can both buffer, e.g. if the program isn't ready for input from the terminal or if a printer isn't ready for output from the program

    // streams provide a singular interface for many different types of input/output where the actual interaction with the underlying device is handled by the OS

    // `ios` is a typedef for `std::basic_ios<char>` which provides functionality common between input/output streams
    // `istream` is the primary class used for input streams, and `>>` is the operator used to remove values from the stream
    // `ostream` is the primary class used for output streams, and `<<` is the operator used to put values into the stream
    // `iostream` can handle both input and output, allowing bidirectional I/O

    // there are four standard streams that are already pre-connected provided to a program by its environment:
    // - cin, an istream tied to standard input
    // - cout, an ostream tied to standard output
    // - cerr, an ostream tied to standard error, unbuffered
    // - clog, an ostream tied to standard error, buffered

    return 0;
}