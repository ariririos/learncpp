#include <iostream>
#include <string>
#include <string_view>



struct Monster {
    enum Type {
    ogre,
    dragon,
    orc,
    giant_spider,
    slime
};
    std::string name {};
    Type type {};
    int health {};
};

constexpr std::string_view get_type(const Monster& m) {
    using enum Monster::Type;

    switch (m.type) {
        case ogre: return "Ogre";
        case dragon: return "Dragon";
        case orc: return "Orc";
        case giant_spider: return "Giant Spider";
        case slime: return "Slime";
        default: return "???";
    }
}

void print_monster(const Monster& m) {
    std::cout << "This " << get_type(m) << " is named " << m.name << " and has " << m.health << " health.\n";
}

int main() {
    Monster torg { "Torg", Monster::ogre, 145 };
    Monster blurp { "Blurp", Monster::slime, 23 };

    print_monster(torg);
    print_monster(blurp);

    return 0;
}