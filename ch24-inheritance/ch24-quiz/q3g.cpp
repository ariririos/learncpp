/*
changes from assignment:
- luck mechanic influences chance of fleeing, chance of finding a potion, and chance of lifesteal
- lifesteal allows you to steal a monster's health on the final blow
- luck potion influences your luck mechanic
- strength potion now varies based on size
- poison potion now takes a set percentage of your health based on its size, no effect from luck
*/

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

class Potion {
public:
    enum Type { health, strength, poison, luck, max_types };

private:
    Type m_type {};
    int m_size {};
    std::string m_name {};
    std::string m_size_name {};

public:
    Potion(Type type, int size) : m_type { type }, m_size { size } {
        assert(0 <= size && size <= 2 && "Size out of range [0, 2]");
        switch (type) {
        case health:
            m_name = "Health";
            break;
        case strength:
            m_name = "Strength";
            break;
        case poison:
            m_name = "Poison";
            break;
        case luck:
            m_name = "Luck";
            break;
        case max_types:
            assert(false && "Invalid potion type");
        }
        switch (size) {
        case 0:
            m_size_name = "Small";
            break;
        case 1:
            m_size_name = "Medium";
            break;
        case 2:
            m_size_name = "Large";
            break;
        }
    }
    const std::string &get_name() { return m_name; }
    Type get_type() { return m_type; }
    int get_size() { return m_size; }
    const std::string &get_size_name() { return m_size_name; }
    static Potion get_random_potion() {
        int potion_idx { Random::get(0, max_types - 1) };
        int potion_size { Random::get(0, 2) };
        return Potion { static_cast<Type>(potion_idx), potion_size };
    }
};

class Player : public Creature {
private:
    int m_level { 1 };
    int m_luck {
        1
    }; // luck influences chance of fleeing, finding potions, and lifesteal; flee chance: 100 - (50 / luck)%; potion chance: 100 - (70 / luck)%; lifesteal chance: 100 - (80 / luck)%

public:
    Player(std::string_view name) : Creature { name, '@', 10, 1, 0 } {}
    int get_level() const { return m_level; }
    int get_luck() const { return m_luck; }
    void level_up() {
        ++m_level;
        ++m_attack;
    }
    bool has_won() const { return m_level >= 20; }
    void increase_health(int value) { m_health += value; }
    void drink_potion(Potion potion) {
        int potion_size { potion.get_size() };
        switch (potion.get_type()) {
        case Potion::health:
            if (potion_size == 0 || potion_size == 1) {
                m_health += 2;
            } else if (potion_size == 2) {
                m_health += 3;
            }
            break;
        case Potion::strength:
            m_attack += (potion_size + 1);
            break;
        case Potion::poison:
            m_health = static_cast<int>(m_health * (0.5 / (potion_size + 1)));

            break;
        case Potion::luck:
            m_luck += (potion_size + 1);
            break;
        case Potion::max_types:
            assert(false && "Can't drink max_types potion!");
            break;
        }
        std::cout << "You drank a " << potion.get_size_name() << " potion of "
                  << potion.get_name() << "\n";
    }
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
            int escape_chance { 100 - 50 / player.get_luck() };
            int escape_roll { Random::get(1, 100) };
            if (escape_roll < escape_chance) {
                std::cout << "You successfully fled.\n";
                return; // end the fight

            } else {
                std::cout << "You failed to flee.\n";
                attack_player(player, monster);
            }
        } else if (action == 'f') {
            int monster_health_before_attack { monster.get_health() };
            attack_monster(player, monster);
            if (!monster.is_dead()) {
                attack_player(player, monster);
            } else {
                // lifesteal: you have a chance of stealing health from a monster you kill on the last blow, equal to the health it had on the last turn before you killed it
                int lifesteal_chance { 100 - 80 / player.get_luck() };
                int lifesteal_roll { Random::get(1, 100) };
                if (lifesteal_roll < lifesteal_chance) {
                    player.increase_health(monster_health_before_attack);
                    std::cout << "You gained " << monster_health_before_attack
                              << " health.\n";
                }
                int potion_chance { 100 - 70 / player.get_luck() };
                int potion_roll { Random::get(1, 100) };
                if (potion_roll < potion_chance) {
                    std::cout << "You found a mythical potion! Do you want to "
                                 "drink it? [y/n]: ";
                    char potion_action {};
                    do {
                        std::cin >> potion_action;
                    } while (!handle_cin_error() &&
                             (tolower(potion_action) != 'y' ||
                              tolower(potion_action) != 'n'));
                    if (potion_action == 'y') {
                        player.drink_potion(Potion::get_random_potion());
                    }
                }
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
        std::cout << "You are at " << player.get_health()
                  << " health. You have " << player.get_luck() << " luck.\n";
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