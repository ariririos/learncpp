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
};

int main() {
    Monster skeleton { Monster::skeleton, "Bones", "*rattle*", 4 };

    return 0;
}