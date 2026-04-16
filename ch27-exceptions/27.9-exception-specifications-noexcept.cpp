#include <iostream>

void do_something() noexcept {}

class Doomed {
public:
    ~Doomed() { std::cout << "Doomed destructed\n"; }
};

void thrower() {
    std::cout << "Throwing exception\n";
    throw 1;
}

void pt() {
    std::cout << "pt (potentially throwing) called\n";
    Doomed
        doomed {}; // this will be destroyed during stack unwinding (if it occurs)
    thrower();
    std::cout << "This never prints\n";
}

void nt() noexcept {
    std::cout << "nt (noexcept) called\n";
    Doomed
        doomed {}; // this will be destroyed during stack unwinding (if it occurs)
    thrower();
    std::cout << "This never prints\n";
}

void tester(int c) noexcept {
    std::cout << "tester (noexcept) case " << c << " called\n";
    try {
        (c == 1) ? pt() : nt();
    } catch (...) {
        std::cout << "tester caught exception\n";
    }
}

void foo() { throw -1; }
void boo() {}
void goo() noexcept {}
struct S {};

int main() {
    // a regular function declaration doesn't give you any information about whether the function may throw; but sometimes we need to know if a function is safe to use somewhere where exceptions aren't, like in a destructor

    // all functions in c++ are either non-throwing or potentially throwing; we can define a function as non-throwing by using `noexcept` (see do_something() above)

    // noexcept doesn't prevent a function from throwing exceptions or calling other functions that throw exceptions, and the compiler doesn't check that noexcept functions don't throw

    // if an unhandled exception would exit a noexcept function, std::terminate will be called even if there's an exception handler that would otherwise handle the exception somewhere up the stack
    // if std::terminate is called from somewhere inside a noexcept function, stack unwinding may or may not occur

    // functions differing only in their exception specification can't be overloaded

    // an example:
    std::cout << std::unitbuf; // flush buffer after each insertion
    std::cout << std::boolalpha;
    tester(
        1); // this throws an exception, which unwinds the stack and destructs doomed, and catches that exception; tester is noexcept but it can still catch and handle exceptions internally
    std::cout << "Test successful\n\n";
    tester(
        2); // this throws an exception, which may or may not unwind the stack and destroy doomed; std::terminate gets called here as soon as the noexcept violation occurs so the exception isn't caught and the next line isn't printed
    std::cout << "Test successful\n";

    // noexcept can be used as `noexcept(true)`, same as noexcept, and `noexcept(false)`, potentially throwing; these are useful in templates to make a function dynamically throwing or non-throwing

    // functions that are implicitly non-throwing:
    // - destructors

    // functions that are non-throwing by default for implicitly-declared or defaulted functions:
    // - constructors: default, copy, move
    // - assignments: copy, move
    // - comparison operators (as of c++20)
    // however, if these functions implicitly or explicitly call another function that's potentially throwing then the original function will be listed as potentially throwing, e.g. if a class has a data member with a potentially throwing constructor, then the class's constructors will be treated as potentially throwing as well

    // functions that are potentially throwing (if not implicitly-declared or defaulted):
    // - normal functions
    // - user-defined constructors
    // - user-defined operators

    // noexcept can also be used an operator that returns whether the compiler thinks an expression will throw an exception or not; it is checked at compile time and not actually evaluated
    [[maybe_unused]] constexpr bool b1 { noexcept(
        5 + 3) }; // true, ints can't throw
    [[maybe_unused]] constexpr bool b2 { noexcept(
        foo()) }; // false; foo() throws an exception
    [[maybe_unused]] constexpr bool b3 { noexcept(
        boo()) }; // false; boo() is implicitly noexcept(false)
    [[maybe_unused]] constexpr bool b4 { noexcept(
        goo()) }; // true; goo() is explicitly noexcept(true)
    [[maybe_unused]] constexpr bool b5 { noexcept(
        S {}) }; // true; a struct's default constructor is noexcept by default

    // exception safety guarantees are contractual guidelines about how functions or classes will behave in the event an exception occurs; there are four levels:
    // - no guarantee: a class may be left in an unusable state
    // - basic guarantee: no memory will be leaked and the object is still usable, but the program may be left in a modified state
    // - strong guarantee: no memory will be leaked and the program state will not be changed; the function must either completely succeed or have no side effects if it fails -- if the failure happens before the state is modified, then this is easy; otherwise this can also be achieved by rolling back any changes if failure occurs
    // - no throw / no fail guarantee: the function will always succeed (no-fail) or fail without throwing an exception that is exposed to the caller (no-throw); this is what noexcept corresponds to

    // a no-throw guarantee can be implemented by returning an error code or ignoring the problem; no-throw guarantees are required during stack unwinding when an exception is already being handled; examples of code that should be no-throw:
    // - destructors and memory deallocation/cleanup functions
    // - functions that other no-throw functions need to call

    // a no-fail guarantee is a slightly stronger form of no-throw where a function will always succeed; examples of code that should be no-fail:
    // - move constructors and move assignment
    // - swap functions
    // - clear/erase/reset functions on containers
    // - operations on std::unique_ptr
    // - functions that other no-fail functions need to call

    // nothrow isn't necessarily useful everywhere, but there's a few good reasons to use it:
    // - noexcept functions can safely be called from functions that aren't exception-safe, such as destructors
    // - the compiler can perform optimizations since it doesn't need to keep the runtime stack in an unwindable state, which can make the code faster
    // - we can use noexcept to produce more efficient code; the stdlib containers are noexcept aware and will use the noexcept operator to determine whether to use move semantics (faster) or copy semantics (slower) in some places

    // the stdlib only uses noexcept on functions that must not throw at all; functions that are potentially throwing but whose implementation doesn't actually throw typically aren't marked noexcept

    // **we should always make move constructors, move assignment operators, and swap functions noexcept**
    // consider marking noexcept: functions that we wish to communicate are no-throw/no-fail; copy constructors and copy assignment operators that are no-throw (for optimization); destructors (which are implicitly noexcept as long as all members have noexcept destructors)
    // if we're uncertain whether a function should be no-throw/no-fail, err on the side of caution and don't mark it noexcept; removing noexcept from a function breaks an interface promise but adding it only makes a function safer

    // dynamic exception specifications allowed functions to specify which exceptions they could throw until c++17:
    // int do_something() throw(); // does not throw
    // int do_something() throw(std::out_of_range, int*); // may throw either std::out_of_range or an int*
    // int do_something() throw(...); // may throw anything

    return 0;
}