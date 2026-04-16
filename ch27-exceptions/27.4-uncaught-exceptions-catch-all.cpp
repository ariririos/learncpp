#include <iostream>

struct GameSession {};

void run_game(GameSession &) { throw 1; }

void save_game(GameSession &) {}

// can't be instantiated
class DummyException {
    DummyException() = delete;
};

int main() {
    // if we were to raise an exception in main() or a function main() calls does, and no one handles it, std::terminate() is called and the program is terminated
    // the call stack may or may not be unwound -- and any cleanup excepted upon destruction of local variables won't happen
    // this is because unhandled exceptions are generally always to be avoided, and not unwinding preserves debug information about how we got to a state that caused an unhandled exception to be thrown

    // we can use a catch-all handler to catch any otherwise unhandled exceptions within a try block and avoid the above
    try {
        throw 5;
    } catch (double x) {
        std::cout << "We caught an exception of type double: " << x << "\n";
    } catch (...) {
        std::cout << "We caught an exception of an undetermined type\n";
    }
    // catch-all blocks need to be placed last in the catch block chain

    // we can, and probably should, wrap statements in main() in a try-catch block to avoid unhandled exceptions
    GameSession session {};
    try {
        run_game(session);
    } catch (...) {
        std::cerr << "Abnormal termination\n";
    }
    save_game(session); // save the game even if the catch-all handler was hit

    // when we hit a catch-all block in main(), we should assume the program is in an indeterminate state, perform cleanup, then terminate

    // it can be useful in debug builds to disable the catch-all handler to get debugging info
    GameSession session2 {};
    try {
        run_game(session2);
    }
#ifndef NDEBUG
    catch (...) {
        std::cerr << "Abnormal termination\n";
    }
#else // we need some sort of catch block in debug mode so we can use a catch that will never be hit
    catch (DummyException) {
    }
#endif

    save_game(session2);

    return 0;
}