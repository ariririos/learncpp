#include <iostream>

int g_counter { 0 };
void eat_stack() {
    std::cout << ++g_counter << " ";
    // this conditional prevents compiler warnings about infinite recursion
    if (g_counter > 0) {
        eat_stack();
    }
    // this prevents tail-call optimization
    std::cout << "hi";
}

int main() {
    // the memory that a program uses is usually split into a few segments:
    // the code segment (or text segment): where the compiled program sits in memory, usually read-only
    // the bss segment (or uninitialized data segment): where zero-initialized global and static variables are stored
    // the data segment (or initialized data segment): where initialized global and static variables are stored
    // the heap: where dynamically allocated variables are allocated from
    // the call stack: where function parameters, local variables, and other function information are stored

    // the heap: the new operator allocates here
    // successive calls to new don't necessarily allocate memory sequentially!
    int *ptr1 { new int };
    int *ptr2 { new int };
    std::cout << ptr1 << " " << ptr2 << "\n";

    // the stack: fixed size, automatic storage duration variables and function calls go here
    // when the program starts, the OS puts main() on the stack and adds "stack frames" which contain all the data associated with a function call
    // the stack pointer is a marker that keeps track of where the top of the call stack is; it's stored in a register
    // when a function returns, the program can just move the stack pointer down and consider the stack frame above it gone, and overwrite it if a new stack frame gets pushed to the same memory
    // the sequence of steps when a function is called:
    // - a function call is encountered
    // - a stack frame is constructed: the address of the instruction one past the function call (the return address) so the CPU knows where to return after the function exits; all function arguments; memory for any local variables; and saved copies of any registers modified by the function that need to be restored when the function returns
    // - the CPU jumps to the function's start point
    // - the instructions inside the function are executed
    // when the function terminates:
    // - registers are restored from the call stack
    // - the stack frame is popped off the stack, freeing memory for all local variables and arguments
    // - the return value is handled (sometimes as part of the stack frame, sometimes in a register)
    // - the CPU resumes execution at the saved return address
    // depending on the architecture, the stack may grow away from 0 or towards 0
    // when the stack doesn't have enough space for either automatic variables or function calls, stack overflow occurs
    // for example:
    eat_stack();

    return 0;
}