#include "../../Random.h"
#include <algorithm>
#include <cassert>
#include <ios>
#include <iostream>
#include <limits>

void ignore_line() {
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

namespace Settings {
    constexpr int bust_score { 21 };
    constexpr int dealer_stop_score { 17 };
} // namespace Settings

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

class Player {
private:
    int m_score {};
    int m_high_aces {};

public:
    // an constructor taking the initial score won't work here because we also need to keep track of aces
    void add_to_score(Card card) {
        m_score += card.value();
        if (card.rank == Card::ace) {
            m_high_aces++;
        }
        check_aces();
    }
    void check_aces() {
        while (m_score > Settings::bust_score && m_high_aces > 0) {
            m_high_aces--;
            m_score -= 10;
        }
    }
    int score() const { return m_score; }
};

enum GameResult { dealer_win, player_win, tie };

// true if player went bust otherwise false
bool player_turn(Deck &deck, Player &player) {
    while (player.score() <= Settings::bust_score) {
        std::cout << "(h) to hit or (s) to stand: ";
        char c {};
        std::cin >> c;
        if (!std::cin) {
            std::cin.clear();
            ignore_line();
        }
        ignore_line();
        if (c == 'h') {
            Card next_card { deck.deal_card() };
            player.add_to_score(next_card);
            std::cout << "You were dealt " << next_card
                      << ". You now have: " << player.score() << "\n";
        } else if (c == 's') {
            return false;
        } else {
            std::cout << "Invalid input\n";
        }
    }
    std::cout << "You went bust!\n";
    return true;
}

// true if dealer went bust otherwise false
bool dealer_turn(Deck &deck, Player &dealer) {
    while (dealer.score() < Settings::dealer_stop_score) {
        Card next_card { deck.deal_card() };
        dealer.add_to_score(next_card);
        std::cout << "The dealer flips a " << next_card
                  << ". They now have: " << dealer.score() << "\n";
    }
    if (dealer.score() > Settings::bust_score) {
        std::cout << "The dealer went bust!\n";
        return true;
    }
    return false;
}

// true if player winning, false if dealer is (or tie)
GameResult play_blackjack() {
    Deck deck {};
    deck.shuffle();
    Player dealer {};
    Card dealer_card { deck.deal_card() };
    dealer.add_to_score(dealer_card);
    std::cout << "The dealer is showing " << dealer_card << " ("
              << dealer.score() << ")\n";
    Player player {};
    Card player_card1 { deck.deal_card() };
    player.add_to_score(player_card1);
    Card player_card2 { deck.deal_card() };
    player.add_to_score(player_card2);
    std::cout << "You are showing " << player_card1 << " " << player_card2
              << " (" << player.score() << ")" << "\n";
    if (player_turn(deck, player)) {
        return dealer_win;
    }
    if (dealer_turn(deck, dealer)) {
        return player_win;
    }
    if (dealer.score() < player.score()) {
        return player_win;
    } else if (player.score() < dealer.score()) {
        return dealer_win;
    }
    return tie;
}

int main() {
    GameResult game { play_blackjack() };
    if (game == player_win) {
        std::cout << "You win!\n";
    } else if (game == dealer_win) {
        std::cout << "You lose!\n";
    } else {
        std::cout << "Tie!\n";
    }

    return 0;
}