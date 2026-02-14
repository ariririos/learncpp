#include <iostream>

class IntPair {
private:
    int m_x {};
    int m_y {};

public:
    IntPair(int x, int y) : m_x { x }, m_y { y } {}
    int x() const { return m_x; }
    int y() const { return m_y; }
};

void print(IntPair p) { std::cout << "(" << p.x() << ", " << p.y() << ")\n"; }

class Foo {
private:
    int m_x {};
    int m_y {};

public:
    Foo(int x = 0, int y = 0) : m_x { x }, m_y { y } {}
};

void *bar7() { return nullptr; }

IntPair ret1() {
    IntPair p { 3, 4 };
    return p;
}

IntPair ret2() { return IntPair { 5, 6 }; }

IntPair ret3() { return { 5, 6 }; }

int main() {
    // print() is expecting an rvalue

    // case 1: pass an lvalue and get lvalue-to-rvalue conversion
    IntPair p { 3, 4 };
    print(p);

    // case 2: explicitly construct an IntPair rvalue
    print(IntPair { 5, 6 });

    // case 3: implicitly construct an IntPair rvalue
    print({ 7, 8 });

    /// ********
    // why to prefer direct-initialization over list-initialization:

    // this creates a default-initialized Foo just like `Foo {}` would:
    Foo();

    // this creates a variable bar of type Foo:
    Foo bar {};

    // but this creates a function definition bar() with return type Foo and no
    // parameters:
    Foo bar2(); // -Wvexing-parse // NOLINT

    // this is a "function-style cast" of literal 1, equivalent to `Foo { 1 }`:
    Foo(1);

    // but this is a variable definition:
    Foo(bar3); // and the parentheses are just redundant

    // it gets worse with function pointers:

    // this is a function bar() with return type Foo*
    Foo *bar4(); // -Wvexing-parse // NOLINT

    // this defines a variable bar5 which is a pointer to a function with no
    // parameters that returns Foo:
    Foo (*bar5)();

    // this is the same as bar4 above, the parens do nothing:
    Foo(*bar6());

    // and this calls bar7, C-style casts the return value to a Foo*, then
    // discards it
    (Foo *)bar7(); // NOLINT

    // ********
    // back to IntPair:
    print(ret1());
    print(ret2());
    print(ret3());

    char c { 'a' };

    // we can use temporary object syntax to do the same thing as static_cast
    // when there aren't any narrowing conversions involved:
    std::cout << static_cast<int>(c) << "\n";
    std::cout << int { c } << "\n";

    return 0;
}