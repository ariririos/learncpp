#include "../print.cpp"

struct Employee {
    int id {};
    int age {};
    double wage {};
};

struct Point {
    double x {};
    double y {};
};

struct Triangle {
    Point* a {};
    Point* b {};
    Point* c {};
};

struct Paw {
    int claws {};
};

struct Animal {
    std::string name {};
    Paw paw {};
};

int main() {
    Employee joe { 1, 34, 65000.0 };
    ++joe.age;
    joe.wage = 68000.0;

    Employee* ptr { &joe };
    print((*ptr).id);
    print(ptr->id);

    Point a { 1, 2 };
    Point b { 3, 7 };
    Point c { 10, 2 };
    Triangle tr { &a, &b, &c };
    Triangle* tr_ptr { &tr };

    print((*(*tr_ptr).c).y);
    print(tr_ptr -> c -> y);

    Animal puma { "Puma", { 5 }};
    Animal* animal_ptr { &puma };

    print((animal_ptr -> paw).claws, "\n");

    return 0;
}