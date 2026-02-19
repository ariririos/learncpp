#include <cassert>
#include <cxxabi.h>
#include <iostream>
#include <type_traits>
#include <vector>

namespace Students {
    // we could specify the underlying type to avoid sign conversion when using a non-constexpr enumeration (the individual options, the enumerator overall is constexpr):
    // enum Names : unsigned int
    enum Names { kenny, kyle, stan, butters, cartman, max_students };
}

enum class StudentNames { kenny, kyle, stan, butters, cartman, max_students };

constexpr auto operator+(StudentNames a) noexcept {
    return static_cast<std::underlying_type_t<StudentNames>>(a);
}

int main() {
    std::vector test_scores { 78, 94, 66, 77, 14 };
    // unscoped enums will implicitly convert to size_t; enums are implicitly
    // constexpr so conversion to an unsigned integral type isn't considered
    // narrowing
    test_scores[Students::stan] = 76;

    // but when used in a non-constexpr way, we might get sign conversion
    // warnings on platforms that default to using a signed type for unscoped
    // enums:
    Students::Names name { Students::stan };
    test_scores[name] = 76;

    // scoped enums always default to `int` as the underlying type

    // (aside: gcc lets you demangle the underlying type for enums)
    int status {};
    const std::type_info &ti { typeid(
        std::underlying_type_t<Students::Names>) };
    char *realname { abi::__cxa_demangle(ti.name(), NULL, NULL, &status) };
    std::cout << "Students::Names: " << ti.name() << " => " << realname
              << " (status " << status << ")\n";
    const std::type_info &ti2 { typeid(std::underlying_type_t<StudentNames>) };
    char *realname2 { abi::__cxa_demangle(ti2.name(), NULL, NULL, &status) };
    std::cout << "ScopedEnum: " << ti2.name() << " => " << realname2
              << " (status " << status << ")\n";
    std::free(realname);

    // max_students is useful to lock the length of the vector to the number of enumerations:
    std::vector<int> test_scores2 ( Students::max_students );
    test_scores2[Students::stan] = 76;
    std::cout << "The class has " << Students::max_students << " students\n";
    // and to assert that the initializer list matches the enum:
    assert(std::size(test_scores) == Students::max_students);
    // use static_assert for a constexpr std::array

    // enum classes won't implicitly convert to an integral type:
    // std::vector<int> test_scores3 ( StudentNames::max_students ); // no matching constructor error
    // test_scores3[StudentNames::stan] =  76; // no viable overloaded operator[] error
    // std::cout << "The class has " << StudentNames::max_students << " students\n"; // invalid operands error
    // the obvious way to fix these is with a static_cast<int>, but to avoid clutter, we can use a helper function (see operator+(StudentNames) above):
    std::vector<int> test_scores3 ( +StudentNames::max_students );
    test_scores3[+StudentNames::stan] = 76;
    std::cout << "The class has " << +StudentNames::max_students << " students\n";
    // but we should probably prefer just using an unscoped enum in a namespace if we're gonna be doing this a lot
    

    return 0;
}