#include <iostream>

std::string get_name(int index) {
    std::cout << "Enter the name of person #" << index << ": ";
    std::string name;
    std::getline(std::cin >> std::ws, name);
    return name;
}

int get_age(std::string_view name) {
    std::cout << "Enter the age of " << name << ": ";
    int age;
    std::cin >> age;
    return age;
}

void print_older(std::string older_name, int older_age,
                 std::string younger_name, int younger_age) {
    std::cout << older_name << " (age " << older_age << ") is older than "
              << younger_name << " (age " << younger_age << ").\n";
}

int main() {
    const std::string name1 = get_name(1);
    const int age1 = get_age(name1);

    const std::string name2 = get_name(2);
    const int age2 = get_age(name2);

    if (age1 > age2) {
        print_older(name1, age1, name2, age2);

    } else {
        print_older(name2, age2, name1, age1);
    }

    return 0;
}