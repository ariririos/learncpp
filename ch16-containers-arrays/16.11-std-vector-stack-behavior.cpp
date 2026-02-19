#include <ios>
#include <iostream>
#include <limits>
#include <vector>

void print_stack(const std::vector<int> &stack) {
    if (stack.empty()) {
        std::cout << "Empty";
    }
    for (auto element : stack) {
        std::cout << element << " ";
    }
    std::cout << "\tCapacity: " << stack.capacity()
              << "  Length: " << stack.size() << "\n";
}

class Foo {
private:
    std::string m_a {};
    int m_b {};

public:
    Foo(std::string_view a, int b) : m_a { a }, m_b { b } {}
    explicit Foo(int b) : m_a {}, m_b { b } {}
};

int main() {
    // remember that a stack is a last-in first-out structure
    // it has two required operations, push and pop
    // push adds a new element to the top, pop removes the top element and
    // optionally returns it
    // other optional operations are:
    // - top/peek, look at the top element without removing
    // - empty, determine if the stack has no elements
    // - size, count how many elements
    // the call stack operates by pushing entries when functions are called and
    // popping them when the function returns, so that the top of the stack
    // always represents the currently executing function in c++, stack
    // operations have been added to the standard library container classes that
    // support efficient insertion and removal at one end -- std::vector,
    // std::deque, and std::list

    // std::vector has the following stack behavior:
    // - push_back() adds a new element
    // - pop_back() removes the top element
    // - back() gets the top element non-destructively
    // - emplace_back() is an alternate version of push_back() that can be more
    // efficient

    std::vector<int> stack {};
    print_stack(stack);
    stack.push_back(1);
    print_stack(stack);
    stack.push_back(2);
    print_stack(stack);
    stack.push_back(3);
    print_stack(stack);
    std::cout << "Top: " << stack.back() << "\n";
    stack.pop_back();
    print_stack(stack);
    stack.pop_back();
    print_stack(stack);
    stack.pop_back();
    print_stack(stack);
    std::cout << "-------\n";

    // push_back() and emplace_back() will reallocate if needed, typically by
    // doubling the capacity (on gcc and clang)

    // if we direct-initialized the stack with a length, it wouldn't work right,
    // because those elements at the beginning would be initialized, and then
    // we'd be pushing more elements on top -- it sets both capacity and length
    // to set just the capacity, we need .reserve()

    std::vector<int> stack2 {};
    print_stack(stack2);
    stack2.reserve(3);
    stack2.push_back(1);
    print_stack(stack2);
    stack2.push_back(2);
    print_stack(stack2);
    stack2.push_back(3);
    print_stack(stack2);
    std::cout << "Top: " << stack2.back() << "\n";
    stack2.pop_back();
    print_stack(stack2);
    stack2.pop_back();
    print_stack(stack2);
    stack2.pop_back();
    print_stack(stack2);

    // use .resize() when accessing by indexing, since this changes both length
    // and capacity use .reserve() when accessing by stack operations, this
    // changes just capacity

    // .emplace_back() is more efficient if we are creating a temporary object
    // just to push it onto the stack:
    std::vector<Foo> stack3 {};

    // similar performance when an object already exists:
    Foo f { "a", 2 };
    stack3.push_back(f); // prefer this
    stack3.emplace_back(f);

    // but if we need to create a temporary object, .emplace_back() is better:
    stack3.push_back(
        { "a", 2 }); // creates a temp object and copies into the vector
    stack3.emplace_back("a",
                        2); // forwards its arguments so the object can be
                            // created directly in the vector without a copy,
                            // called "perfect forwarding"

    // .push_back() won't use explicit constructors, .emplace_back() will
    // stack3.push_back({ 2 }); // no matching constructor error
    stack3.emplace_back(2);
    // pre-c++20, .emplace_back() doesn't work with aggregate initialization
    std::cout << "-------\n";
    std::vector<int> score_list {};
    while (true) {
        std::cout << "Enter a score (or -1 to finish): ";
        int x {};
        std::cin >> x;
        if (!std::cin) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }
        if (x == -1) {
            break;
        }
        score_list.push_back(x);
    }
    std::cout << "Your list of scores: \n";
    for (const auto& score : score_list) {
        std::cout << score << " ";
    }
    std::cout << "\n";

    return 0;
}