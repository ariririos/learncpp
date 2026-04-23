#include <algorithm>
#include <charconv>
#include <ios>
#include <iostream>
#include <limits>
#include <map>
#include <string_view>

bool is_valid_name(std::string_view name) {
    return std::ranges::all_of(
        name, [](char ch) { return std::isalpha(ch) || std::isspace(ch); });
}

bool input_matches(std::string_view input, std::string_view pattern) {
    if (input.length() != pattern.length()) {
        return false;
    }

    static const std::map<char, int (*)(int)> validators {
        { '#', std::isdigit },
        { '_', std::isspace },
        { '@', std::isalpha },
        { '?', [](int) { return 1; } }
    };

    return std::ranges::equal(input, pattern, [](char ch, char mask) -> bool {
        auto found { validators.find(mask) };

        if (found !=
            validators.end()) { // if the pattern's current element was found
            return (*found->second)(ch); // call the function
        }

        return ch == mask;
    });
}

std::optional<int> extract_age(std::string_view age) {
    int result {};
    const auto end {
        age.data() + age.length()
    }; // get end iterator of underlying C-style string

    // try to parse an int from `age`

    // if we got an error, return nothing
    if (std::from_chars(age.data(), end, result).ec != std::errc {}) {
        return {};
    }

    // if age isn't positive, return nothing
    if (result <= 0) {
        return {};
    }

    return result; // otherwise return an int
}

int main() {
    // ios_base contains several flags to signal stream state:
    // - goodbit: everything's good
    // - badbit: fatal error (e.g. tried to read past the end of the file)
    // - eofbit: stream has reached end of file
    // - failbit: nonfatal error (e.g. entering letters when the program expected an integer)

    // ios derives from ios_base so these are typically accessed through ios

    // ios provides some member functions to access these states:
    // - bool good(): returns goodbit state
    // - bool bad(): returns badbit state
    // - bool eof(): returns eofbit state
    // - bool fail() returns failbit state
    // - clear(): clears all flags and restores the stream to the goodbit state
    // - clear(state): clears all flags and sets the state flag passed in
    // - rdstate(): returns the currently set flags
    // - setstate(state): sets the state flag passed in

    // failbit is most commonly used, and is triggered when invalid input is entered; for example, entering character data into an int:
    // std::cout << "Enter your age: ";
    // int age {};
    // std::cin >> age;
    // if an error occurs and the stream is set to anything other than goodbit, further stream operations will be ignored; it can be cleared via clear()

    // for validating string input, we could use regex (<regex>), but performance is better if we manually verify using functions that check for specific numbers or characters; for numerical validation, we not only need to check that numbers are within a certain range, but also need to handle things that aren't numbers at all
    // <cctype> has the validation functions we can use, which return non-zero if their parameters are:
    // - std::isalnum(int): alphanumeric
    // - std::isalpha(int): a letter
    // - std::iscntrl(int): a control character
    // - std::isdigit(int): a digit
    // - std::isgraph(int): a printable non-whitespace character
    // - std::isprint(int): a printable character, including whitespace
    // - std::ispunct(int): neither alphanumeric nor whitespace
    // - std::isspace(int): whitespace
    // - std::isxdigit(int): hexadecimal digit (0-9, a-f, A-F)

    // example of string validation: we'll ask the user to enter their name, and step through each character (using std::all_of), and check that it's alphabetical or whitespace
    std::string name {};
    do {
        std::cout << "Enter your name: ";
        std::getline(std::cin, name);
    } while (!is_valid_name(name));

    std::cout << "Hello " << name << "!\n";

    std::string phone_number {};
    do {
        std::cout << "Enter a phone number (###) ###-####: ";
        std::getline(std::cin, phone_number);
    } while (!input_matches(phone_number, "(###) ###-####"));

    std::cout << "You entered: " << phone_number << "\n";
    // this function has a few problems however: #, @, _, and ? are no longer valid characters in the input; unlike with regex, there's no template symbol that means "a variable number of characters can be entered", so there's no way to create a pattern that looks for two words separated by whitespace because a "word" can't be represented by the pattern

    // for numeric validation we need to check both the failbit for non-numeric input and if valid, the actual input for validity
    int age {};
    while (true) {
        std::cout << "Enter your age: ";
        std::cin >> age;

        if (std::cin.fail()) { // no extraction took place
            std::cin
                .clear(); // reset the state back to goodbit so we can use ignore()
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(),
                            '\n'); // clear out the bad input from the stream
            continue;
        }
        std::cin.ignore(
            std::numeric_limits<std::streamsize>::max(),
            '\n'); // clear out any additional input from the stream (e.g. if 123abc was entered, 123 will be extracted and abc will be ignored)

        // if instead of just ignoring extraneous input, we want to have it make the whole thing invalid, we can count how many characters were ignored and bail out if it's more than one (the '\n')
        if (std::cin.gcount() > 1) {
            continue;
        }

        if (age <= 0) {
            continue;
        }

        break;
    }

    std::cout << "You entered: " << age << "\n";

    // we could also do the same thing by reading the input as a string and then trying to convert it to a number
    int age2 {};
    while (true) {
        std::cout << "Enter your age: ";
        std::string str_age {};

        // try to get a line of input
        if (!std::getline(std::cin >> std::ws, str_age)) {
            // if it failed, clean up and try again
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }

        auto extracted { extract_age(str_age) };

        if (!extracted) {
            continue;
        }

        age2 = *extracted;
        break;
    }

    std::cout << "You entered: " << age2 << "\n";

    return 0;
}