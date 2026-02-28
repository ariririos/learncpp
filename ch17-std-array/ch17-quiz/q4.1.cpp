#include "../../Random.h"
#include <algorithm>
#include <cassert>
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
        ten,
        jack,
        queen,
        king,
        max_ranks
    };

    enum Suits { clubs, diamonds, hearts, spades, max_suits };

    static constexpr std::array rank_codes { 'A', '2', '3', '4', '5', '6', '7',
                                             '8', '9', 'T', 'J', 'Q', 'K' };
    static constexpr std::array suit_codes { 'C', 'D', 'H', 'S' };
    static constexpr std::array all_ranks { ace,  two,   three, four, five,
                                            six,  seven, eight, nine, ten,
                                            jack, queen, king };
    static constexpr std::array all_suits { clubs, diamonds, hearts, spades };
    static constexpr std::array rank_values { 11, 2, 3,  4,  5,  6, 7,
                                              8,  9, 10, 10, 10, 10 };
    static_assert(std::size(rank_values) == max_ranks);
    static_assert(std::size(rank_codes) == max_ranks);
    static_assert(std::size(suit_codes) == max_suits);
    static_assert(std::size(all_ranks) == max_ranks);
    static_assert(std::size(all_suits) == max_suits);
    static constexpr int cards_per_deck { static_cast<int>(max_ranks) *
                                          static_cast<int>(max_suits) };

    Ranks rank {};
    Suits suit {};

    friend std::ostream &operator<<(std::ostream &out, const Card &card) {
        out << rank_codes[card.rank] << suit_codes[card.suit];
        return out;
    }

    int value() const { return rank_values[rank]; }
};

class Deck {
private:
    std::size_t m_deck_index {};
    std::array<Card, Card::cards_per_deck> m_cards {};

public:
    Deck() {
        std::size_t index { 0 };
        for (auto suit : Card::all_suits) {
            for (auto rank : Card::all_ranks) {
                m_cards[index++] = Card { rank, suit };
            }
        }
    }
    Card deal_card() {
        assert(m_deck_index < 52 && "No more cards");
        return m_cards[m_deck_index++];
    }
    void shuffle() {
        std::shuffle(m_cards.begin(), m_cards.end(), Random::mt);
        m_deck_index = 0;
    }
};

struct Player {
    int score {};
};

// true if player winning, false if dealer is (or tie)
bool play_blackjack() {
    Deck deck {};
    deck.shuffle();
    Player dealer { deck.deal_card().value() };
    std::cout << "The dealer is showing: " << dealer.score << "\n";
    Player player { deck.deal_card().value() + deck.deal_card().value() };
    std::cout << "You have score: " << player.score << "\n";

    return dealer.score < player.score;
}

int main() {
    if (play_blackjack()) {
        std::cout << "You win!\n";
    } else {
        std::cout << "You lose!\n";
    }

    return 0;
}