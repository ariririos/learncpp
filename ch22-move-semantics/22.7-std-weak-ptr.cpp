#include <iostream>
#include <memory>
#include <string>

class Person {
    std::string m_name {};
    std::shared_ptr<Person> m_partner;

public:
    Person(const std::string &name) : m_name { name } {
        std::cout << m_name << " created\n";
    }
    ~Person() { std::cout << m_name << " destroyed\n"; }
    friend bool partner_up(std::shared_ptr<Person> &p1,
                           std::shared_ptr<Person> &p2) {
        if (!p1 || !p2) {
            return false;
        }
        p1->m_partner = p2;
        p2->m_partner = p1;
        std::cout << p1->m_name << " is now partnered with " << p2->m_name
                  << "\n";

        return true;
    }
};

class Resource {
public:
    std::shared_ptr<Resource> m_ptr {};
    Resource() { std::cout << "Resource acquired\n"; }
    ~Resource() { std::cout << "Resource destroyed\n"; }
};

class Person2 {
    std::string m_name;
    std::weak_ptr<Person2> m_partner;

public:
    Person2(const std::string &name) : m_name { name } {
        std::cout << m_name << " created\n";
    }
    ~Person2() { std::cout << m_name << " destroyed\n"; }
    friend bool partner_up2(std::shared_ptr<Person2> &p1,
                            std::shared_ptr<Person2> &p2) {
        if (!p1 || !p2) {
            return false;
        }
        p1->m_partner = p2;
        p2->m_partner = p1;
        std::cout << p1->m_name << " is now partnered with " << p2->m_name
                  << "\n";

        return true;
    }
};

class Person3 {
    std::string m_name;
    std::weak_ptr<Person3> m_partner;

public:
    Person3(const std::string &name) : m_name { name } {
        std::cout << m_name << " created\n";
    }
    ~Person3() { std::cout << m_name << " destroyed\n"; }
    friend bool partner_up3(std::shared_ptr<Person3> &p1,
                            std::shared_ptr<Person3> &p2) {
        if (!p1 || !p2) {
            return false;
        }
        p1->m_partner = p2;
        p2->m_partner = p1;
        std::cout << p1->m_name << " is now partnered with " << p2->m_name
                  << "\n";

        return true;
    }
    std::shared_ptr<Person3> get_partner() const { return m_partner.lock(); }
    const std::string &get_name() const { return m_name; }
};

std::weak_ptr<Resource> get_weak_ptr() {
    auto ptr { std::make_shared<Resource>() };
    return std::weak_ptr<Resource> { ptr };
} // ptr goes out of scope, Resource destroyed

Resource *get_dumb_ptr() {
    auto ptr { std::make_unique<Resource>() };
    return ptr.get(); // NOLINT
} // ptr goes out of scope, Resource destroyed

int main() {
    {
        // circular dependencies with std::shared_ptr will cause them to fail to deallocate when they go out of scope
        auto lucy { std::make_shared<Person>("Lucy") };
        auto ricky { std::make_shared<Person>("Ricky") };
        // lowercase lucy and ricky are the shared pointers, capital Lucy and Ricky are the objects they point at

        partner_up(lucy, ricky);
        // after this call there are two shared pointers pointing to Ricky (ricky and Lucy's m_partner) and two shared pointers pointing to Lucy (lucy and Ricky's m_partner)

        // at this point ricky goes out of scope first (variables are deallocated in reverse order of their declaration)
        // the ricky shared pointer sees Ricky is still being referred to by Lucy's m_partner so it doesn't deallocate Ricky
        // at this point we have one shared pointer to "Ricky" (from Lucy's m_partner) and two shared pointers to "Lucy" (lucy and Ricky's m_partner)
        // then the lucy shared pointer goes out of scope and same thing happens -- it sees Lucy is still being referred to by Ricky's m_partner so Lucy isn't deallocated

        // so at the end of the program there's one shared pointer each to Lucy and Ricky because they refer to each other, so neither can be deallocated
    }

    // a circular reference occurs anytime a series of references (whether actual C++ references, pointers, unique IDs, or any other way to identify specific objects), create a referential loop; this can happen with any number of references, even just one:
    {
        auto ptr1 { std::make_shared<Resource>() };
        ptr1->m_ptr = ptr1;
        // when ptr1 goes out of scope, the Resource isn't deallocated because it points to itself
        // the Resource also can't be deallocated once ptr1 goes out of scope because we can't reassign m_ptr (and trigger the std::shared_ptr to release the Resource), so it leaks memory
    }

    // std::weak_ptr solves the circular dependency problem by acting as an observer -- it can observe and access the same object as a std::shared_ptr but doesn't count as an owner for its reference count
    {
        auto lucy { std::make_shared<Person2>("Lucy") };
        auto ricky { std::make_shared<Person2>("Ricky") };
        partner_up2(lucy, ricky);
        // Lucy and Ricky get deallocated properly at the end of this block
    }

    // std::weak_ptr can't be directly used (it has no operator->); it has to be converted into a std::shared_ptr first using its .lock():
    {
        auto lucy { std::make_shared<Person3>("Lucy") };
        auto ricky { std::make_shared<Person3>("Ricky") };
        partner_up3(lucy, ricky);

        auto partner {
            ricky->get_partner()
        }; // this is okay (won't create a circular reference) because it's a local variable and will go out of scope at the end of the block
        std::cout << ricky->get_name()
                  << "'s partner is: " << partner->get_name() << "\n";
    }

    // unfortunately since std::weak_ptr isn't an owner, it won't keep a resource it's pointing to alive and can end up dangling; but it can check if it's valid or not via its .expired():
    {
        // there's no way for us to tell if a dumb ptr is dangling or not:
        auto dumb { get_dumb_ptr() };
        std::cout
            << "Our dumb ptr is: "
            << ((dumb == nullptr)
                    ? "nullptr\n"
                    : "non-null\n"); // non-null because it still holds the address of the deallocated object

        // but the std::weak_ptr will see that Resource has a reference count of 0; we shouldn't call .lock() on it once we know it's expired -- if we do it'll be a std::shared_ptr to nullptr
        auto weak { get_weak_ptr() };
        std::cout << "Our weak ptr is: "
                  << ((weak.expired()) ? "expired\n" : "valid\n");
    }
    return 0;
}