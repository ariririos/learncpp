#include "../../Random.h"
#include <cassert>
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
    std::string m_name { "???" };
    std::string m_roar { "???" };
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
        default:
            return "???";
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
    constexpr std::string_view get_name(int i) {
        assert(i >= 0 && i <= 5 && "index out of range");
        switch (i) {
        case 0:
            return "Bones";
        case 1:
            return "Blarg";
        case 2:
            return "Nosfer";
        case 3:
            return "Smeek";
        case 4:
            return "Lirot";
        case 5:
            return "Tyvid";
        default:
            return "???";
        }
    }
    constexpr std::string_view get_roar(int i) {
        assert(i >= 0 && i <= 5 && "index out of range");
        switch (i) {
        case 0:
            return "*rattle*";
        case 1:
            return "*roar*";
        case 2:
            return "*screech*";
        case 3:
            return "*slither*";
        case 4:
            return "*bang*";
        case 5:
            return "*whisper*";
        default:
            return "???";
        }
    }
    Monster generate() {
        return { static_cast<Monster::Type>(
                     Random::get(0, Monster::max_monster_types - 1)),
                 get_name(Random::get(0, 5)), get_roar(Random::get(0, 5)),
                 Random::get(1, 100) };
    }
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