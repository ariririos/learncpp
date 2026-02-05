#include <iostream>

double add(double x, double y) { return x + y; }
// int add(int a, int b); // fails to link
inline double pi() { return 3.14159265358979323846; }
static int x; // internal linkage (not visible to other files), zero-initialized
const int y { 0 }; // const gives internal linkage 
constexpr int z { 0 }; // constexpr gives internal linkage, 
const static int t { 0 }; // const gives internal linkage, this shadows `t` from add.cpp
extern int u; // defines u as coming from outside this file, in particular, add.cpp
extern const int v; // this does the same for v
int w; // zero initialized, global
inline int i { 0 }; // global linkage

double get_gravity();

static void internal_function() {
    printf("Not visible outside of this file");
}

int main() {
    std::cout << "x = " << x << "\n"; // 0
    std::cout << "y = " << y << "\n"; // 0
    std::cout << "z = " << z << "\n"; // 0
    std::cout << "t = " << t << "\n"; // shadowed from add.cpp, should give 0 not 2
    std::cout << "u = " << u << "\n"; // uninit
    std::cout << "v = " << v << "\n"; // uninit
    std::cout << "w = " << w << "\n"; // uninit
    


    std::cout << add(3, 4) << "\n";
    // std::cout << add_int(3, 4); // won't compile because add_int is static in add.cpp

    std::cout << "gravity = " << get_gravity() << "\n";
    internal_function();
    return 0;
}