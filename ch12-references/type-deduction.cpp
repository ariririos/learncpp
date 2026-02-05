#include <string>
#include <string_view>
#include <iostream>
#define print_expr(x) { std::cout << #x << " = " << x << "\n"; }

std::string& return_same_ref(std::string& ref) {
    return ref;
}

const std::string& return_same_const_ref(const std::string& ref) {
    return ref;
}

constexpr std::string_view hello { "hello" };

constexpr const std::string_view& get_const_hello() {
    return hello;
}

std::string* return_same_ptr(std::string* ptr) {
    return ptr;
}

int main() {
    // non-compound type deduction
    int a { 5 };
    auto b { a }; // NOLINT
    const double c { 7.8 };
    auto d { c };
    constexpr double e { 7.8 };
    auto f { e };
    const auto g { e };
    constexpr auto h { e };

    // reference deduction
    std::string i { "hello world" };
    auto str { return_same_ref(i) }; // std::string, reference dropped
    print_expr(str);
    auto& ref { return_same_ref(i) }; // std::string&, reference reapplied
    print_expr(ref);

    // top-level and low-level const
    // const int x; // top-level
    // int* const y; // top-level
    // all references are top-level const

    // const int& ref3; // low-level
    // const int* ptr; // low-level

    // type deduction drops top-level consts only but the process of deduction can transmute a low-level const to top-level

    auto str3 { return_same_const_ref(i) }; // const std::string& -> reference dropped -> const std::string -> low-level const becomes top-level, can be dropped -> std::string
    print_expr(str3);

    auto& str4 { return_same_const_ref(i) }; // reference dropped and re-applied, low-level const not dropped (const never becomes top-level because reference is reapplied before const drops)
    const auto& str5 { return_same_const_ref(i) }; // same as above

    auto ref3 { get_const_hello() }; // std::string_view, ref dropped, top-level const dropped
    constexpr auto ref4 { get_const_hello() }; // ref and top-level const dropped, constexpr applied, implicitly const

    auto& ref5 { get_const_hello() }; // const std::string_view&, ref re-applied, low-level const not dropped
    constexpr const auto& ref6 {get_const_hello()}; // constexpr const std::string_view&, ref re-applied, low-level const not dropped, constexpr applied

    auto ptr1 { return_same_ptr(&i) }; // std::string*, pointer not dropped
    print_expr(ptr1);

    auto* ptr2 { return_same_ptr(&i) }; // same thing but more explicit
    print_expr(ptr2);

    auto ptr3 { *return_same_ptr(&i) }; // std::string because we dereferenced
    print_expr(ptr3);

    // auto* ptr4 { *return_same_ptr(&i) }; // won't compile, auto* will only work with a pointer initializer
    // print_expr(ptr4);

    // these two mean the same thing:
    const auto ptr4 { return_same_ptr(&i) }; // std::string* const
    print_expr(ptr4);
    auto const ptr5 { return_same_ptr(&i) }; // std::string* const
    print_expr(ptr5);

    // for auto* order matches 
    const auto* ptr6 { return_same_ptr(&i) }; // const std::string*
    print_expr(ptr6);
    auto* const ptr7 { return_same_ptr(&i) }; // std::string* const
    print_expr(ptr7);

    const std::string* const ptr { &i };

    auto ptr_a { ptr }; // const std::string*, top-level const dropped
    print_expr(ptr_a);
    auto* ptr_b { ptr }; // const std::string*, top-level const dropped
    print_expr(ptr_b);
    
    auto const ptr_c { ptr }; // const std::string* const, top-level const reapplied, low-level const not dropped
    print_expr(ptr_c);
    const auto ptr_d { ptr }; // const std::string* const, top-level const reapplied, low-level const not dropped
    print_expr(ptr_d);

    auto* const ptr_e { ptr }; // const std::string* const, top-level const reapplied, low-level const not dropped
    print_expr(ptr_e);
    const auto* ptr_f { ptr }; // const std::string*, top-level const dropped, low-level const not dropped (redundant)
    print_expr(ptr_f);

    const auto const ptr_g { ptr }; // const std::string* const, warns with "duplicate const" since const before/after `auto` both mean top-level const // NOLINT
    print_expr(ptr_g);
    const auto* const ptr_h { ptr }; // const std::string* const, top-level const reapplied, low-level const redundant
    print_expr(ptr_h);

    return 0;
}