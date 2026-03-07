#include <functional>
#include <iostream>
#include <vector>

struct Car {
    std::string_view make {};
    std::string_view model {};
};

auto make_walrus(const std::string &name) {
    return [&]() { std::cout << "I'm a walrus named " << name << "\n"; };
}

void my_invoke(const std::function<void()> &fn) { fn(); }

int main() {
    std::array<std::string_view, 4> arr { "apple", "banana", "walnut",
                                          "lemon" };

    // lambdas can't use variables outside of themselves unless those variables are global/static or constexpr implicitly/explicitly
    std::cout << "search for: ";

    std::string search {};
    std::cin >> search;

    // so this won't work:
    // auto found { std::find_if(arr.begin(), arr.end(), [](std::string_view str) {
    //     return str.find(search) != std::string_view::npos;
    // }) };

    // we need to use the capture clause:
    auto found { std::find_if(
        arr.begin(), arr.end(), [search](std::string_view str) {
            return str.find(search) != std::string_view::npos;
        }) };

    if (found == arr.end()) {
        std::cout << "Not found\n";
    } else {
        std::cout << "Found " << *found << '\n';
    }

    // lambdas normally capture variables by making a copy
    // under the hood lambdas are objects that can be called using operator() (they are called "functors"), and the compiler creates a custom object definition for each lambda, where captured variables are data members; at runtime, when the lambda is encountered, the lambda object is instantiated and the data members are initialized at that point

    // captures are const by default:
    int ammo { 10 };
    // this won't work because ammo cannot be modified:
    // auto shoot { [ammo]() {
    //     ammo--;
    //     std::cout << "Pew! " << ammo << " shot(s) left.\n";
    // } };
    // unless we mark it mutable:
    auto shoot { [ammo]() mutable {
        ammo--;
        std::cout << "Pew! " << ammo << " shot(s) left.\n"; // prints 9, then 8
    } };

    shoot();
    shoot();
    std::cout << ammo << " shot(s) left\n"; // this prints 10
    // but this doesn't do what we expect: across calls to the lambda, the value of ammo is preserved, but changes to ammo inside the lambda don't affect the outer variable

    // we use capture by reference to change the outer variable; variables captured by reference are non-const unless the variable they're capturing is const

    auto shoot2 { [&ammo]() { // mutable not needed anymore
        ammo--;
        std::cout << "Pew! " << ammo << " shot(s) left.\n";
    } };

    shoot2();
    std::cout << "Pew! " << ammo << " shot(s) left.\n";

    // using references to count the number of comparisons used when sorting:
    std::array<Car, 3> cars { { { "Volkswagen", "Golf" },
                                { "Toyota", "Corolla" },
                                { "Honda", "Civic" } } };

    int comparisons { 0 };
    std::sort(cars.begin(), cars.end(),
              [&comparisons](const auto &a, const auto &b) {
                  comparisons++;
                  return a.make < b.make;
              });

    std::cout << "Comparisons: " << comparisons << "\n";
    for (const auto &car : cars) {
        std::cout << car.make << " " << car.model << "\n";
    }

    struct CEnemy {};
    // multiple captures are separated by commas
    int health {};
    int armor {};
    std::vector<CEnemy> enemies {};

    [health, armor, &enemies]() {}; // NOLINT

    // we can use default captures to autogenerate the list of variables to capture
    // use "=" to capture all used variables by value
    // use "&" to capture all used variables by reference

    std::array areas { 100, 25, 121, 40, 56 };
    int width {};
    int height {};
    std::cout << "Enter width and height: ";
    std::cin >> width >> height;

    auto found2 { std::find_if(areas.begin(), areas.end(), [=](int known_area) {
        return width * height == known_area;
    }) };

    if (found2 == areas.end()) {
        std::cout << "I don't know this area\n";
    } else {
        std::cout << "Area found\n";
    }

    // default captures and normal captures can be mixed, but each variable can be captured only once:
    // capture health and armor by value and enemies by reference
    [health, armor, &enemies]() {}; // NOLINT
    // capture enemies by reference and everything else by value
    [=, &enemies]() {}; // NOLINT
    // capture armor by value and everything else by reference
    [&, armor]() {}; // NOLINT
    // illegal, we already said to capture everything by reference
    // [&, &armor]() {};
    // illegal, we already said to capture everything by value
    // [=, armor](){};
    // illegal, armor appears twice
    // [armor, &health, &armor]() {};
    // illegal, the default capture needs to come first
    // [armor, &]() {};

    // we can define a new variable in the capture clause visible only in the lambda's scope:

    auto found3 { std::find_if(areas.begin(), areas.end(),
                               [user_area { width * height }](int known_area) {
                                   return user_area == known_area;
                               }) };
    // user_area is only calculated once when the lambda is defined and is stored in the lambda object, making it the same for every call; if the lambda is mutable and modifies a variable that was defined in the capture, the original value is overriden

    if (found3 == areas.end()) {
        std::cout << "I don't know this area\n";
    } else {
        std::cout << "Area found\n";
    }

    // captured variables will become dangling if a variable captured by reference dies before the lambda runs:
    auto say_name { make_walrus(
        "Roofus") }; // temporary std::string created here
    say_name();
    // even if the parameter had been passed by reference, the parameter would die at the end of the function call and the lambda still would've been left with a dangling reference
    // in this case capture by value is necessary

    // lambdas are objects and can be copied
    int i { 0 };
    auto count { [i]() mutable { std::cout << ++i << "\n"; } };
    count(); // 1
    auto other_count { count };
    count();       // 2
    other_count(); // 2
    // other_count makes a copy of count at its current state where its copy of i is 1

    int j { 0 };
    auto count2 { [j]() mutable { std::cout << ++j << "\n"; } };
    my_invoke(count2); // 1
    my_invoke(count2); // 1
    my_invoke(count2); // 1
    // since count2 has a lambda type, it doesn't match the type of the reference -- std::function<void()> -- so it converts the lambda into a temporary std::function so the parameter can bind to it; meaning each fn() inside my_invoke() is called on a copy of the lambda, not the actual lambda
    // if we need to pass a mutable lambda to a function, we can either:
    // - remove the capture by tracking state using a static local variable
    // - prevent copies by putting the lambda in a std::function immediately:
    int k { 0 };
    std::function count3 { [k]() mutable { std::cout << ++k << "\n"; } };
    my_invoke(count3); // 1
    my_invoke(count3); // 2
    my_invoke(count3); // 3
    // the same thing would be possible by using a std::reference_wrapper:
    my_invoke(std::ref(count2)); // 1
    my_invoke(std::ref(count2)); // 2
    my_invoke(std::ref(count2)); // 3
    // and this works even if the function takes the lambda by value rather than by reference

    // avoid mutable lambdas to avoid all these problems and further problems when parallelism is introduced

    return 0;
}