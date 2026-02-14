#include <iostream>

class Foo {
private:
    int m_x {};
    int m_y {};

public:
    Foo(int x, int y) {
        std::cout << "Foo(" << x << ", " << y << ") constructed\n";
    }

    void print() const {
        std::cout << "Foo(" << m_x << ", " << m_y << ")\n"; // wrong because constructor does not initialize the private data members
    }
};

int main() {
    Foo foo { 6, 7 };
    foo.print();

    return 0;
}