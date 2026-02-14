#include <iostream>
#include <bitset>
#define print_expr(x) { std::cout << #x << " = " << x << "\n"; }

enum Color {
    red,
    green,
    blue,
};

enum Pet {
    cat,
    dog,
    pig,
    whale
};

enum Result {
    ok,
    err
};

Result read_file() {
    return ok;
}

enum FileType {
    regular,
    link,
    directory,
};

void read_file(FileType file_type) {
    switch (file_type) {
        case regular:
            std::cout << "Regular file\n";
        break;
        case link:
            std::cout << "Symbolic link\n";
        break;
        case directory:
            std::cout << "Directory\n";
        break;
    }
}

namespace Flags {
    enum State {
        is_hungry,
        is_sad,
        is_mad,
        is_happy,
        is_laughing,
        is_asleep,
        is_dead,
        is_crying
    };
}

int main() {
    Color apple { red };
    Color shirt { green };
    Color cup { blue };

    Pet my_pet { cat };

    Result file_result = read_file();
    if (file_result == ok) {
        std::cout << "File read successful\n";
    }
    else {
        std::cout << "File read unsuccessful\n";
    }

    read_file(regular);
    read_file(link);
    read_file(directory);
    read_file(FileType::regular);

    std::bitset<8> me {};
    me.set(Flags::is_happy);
    me.set(Flags::is_laughing);

    std::cout << me << "\n";

    std::cout << std::boolalpha;

    std::cout << "Happy? " << me.test(Flags::is_happy) << "\n";
    std::cout << "Laughing? " << me.test(Flags::is_laughing) << "\n";

    return 0;
}