#include <iostream>

struct Card {
    enum Ranks {
        ace,
        two,
        three,
        four,
        five,
        six,
        seven,
        eight,
        nine,
        jack,
        queen,
        king,
        max_ranks
    };

    enum Suits { clubs, diamonds, hearts, spades, max_suits };

    static constexpr std::array rank_codes { 'A', '2', '3', '4', '5', '6',
                                             '7', '8', '9', 'J', 'Q', 'K' };
    static constexpr std::array suit_codes { 'C', 'D', 'H', 'S' };
    static constexpr std::array all_ranks { ace,  two,  three, four,
                                            five, six,  seven, eight,
                                            nine, jack, queen, king };
    static constexpr std::array all_suits { clubs, diamonds, hearts, spades };
    static constexpr std::array rank_values { 11, 2, 3, 4,  5,  6,
                                              7,  8, 9, 10, 10, 10 };
    static_assert(std::size(rank_values) == max_ranks);
    static_assert(std::size(rank_codes) == max_ranks);
    static_assert(std::size(suit_codes) == max_suits);
    static_assert(std::size(all_ranks) == max_ranks);
    static_assert(std::size(all_suits) == max_suits);

    Ranks rank {};
    Suits suit {};

    friend std::ostream &operator<<(std::ostream &out, const Card &card) {
        out << rank_codes[card.rank] << suit_codes[card.suit];
        return out;
    }

    int value() const { return rank_values[rank]; }
};

int main() {
    Card card { Card::five, Card::hearts };
    std::cout << card << "\n";

    for (auto suit : Card::all_suits) {
        for (auto rank : Card::all_ranks) {
            std::cout << Card { rank, suit } << " ";
        }
    }
    std::cout << "\n";

    return 0;
}