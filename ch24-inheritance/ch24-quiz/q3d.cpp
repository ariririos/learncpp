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

int main() {
    Monster m { Monster::Type::orc };
    std::cout << "A " << m.get_name() << " (" << m.get_symbol()
              << ") was created.\n";

    return 0;

    return 0;
}