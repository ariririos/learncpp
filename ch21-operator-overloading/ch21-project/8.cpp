#include "../../Random.h"
#include <cassert>
#include <iostream>
#include <limits>

constexpr int g_console_lines { 25 };

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

class Direction {
public:
    enum Type { up, down, left, right, max_directions };

private:
    Type m_dir {};

public:
    Direction(Type dir) : m_dir { dir } {}
    Direction operator-() const {
        switch (m_dir) {
        case up:
            return down;
        case down:
            return up;
        case left:
            return right;
        case right:
            return left;
        case max_directions:
            return max_directions;
        }
        assert(false && "Invalid direction");
    }
    Type get_direction() const { return m_dir; }
    friend std::ostream &operator<<(std::ostream &out, const Direction &d);
    static Direction get_random_direction() {
        int index { Random::get(0, Type::max_directions - 1) };
        return static_cast<Type>(index);
    }
};

std::ostream &operator<<(std::ostream &out, const Direction &d) {
    switch (d.m_dir) {
    case Direction::up:
        out << "up";
        break;
    case Direction::down:
        out << "down";
        break;
    case Direction::left:
        out << "left";
        break;
    case Direction::right:
        out << "right";
        break;
    case Direction::max_directions:
        out << "???";
        break;
    default:
        assert(false && "Invalid direction");
        out << "Invalid direction";
    }
    return out;
};

struct Point {
    int x;
    int y;
    Point get_adjacent_point(const Direction &d) const {
        using enum Direction::Type;
        switch (d.get_direction()) {
        case up:
            return Point { x, y - 1 };
        case down:
            return Point { x, y + 1 };
        case left:
            return Point { x - 1, y };
        case right:
            return Point { x + 1, y };
        case max_directions:
            assert(false && "Invalid direction max_directions");
            return *this;
        default:
            assert(false && "Invalid direction");
            return *this;
        }
    }
};

bool operator==(const Point p1, const Point p2) {
    return p1.x == p2.x && p1.y == p2.y;
}

bool operator!=(const Point p1, const Point p2) { return !operator==(p1, p2); }

class Board {
public:
    static constexpr int s_size { 4 };
    using BoardArray = Tile[s_size][s_size];

    Board() {
        for (std::size_t y { 0 }; y < s_size; y++) {
            for (std::size_t x { 0 }; x < s_size; x++) {
                if (!(y == 3 && x == 3)) {
                    m_board[y][x] =
                        Tile(static_cast<int>(s_size * y + (x + 1)));
                } else {
                    m_board[y][x] = Tile(0);
                }
            }
        }
    }
    const BoardArray &get_board() const { return m_board; }
    static bool is_valid_point(Point p) {
        return p.x >= 0 && p.x < s_size && p.y >= 0 && p.y < s_size;
    }
    Point find_empty_tile() {
        for (std::size_t y { 0 }; y < s_size; y++) {
            for (std::size_t x { 0 }; x < s_size; x++) {
                if (m_board[y][x].is_empty()) {
                    return Point { static_cast<int>(x), static_cast<int>(y) };
                }
            }
        }
        assert(false && "Empty tile missing");
        return Point { -1, -1 };
    }
    void swap_tiles(const Point p1, const Point p2) {
        std::swap(m_board[p1.y][p1.x], m_board[p2.y][p2.x]);
    }
    bool move_tile(const Direction &d) {
        Point empty_tile { find_empty_tile() };
        Point empty_adjacent_tile { empty_tile.get_adjacent_point(-d) };
        if (is_valid_point(empty_adjacent_tile)) {
            swap_tiles(empty_tile, empty_adjacent_tile);
            return true;
        }
        return false;
    }
    void randomize() {
        for (int i { 0 }; i < 1000; i++) {
            move_tile(Direction::get_random_direction());
        }
    }
    bool operator==(const Board &other) const {
        for (std::size_t y { 0 }; y < Board::s_size; y++) {
            for (std::size_t x { 0 }; x < Board::s_size; x++) {
                if (m_board[y][x].get_num() !=
                    other.get_board()[y][x].get_num()) {
                    return false;
                }
            }
        }
        return true;
    }
    bool player_won() {
        Board winning_board {};
        return *this == winning_board;
    }

private:
    BoardArray m_board {};
};

std::ostream &operator<<(std::ostream &out, const Board &b) {
    for (int i { 0 }; i < g_console_lines; i++) {
        out << "\n";
    }
    for (std::size_t y { 0 }; y < b.s_size; y++) {
        for (std::size_t x { 0 }; x < b.s_size; x++) {
            out << b.get_board()[y][x];
        }
        std::cout << "\n";
    }
    std::cout << "\n";
    return out;
}

namespace UserInput {
    char get_command_from_user() {
        while (true) {
            char command {};
            std::cin >> command;
            if (!std::cin) {
                if (std::cin.eof()) {
                    std::exit(0);
                }
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(),
                                '\n');
            }
            if (command == 'w' || command == 'a' || command == 's' ||
                command == 'd' || command == 'q') {
                return command;
            }
        }
    }
    Direction char_to_direction(const char c) {
        switch (c) {
        case 'w':
            return Direction::up;
        case 'a':
            return Direction::left;
        case 's':
            return Direction::down;
        case 'd':
            return Direction::right;
        default:
            assert(false && "Invalid char for direction");
            return Direction::max_directions;
        }
    }
} // namespace UserInput

int main() {
    Board board {};
    board.randomize();
    std::cout << board;

    std::cout << "Enter a command: ";
    while (true) {
        using namespace UserInput;
        char command { get_command_from_user() };
        if (command == 'q') {
            break;
        }
        if (board.move_tile(UserInput::char_to_direction(command))) {
            std::cout << board;
        }
        if (board.player_won()) {
            std::cout << "You won!\n";
            break;
        }
    }
    std::cout << "\n\nBye!\n\n";
    return 0;
}