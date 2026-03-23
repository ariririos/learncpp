#include <iostream>
#include <memory> // for std::shared_ptr

class Resource {
public:
    Resource() { std::cout << "Resource acquired\n"; }
    ~Resource() { std::cout << "Resource destroyed\n"; }
};

int main() {
    // auto* res{ new Resource{} }; // don't use dumb ptr, create the Resource with a std::make_shared
    // std::shared_ptr<Resource> ptr1{ res }; // use std::make_shared
    // std::shared_ptr<Resource> ptr2{ res }; // use std::make_shared so you can't have multiple independent std::shared_ptr to the same resource

    auto ptr1 { std::make_shared<Resource>() };
    auto ptr2 { ptr1 };

    return 0;
}