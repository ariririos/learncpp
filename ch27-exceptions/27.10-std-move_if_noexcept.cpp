#include <iostream>
#include <stdexcept>
#include <utility>

class MoveClass {
private:
    int *m_resource {};

public:
    MoveClass() = default;

    MoveClass(int resource) : m_resource { new int { resource } } {}

    MoveClass(const MoveClass &that) {
        if (that.m_resource != nullptr) {
            m_resource = new int { *that.m_resource };
        }
    }

    MoveClass(MoveClass &&that) noexcept : m_resource { that.m_resource } {
        that.m_resource = nullptr;
    }

    ~MoveClass() {
        std::cout << "Destroying " << *this << "\n";
        delete m_resource;
    }

    friend std::ostream &operator<<(std::ostream &out,
                                    const MoveClass &move_class) {
        out << "MoveClass(";

        if (move_class.m_resource == nullptr) {
            out << "empty";
        } else {
            out << *move_class.m_resource;
        }

        out << ")";

        return out;
    }
};

class CopyClass {
public:
    bool m_throw {};

    CopyClass() = default;

    CopyClass(const CopyClass &that) : m_throw { that.m_throw } {
        if (m_throw) {
            throw std::runtime_error { "abort!" };
        }
    }
};

int main() {
    // when we are copying an object, if it fails, the object being copied isn't changed in any way, and we can just discard the failed copy and move on -- the strong exception guarantee is upheld

    // but a failed move after ownership has been transferred will result in the source object being left in a modified state; if the source object is a temporary then this doesn't matter, but otherwise we've damaged the source object
    // to maintain a strong execption guarantee, we'd need to transfer ownership back, but if the first move failed there's no guarantee the move back will succeed

    // to give move constructors a strong exception guarantee, we not only have to make sure that the body of the move constructor doesn't throw, but that it also doesn't call any potentially throwing functions

    // for example:

    // CopyClass's copy constructor will throw an exception if copying from a CopyClass object whose m_throw == true

    std::pair my_pair { MoveClass { 13 },
                        CopyClass {} }; // prints "Destroying MoveClass(empty)"
    // the MoveClass object is empty because it's a temporary that starts out containing "13", but then the MoveClass subobject in my_pair gets move constructed from it, so it ends up empty when it gets destroyed at the end of the expression
    std::cout
        << "my_pair.first: " << my_pair.first
        << "\n"; // prints "my_pair.first: MoveClass(13)" (this is the object that was move constructed into from the previous line)

    try {
        my_pair.second.m_throw = true; // to trigger copy constructor exception
        std::pair moved_pair { std::move(
            my_pair) }; // prints "destroying MoveClass(13)"
        // we created move_pair by copy constructing its CopyClass subobject, which lacks a move constructor, but that copy constructor threw an exception; then construction of moved_pair is aborted, so its already-created subobjects (MoveClass) are destroyed; finally, the exception is caught and execution continues below in the catch block
        std::cout << "moved pair exists\n"; // never prints
    } catch (const std::exception &ex) {
        std::cerr << "Error found: " << ex.what()
                  << "\n"; // prints "Error found: abort!"
    }

    std::cout << "my_pair.first: " << my_pair.first
              << "\n"; // prints "my_pair.first: MoveClass(empty)"
    // when construction of moved_pair was aborted above, the original had already been moved out of
    // this violates the strong exception guarantee because my_pair.first was damaged

    // note that the guarantee could've been maintained if std::pair had tried to do a copy instead of a move; moved_pair would've failed to construct, but my_pair wouldn't have been altered (we would've used the MoveClass copy constructor instead)
    // we can do this using std::move_if_noexcept, which is a counterpart to std::move, used the same way, that does a move if its argument won't throw an exception when move constructed (or if it's move-only and has no copy constructor)
    // if its argument can be moved safely, it will be converted into an r-value reference; otherwise, it will return a regular l-value reference

    // the same code as above using std::move_if_noexcept:
    std::pair my_pair2 { MoveClass { 13 },
                         CopyClass {} }; // prints "Destroying MoveClass(empty)"
    std::cout << "my_pair2.first: " << my_pair2.first
              << "\n"; // prints "my_pair2.first: MoveClass(13)"

    try {
        my_pair2.second.m_throw = true;
        std::pair moved_pair { std::move_if_noexcept(
            my_pair2) };                    // prints "destroying MoveClass(13)"
        std::cout << "moved pair exists\n"; // never prints
    } catch (const std::exception &ex) {
        std::cerr << "Error found: " << ex.what()
                  << "\n"; // prints "Error found: abort!"
    }

    std::cout << "my_pair2.first: " << my_pair2.first
              << "\n"; // prints "my_pair.first: MoveClass(13)"
    // my_pair2 was not modified because the std::pair move constructor isn't noexcept (as of c++20)

    // the stdlib uses std::move_if_noexcept to prefer moves when they are noexcept, e.g. std::vector::resize will use move semantics if the element type has a noexcept move constructor, and copy semantics otherwise; this means std::vector will generally be faster with objects with a noexcept move constructor

    // warning: if a type has potentially throwing move semantics and deleted copy semantics then std::move_if_noexcept will waive the strong exception guarantee and invoke move semantics

    return 0;
}