#include <iostream>
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

int main() {
    Creature o { "orc", 'o', 4, 2, 10 };
    o.add_gold(5);
    o.reduce_health(1);
    std::cout << "The " << o.get_name() << " has " << o.get_health()
              << " health and is carrying " << o.get_gold() << " gold.\n";

    return 0;
}