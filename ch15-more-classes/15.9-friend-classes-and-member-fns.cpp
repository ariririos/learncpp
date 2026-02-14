#include <iostream>

class Storage {
private:
    int m_n_value {};
    double m_d_value {};

public:
    Storage(int n_value, double d_value)
        : m_n_value { n_value }, m_d_value { d_value } {}
    friend class Display;
};

class Display {
private:
    bool m_display_int_first {};

public:
    Display(bool display_int_first)
        : m_display_int_first { display_int_first } {}

    void display_storage(const Storage &storage) {
        // since Display is a friend of Storage, its private members can be
        // accessed here:
        if (m_display_int_first) {
            std::cout << storage.m_n_value << " " << storage.m_d_value << "\n";
        } else {
            std::cout << storage.m_d_value << " " << storage.m_n_value << "\n";
        }
    }

    void set_display_int_first(bool b) { m_display_int_first = b; }
};

class Storage2; // forward declaration of Storage (needed for display_storage
                // forward declaration)

class Display2 {
private:
    bool m_display_int_first {};

public:
    Display2(bool display_int_first)
        : m_display_int_first { display_int_first } {}

    void display_storage(
        const Storage2
            &storage); // just the declaration, definition has to wait until
                       // we've seen Storage2 since we access its members
};

class Storage2 {
private:
    int m_n_value {};
    double m_d_value {};

public:
    Storage2(int n_value, double d_value)
        : m_n_value { n_value }, m_d_value { d_value } {}
    // we actually makes the display_storage member function a friend here
    // we have to wait until we've actually seen the full definition of Display2
    // since we reference its members
    friend void Display2::display_storage(const Storage2 &storage);
};

// and now we can actually define display_storage
// once we've seen the full definition of Storage2
void Display2::display_storage(const Storage2 &storage) {
    if (m_display_int_first) {
        std::cout << storage.m_n_value << " " << storage.m_d_value << "\n";
    } else {
        std::cout << storage.m_d_value << " " << storage.m_n_value << "\n";
    }
}

int main() {
    Storage storage { 5, 6.7 };
    Display display { false };
    display.display_storage(storage);
    display.set_display_int_first(true);
    display.display_storage(storage);

    // Display has no access to the `this` pointer of Storage (which is really a
    // function parameter anyway) friendship is not reciprocal (Storage cannot
    // access private members of Display unless Display declares it as a friend)
    // friendship is not transitive (if A is a friend of B and B is a friend of
    // C, that doesn't mean A is a friend of C) friendship is not inherited (if
    // A makes B a friend, classes derived from B are not friends of A) friend
    // class declaration acts as a forward declaration

    // making just the display_storage member function a friend requires a few
    // steps: rearranging Display and Storage (so that the friend declaration of
    // display_storage in Storage will have actually seen Display's members by
    // then) forward declaration of Storage (for display_storage) declaration of
    // display_storage (we have to wait to define it until we've seen the full
    // definition of Storage because we access Storage members) actually making
    // display_storage a friend (here is where the rearrangement was necessary)
    // and finally defining display_storage after Storage (since we access its
    // members)

    Storage2 storage2 { 5, 6.7 };
    Display2 display2 { false };
    display2.display_storage(storage2);

    // if each class was defined in a separate header file and member functions were defined in corresponding cpp files, all this rearrangement would be unnecessary

    return 0;
}