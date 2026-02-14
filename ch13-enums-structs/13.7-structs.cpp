#include <iostream>
#define print(x, ...) { std::cout << #x << " = " << x; __VA_OPT__(std::cout , __VA_ARGS__;) std::cout << std::endl; }

template <typename T>
std::ostream& operator,(std::ostream& out, const T& t) {
    out << " " << t;
    return out;
}

std::ostream& operator,(std::ostream& out, std::ostream&(*f)(std::ostream&)) {
    out << f;
    return out;
}

struct Employee {
    int id {};
    int age {};
    double wage {};
};

int main() {
    Employee joe {};

    joe.id = 14;
    joe.age = 32;
    joe.wage = 60000.0;

    Employee frank {};
    frank.id = 15;
    frank.age = 28;
    frank.wage = 45000.0;

    int total_age { joe.age + frank.age };

    std::cout << "Joe and Frank have lived " << total_age << " total years\n";

    if (joe.wage > frank.wage) {
        std::cout << "Joe makes more than Frank\n";
    }
    else if (joe.wage < frank.wage) {
        std::cout << "Joe makes less than Frank\n";
    }
    else {
        std::cout << "Joe and Frank make the same amount\n";
    }

    frank.wage += 5000.0;

    ++joe.age;

    print(frank.id);
    print(joe.id);

    return 0;
}