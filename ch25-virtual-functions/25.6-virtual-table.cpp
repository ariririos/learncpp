#include <iostream>
#include <string_view>

namespace Resolution {
    class Base {
    public:
        std::string_view get_name() const { return "Base"; }
        virtual std::string_view get_name_virtual() const { return "Base"; }
        virtual ~Base() {}
    };

    class Derived : public Base {
    public:
        std::string_view get_name() const { return "Derived"; }
        virtual std::string_view get_name_virtual() const override {
            return "Derived";
        }
    };
}; // namespace Resolution

namespace VTable {
    struct VirtualTable {};
    class Base {
    public:
        VirtualTable *__vptr;
        virtual void function1() {};
        virtual void function2() {};
        virtual ~Base() {}
    };

    class D1 : public Base {
    public:
        void function1() override {};
    };

    class D2 : public Base {
    public:
        void function2() override {}
    };
} // namespace VTable

int main() {
    Resolution::Derived derived {};
    Resolution::Base &base { derived };

    std::cout
        << "base has static type " << base.get_name()
        << "\n"; // non-virtual function gets resolved to Base::get_name() at compile time
    std::cout
        << "base has dynamic type " << base.get_name_virtual()
        << "\n"; // virtual function gets resolved to Derived::get_name_virtual() at runtime

    // c++ doesn't specify how virtual functions should be implemented, but typically a virtual table (vtable) is used -- a lookup table of functions used to resolve calls dynamically

    // every class that uses virtual functions (or is derived from one) has a corresponding virtual table, a static array set up by the compiler at compile time, with an entry for each virtual function which is just a function pointer to the most-derived function accessible by that class
    // each class also has a hidden pointer, call it *__vptr, which is automatically set to the virtual table for its class whenever objects of that class are created; unlike `this`, *__vptr is a real pointer member and is inherited by derived classes

    // when we create objects of class VTable::{Base, D1, D2}, *__vptr points to their respective vtables, which each have two members for each of the two functions they can access
    // Base objects can only access Base functions, so its pointers are to its own functions
    // D1's objects can access members of both D1 and Base, but since D1 has overriden function1, its function1 pointer is to D1::function1; its function2 pointer is still to Base::function2
    // D2's virtual table is similar to D1's, with the function1 pointer to Base::function1 and function2 pointer to D2::function2
    VTable::D1 d1 {};
    VTable::Base *d_ptr { &d1 };
    // d_ptr is a Base pointer and only points to the Base portion of d1; *__vptr is in the Base portion of the class, so d_ptr has access to it; d_ptr->__vptr points to the D1 virtual table (because d1.__vptr does) so even though d_ptr is of type Base*, it still has access to D1's virtual table

    // when you call d_ptr->function1(), a few things happen: the program recognizes that function1() is virtual, it uses d_ptr->__vptr to access D1's virtual table, it finds that the function1 pointer is set to D1::function1(), and then it calls that function
    d_ptr->function1();

    // but what if d_ptr actually pointed to a Base object instead of a D1 object? it wouldn't call D1::function1() in that case, it would call Base::function1(); b.__vptr points to Base's virtual table, not D1's, so b_ptr->__vptr points to Base's virtual table too; the Base virtual table's function1 entry points to Base::function1(), so this call resolves to Base::function1()
    VTable::Base b {};
    VTable::Base *b_ptr { &b };
    b_ptr->function1();

    // by having derived classes inherit __vptr, the compiler and runtime can ensure that the right function is called when doing virtual function resolution even when we only have a pointer or reference to a base clas

    // this means virtual functions require three operations: following *__vptr to get to the right virtual table, indexing the virtual table to find the correct function, then actually doing the call; a regular indirect function call only requires two operations (no indexing, we already have the function pointer); a direct function call only requires one (doing the call)

    // any class that uses virtual functions has a *__vptr and thus will be bigger by one pointer

    return 0;
}