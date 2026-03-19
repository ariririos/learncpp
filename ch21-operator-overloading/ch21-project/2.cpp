#include <iostream>

class Tile {
private:
    int m_num {};

public:
    Tile() = default;
    explicit Tile(int num) : m_num { num } {}
    int get_num() const { return m_num; }
    bool is_empty() const { return m_num == 0; }
};

std::ostream &operator<<(std::ostream &out, const Tile &t) {
    int value { t.get_num() };
    if (value == 0) {
        out << "    ";
        return out;
    }
    if (value > 9) {
        out << " ";
    } else {
        out << "  ";
    }
    out << value << " ";
    return out;
}

int main() {
    Tile tile1 { 10 };
    Tile tile2 { 8 };
    Tile tile3 { 0 }; // the missing tile
    Tile tile4 { 1 };

    std::cout
        << "0123456789ABCDEF\n"; // to make it easy to see how many spaces are in the next line
    std::cout << tile1 << tile2 << tile3 << tile4 << '\n';

    std::cout << std::boolalpha << tile1.is_empty() << ' ' << tile3.is_empty()
              << '\n';
    std::cout << "Tile 2 has number: " << tile2.get_num()
              << "\nTile 4 has number: " << tile4.get_num() << '\n';

    return 0;
}