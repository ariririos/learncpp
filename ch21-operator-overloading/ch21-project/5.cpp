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

class Board {
public:
    static constexpr int s_size { 4 };
    using BoardArray = Tile[s_size][s_size];

    Board() {
        for (std::size_t i { 0 }; i < s_size; i++) {
            for (std::size_t j { 0 }; j < s_size; j++) {
                if (!(i == 3 && j == 3)) {
                    m_board[i][j] =
                        Tile(static_cast<int>(s_size * i + (j + 1)));
                } else {
                    m_board[i][j] = Tile(0);
                }
            }
        }
    }
    const BoardArray &get_board() const { return m_board; }

private:
    BoardArray m_board {};
};

std::ostream &operator<<(std::ostream &out, const Board &b) {
    for (int i { 0 }; i < g_console_lines; i++) {
        out << "\n";
    }
    for (std::size_t i { 0 }; i < b.s_size; i++) {
        for (std::size_t j { 0 }; j < b.s_size; j++) {
            out << b.get_board()[i][j];
        }
        std::cout << "\n";
    }
    std::cout << "\n";
    return out;
}

class Direction {
public:
    enum Type { up, down, left, right, max_directions };

private:
    Type m_dir {};

public:
    Direction(Type dir) : m_dir { dir } {}
    Direction operator-() {
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
    char direction_to_char(const Direction &d) {
        switch (d.get_direction()) {
        case Direction::up:
            return 'w';
        case Direction::left:
            return 'a';
        case Direction::down:
            return 's';
        case Direction::right:
            return 'd';
        case Direction::max_directions:
            return '?';
        default:
            assert(false && "Invalid direction");
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
    std::cout << board;

    std::cout << "Generating random direction... "
              << Direction::get_random_direction() << "\n";
    std::cout << "Generating random direction... "
              << Direction::get_random_direction() << "\n";
    std::cout << "Generating random direction... "
              << Direction::get_random_direction() << "\n";
    std::cout << "Generating random direction... "
              << Direction::get_random_direction() << "\n";

    std::cout << "Enter a command: ";
    while (true) {
        using namespace UserInput;
        char command { get_command_from_user() };
        if (command == 'q') {
            break;
        }
        std::cout << "You entered direction: "
                  << UserInput::char_to_direction(command) << "\n";
    }
    std::cout << "\n\nBye!\n\n";

    return 0;
}