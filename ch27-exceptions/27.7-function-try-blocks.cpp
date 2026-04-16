#include <iostream>

namespace NoFunctionTry {
    class A {
    private:
        int m_x;

    public:
        A(int x) : m_x { x } {
            if (x <= 0) {
                throw 1;
            }
        }
    };

    class B : public A {
    public:
        B(int x)
            : A { x } // A initialized in the member initializer list of B
        {
            // how would we handle it here if creation of A fails?
        }
    };
} // namespace NoFunctionTry

namespace FunctionTry {
    class A {
    private:
        int m_x;

    public:
        A(int x) : m_x { x } {
            if (x <= 0) {
                throw 1;
            }
        }
    };

    class B : public A {
    public:
        B(int x)
        try
            : A { x }
        // added a try here, which catches all exceptions from that point until the end of the function
        {
        } catch (...) { // this is at the function level
            // exceptions from either member initializer list or from constructor body are caught here
            std::cerr << "Exception caught\n";
            throw; // and rethrow the exception
        }
    };
} // namespace FunctionTry

int main() {
    try {
        NoFunctionTry::B b { 0 };
    } catch (int) {
        std::cout << "Oops\n";
    }

    try {
        FunctionTry::B b { 0 };
    } catch (int) {
        std::cout << "Oops\n";
    }

    // in a regular catch block, we can throw a new exception, rethrow the current exception, or resolve the exception (either using a return statement or letting control reach the end of the catch block)
    // in a function-level catch block for a constructor, we can only either throw a new exception or rethrow the existing exception; we can't return, and reaching the end of the catch block will implicitly rethrow
    // for a destructor, we can throw, rethrow, or resolve, and reaching the end of the catch block will implicitly rethrow
    // for other types of functions, we can throw, rethrow, or resolve; reaching the end of the catch block will implicitly resolve in a void function and produce undefined behavior for value-returning functions

    // since the behavior of a function can be implicit rethrow, resolving the exception, or undefined behavior based on its type if we let control reach the end of the catch block, **we should never let control reach the end of a catch block for a function-level try**, and always explicitly throw, rethrow, or return

    // function try is basically only used with constructors

    // function try shouldn't be used to clean up resources; since a class's destructor doesn't run if its construction fails, we might try to use function try to clean up partially allocated resources
    // but referring to members of the failed object is undefined behavior because the object is considered "dead" before the catch block runs
    // we should instead follow the rules for cleaning up classes that throw exceptions (27.5 - i.e. members' destructors will run so use those)
    // function try is useful primarily for logging failures before rethrowing or changing the type of exception thrown
}