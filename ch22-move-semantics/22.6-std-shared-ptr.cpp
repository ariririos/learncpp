#include <iostream>
#include <memory>

class Resource {
public:
    Resource() { std::cout << "Resource acquired\n"; }
    ~Resource() { std::cout << "Resource destroyed\n"; }
};

int main() {
    // std::shared_ptr solves the case where we need multiple smart pointers co-owning a resource
    // it has an internal counter keeping track of how many std::shared_ptr are sharing the resource, and only deallocates the resource when the last std::shared_ptr managing the resource goes out of scope (or reassigned to point at something else)
    {
        Resource *res { new Resource };
        std::shared_ptr<Resource> ptr1 { res };
        {
            std::shared_ptr<Resource> ptr2 {
                ptr1
            }; // makes another std::shared_ptr pointing to the same thing
            std::cout << "Killing one shared pointer\n";
        } // ptr2 goes out of scope here
        std::cout << "Killing another shared pointer\n";
    } // ptr1 goes out of scope here and Resource is destroyed

    // we need to copy a std::shared_ptr from another std::shared_ptr otherwise they won't know about each other
    // if we don't, each std::shared_ptr deletes its underlying resource when it goes out of scope and we get a double free, for example:
    /*
    {
        Resource *res { new Resource };
        std::shared_ptr<Resource> ptr1 { res };
        {
            std::shared_ptr<Resource> ptr2 {
                res
            }; // makes another std::shared_ptr pointing to the same thing
            std::cout << "Killing one shared pointer\n";
        } // ptr2 goes out of scope here, the Resource is destroyed
        std::cout << "Killing another shared pointer\n";
    } // ptr1 goes out of scope, and we get a double free of the Resource
    */

    // std::make_shared does for std::shared_ptr what std::make_unique does for std::unique_ptr
    // it prevents us from accidentally making multiple independent std::shared_ptr pointing to the same resource
    // it's also more performant than not using it due to its internal memory management (see below)

    // internally std::shared_ptr is two pointers: one to the resource being managed, and another to a "control block", a dynamically allocated object maintaining internal state, in particular the reference count
    // when std::shared_ptr is created via constructor, it allocates memory for the managed object, usually passed in, and the control block, created in the constructor; when created via std::make_shared, these two allocations are combined into one
    // when multiple independent std::shared_ptr are created pointing at the same resource, their independent control blocks will have no idea about each other and deallocate the resource multiple times
    // but when a std::shared_ptr is copy assigned, the single control block is updated with the new reference count

    // a std::unique_ptr can be converted into a std::shared_ptr via a constructor that takes a std::unique_ptr r-value and does a move; the reverse isn't possible safely, so returning a smart pointer from a function should use std::unique_ptr and convert to std::shared_ptr if desired

    // std::shared_ptr has the same problems as std::unique_ptr in that it won't work if dynamically allocated and not deallocated (or inside an object that's dynamically allocated and not deallocated), but multiplied by the number of shared pointers at the same object

    // std:shared_ptr does not get the ability to manage C-style arrays until c++20

    return 0;
}