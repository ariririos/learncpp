namespace constants {
    inline constexpr double gravity { 9.8 };
}

double get_gravity() {
    return constants::gravity;
}