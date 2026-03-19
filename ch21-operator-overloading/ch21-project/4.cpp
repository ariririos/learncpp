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

namespace UserInput {
    enum Command { Up, Left, Down, Right, Quit };
    Command get_command_from_user() {
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
            switch (command) {
            case 'w':
                return Up;
            case 'a':
                return Left;
            case 's':
                return Down;
            case 'd':
                return Right;
            case 'q':
                return Quit;
            }
        }
    }
    char command_to_char(const Command c) {
        switch (c) {
        case Up:
            return 'w';
        case Left:
            return 'a';
        case Down:
            return 's';
        case Right:
            return 'd';
        case Quit:
            return 'q';
        default:
            return '?';
        }
    }
} // namespace UserInput

int main() {
    Board board {};
    std::cout << board;

    while (true) {
        using namespace UserInput;
        Command command { get_command_from_user() };
        std::cout << "Valid command: " << command_to_char(command) << "\n";
        if (command == Quit) {
            break;
        }
    }
    std::cout << "\n\nBye\n\n";

    return 0;
}