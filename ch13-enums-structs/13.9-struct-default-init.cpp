#include "../print.cpp"

struct Something {
    int x; // no default (bad) but value-initializes to zero if initializer list provided, otherwise remains uninitialized
    int y {}; // value-initialized to zero
    int z { 2 }; // defaults to 2 unless overriden by initializer
};

std::ostream& operator<<(std::ostream& out, Something s) {
    out << "x: " << s.x << " y: " << s.y << " z: " << s.z << "\n";
    return out;
}

int main() {
    Something s {}; // x and y value-initialized, z uses default
    print(s);

    Something t { .z = 3 }; // x and y value-initialized, z overriden
    print(t);

    Something u; // bad, x remains uninitialized (y still value-initialized, z still uses default)
    print(u);

}