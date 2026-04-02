#include "../../Random.h"
#include <cassert>
#include <cctype>
#include <iostream>
#include <limits>
#include <string>

class Creature {
protected:
    std::string m_name {};
    char m_symbol {};
    int m_health {};
    int m_attack {};
    int m_gold {};

public:
    Creature(std::string_view name, char symbol, int health, int attack,
             int gold)
        : m_name { name }, m_symbol { symbol }, m_health { health },
          m_attack { attack }, m_gold { gold } {}
    const std::string &get_name() const { return m_name; }
    char get_symbol() const { return m_symbol; }
    int get_health() const { return m_health; }
    int get_attack() const { return m_attack; }
    int get_gold() const { return m_gold; }
    void reduce_health(int value) { m_health -= value; }
    bool is_dead() const { return m_health <= 0; }
    void add_gold(int gold) { m_gold += gold; }
};

class Player : public Creature {
private:
    int m_level { 1 };

public:
    Player(std::string_view name) : Creature { name, '@', 10, 1, 0 } {}
    int get_level() const { return m_level; }
    void level_up() {
        ++m_level;
        ++m_attack;
    }
    bool has_won() const { return m_level >= 20; }
};

class Monster : public Creature {
public:
    enum Type { dragon, orc, slime, max_types };

private:
    static inline Creature monster_data[] { { "dragon", 'D', 20, 4, 100 },
                                            { "orc", 'o', 4, 2, 25 },
                                            { "slime", 's', 1, 1, 10 } };
    static_assert(std::size(monster_data) == max_types);

public:
    Monster(Type type) : Creature { monster_data[type] } {}
    static Monster get_random_monster() {
        int monster_idx { Random::get(0, max_types - 1) };
        return Monster { static_cast<Type>(monster_idx) };
    }
};

void ignore_line() {
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

bool handle_cin_error() {
    if (!std::cin) {
        if (std::cin.eof()) {
            std::exit(0);
        }
        std::cin.clear();
        ignore_line();
        return false;
    }
    return true;
}

void attack_player(Player &player, const Monster &monster) {
    assert(!monster.is_dead() && "Dead monsters can't attack!");
    player.reduce_health(monster.get_attack());
    std::cout << "The " << monster.get_name() << " hit you for "
              << monster.get_attack() << " damage.\n";
}

void attack_monster(Player &player, Monster &monster) {
    assert(!player.is_dead() && "Dead players can't attack!");
    monster.reduce_health(player.get_attack());
    std::cout << "You hit the " << monster.get_name() << " for "
              << player.get_attack() << " damage.\n";
    if (monster.is_dead()) {
        player.add_gold(monster.get_gold());
        player.level_up();
        std::cout << "You killed the " << monster.get_name() << ".\n";
        std::cout << "You found " << monster.get_gold() << " gold.\n";
        std::cout << "You are now level " << player.get_level() << ".\n";
    }
}

void fight_monster(Player &player, Monster &monster) {
    while (!player.is_dead() && !monster.is_dead()) {
        std::cout << "(R)un or (F)ight: ";
        char action {};
        do {
            std::cin >> action;
        } while (!handle_cin_error() &&
                 (tolower(action) != 'r' || tolower(action) != 'f'));
        if (action == 'r') {
            bool successful_escape { static_cast<bool>(Random::get(0, 1)) };
            if (!successful_escape) {
                std::cout << "You failed to flee.\n";
                attack_player(player, monster);
            } else {
                std::cout << "You successfully fled.\n";
                return; // end the fight
            }
        } else if (action == 'f') {
            attack_monster(player, monster);
            if (!monster.is_dead()) {
                attack_player(player, monster);
            }

        } else {
            assert(false && "input can only be r or f");
        }
    }
}

int main() {
    std::cout << "Enter your name: ";
    std::string name {};
    do {
        std::cin >> name;
    } while (!handle_cin_error());

    Player player { name };

    std::cout << "Welcome, " << player.get_name() << "\n";
    while (!player.has_won() && !player.is_dead()) {
        Monster random_monster { Monster::get_random_monster() };
        std::cout << "You have encountered a " << random_monster.get_name()
                  << " (" << random_monster.get_symbol() << ").\n";
        fight_monster(player, random_monster);
    }

    if (player.has_won()) {
        std::cout << "You won with " << player.get_gold() << " gold!\n";
    } else if (player.is_dead()) {
        std::cout << "You died at level " << player.get_level() << " and with "
                  << player.get_gold()
                  << " gold.\nToo bad you can't take it with you!\n";
    } else {
        assert(false &&
               "Player should either have won or be dead at this point");
    }

    return 0;
}