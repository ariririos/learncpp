#include <cstdarg>
#include <iostream>

double find_average(int count, ...) {
    int sum { 0 };
    // need to declare a std::va_list to access the ellipsis
    std::va_list list;
    // we initialize the va_list using the list as the first argument and the last non-ellipsis argument as the second
    va_start(list, count);
    for (int arg { 0 }; arg < count; arg++) {
        sum += va_arg(list, int);
    }
    // clean up
    va_end(list);
    // va_start can be called whenever to reset the va_list to point to the first parameter in the ellipsis again
    return static_cast<double>(sum) / count;
}

double find_average_sentinel(int first, ...) {
    int sum { first };
    std::va_list list;
    va_start(list, first);

    int count { 1 };
    while (true) {
        int arg { va_arg(list, int) };
        if (arg == -1) {
            break;
        }
        sum += arg;
        count++;
    }
    va_end(list);
    return static_cast<double>(sum) / count;
}

double find_average_decoder(std::string_view decoder, ...) {
    double sum { 0 };
    std::va_list list;
    va_start(list, decoder);

    for (auto codetype : decoder) {
        switch (codetype) {
        case 'i':
            sum += va_arg(list, int);
            break;
        case 'd':
            sum += va_arg(list, double);
            break;
        }
    }
    va_end(list);
    return sum / static_cast<double>(std::size(decoder));
}

int main() {
    // ellipses allow passing a variable number of arguments to a function; they must appear as the last argument and hold any additional arguments beyond the last named argument
    std::cout << find_average(5, 1, 2, 3, 4, 5) << "\n";
    std::cout << find_average(6, 1, 2, 3, 4, 5, 6) << "\n";

    // ellipses should generally be avoided because they circumvent type checking
    std::cout << find_average(6, 1.0, 2, 3, 4, 5, 6)
              << "\n"; // this prints garbage
    // this happens because va_arg reads the bytes as the type given, so assuming 8-bit doubles and 4-bit ints, it reads the first half of "1.0" as an int and the second half as another int

    // ellipses also don't know how many parameters were passed, so our options look like:
    // - passing a length parameter (as above)
    // - using a sentinel value (e.g. -1)
    std::cout << find_average_sentinel(1, 2, 3, 4, 5, 6, -1) << "\n";
    // - using a decoder string
    std::cout << find_average_decoder("iiiii", 1, 2, 3, 4, 5) << "\n";
    std::cout << find_average_decoder("iiiiii", 1, 2, 3, 4, 5, 6) << "\n";
    std::cout << find_average_decoder("iiddi", 1, 2, 3.5, 4.5, 5) << "\n";
    // this is what printf does

    // recommendations for ellipses:
    // - we could have passed a dynamically sized array of ints instead
    // - we should try to make sure all arguments are the same type
    // - count parameter and decoder strings are safer than using a sentinel
    // - parameter packs, variadic templates, and c++17 fold expressions make ellipses a viable option
    return 0;
}