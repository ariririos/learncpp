#include <iostream>
#include <string>
#include <string_view>

class Monster {
public:
    enum Type {
        dragon,
        goblin,
        ogre,
        orc,
        skeleton,
        troll,
        vampire,
        zombie,
        max_monster_types
    };

private:
    Type m_type {};
    std::string m_name {};
    std::string m_roar {};
    int m_hp {};

public:
    Monster(Type type, std::string_view name, std::string_view roar, int hp)
        : m_type { type }, m_name { name }, m_roar { roar }, m_hp { hp } {}
    constexpr std::string_view get_type_string() const {
        switch (m_type) {
        case dragon:
            return "dragon";
        case goblin:
            return "goblin";
        case ogre:
            return "ogre";
        case orc:
            return "orc";
        case skeleton:
            return "skeleton";
        case troll:
            return "troll";
        case vampire:
            return "vampire";
        case zombie:
            return "zombie";
        case max_monster_types:
            return "";
        }
    }
    void print() const {
        std::cout << m_name << " the " << get_type_string();
        if (m_hp > 0) {
            std::cout << " has " << m_hp << " hit points and says " << m_roar;
        } else {
            std::cout << " is dead";
        }
        std::cout << "\n";
    }
};

namespace MonsterGenerator {
    Monster generate() { return { Monster::skeleton, "Bones", "*rattle*", 4 }; }
} // namespace MonsterGenerator

int main() {
    Monster skeleton { Monster::skeleton, "Bones", "*rattle*", 4 };
    skeleton.print();

    Monster vampire { Monster::vampire, "Nibblez", "*hiss*", 0 };
    vampire.print();

    Monster m { MonsterGenerator::generate() };
    m.print();
    
    return 0;
}