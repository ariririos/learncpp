#include <iostream>

class Point2D {
private:
    int m_x;
    int m_y;

public:
    Point2D() : m_x { 0 }, m_y { 0 } {}
    Point2D(int x, int y) : m_x { x }, m_y { y } {}
    friend std::ostream &operator<<(std::ostream &out, const Point2D &point) {
        out << "(" << point.m_x << ", " << point.m_y << ")";
        return out;
    }
    void set_point(int x, int y) {
        m_x = x;
        m_y = y;
    }
};

class Creature {
private:
    std::string m_name;
    Point2D m_location;

public:
    Creature(std::string_view name, const Point2D &location)
        : m_name { name }, m_location { location } {}
    friend std::ostream &operator<<(std::ostream &out,
                                    const Creature &creature) {
        out << creature.m_name << " is at " << creature.m_location;
        return out;
    }
    void move_to(int x, int y) { m_location.set_point(x, y); }
};

int main() {
    // object composition is a "has-a" relationship between two objects; structs and classes are called "composite types" because of this relationship
    // composition and aggregation are the two main types of object composition; this section is about composition and the next is about aggregation

    // a composition relates an object/class and a part/member when:
    // - the part is a part of the object
    // - the part can only belong to one object at a time
    // - the part has its existence managed by the object
    // - the part doesn't know about the existence of the object
    // the object is responsible for the existence of the parts, usually by the part being created when the object is and being destroyed similarly; but more generally by the part's lifetime being managed transparently by the object
    // the part is unaware of the object (a unidirectional relationship); the part can be transferred between objects but remains in the same type of relationship after the transfer

    // Fraction is a composition:
    class Fraction {
    private:
        // numerator and denominator cannot belong to more than one Fraction at a time, and they have no idea they're part of a Fraction because all the information they hold is an integer
        // when the Fraction is created, these two members are created as well; when it's destroyed, so are these
        int m_numerator;
        int m_denominator;

    public:
        Fraction(int numerator = 0, int denominator = 1)
            : m_numerator { numerator }, m_denominator { denominator } {}
    };

    // composition models "has-a" type relationships, but more accurately, it models "part-of" relationships

    // compositions are usually implemented as structs or class with normal data members, which ties their lifetimes to the struct/class; if the composition needs dynamic memory, the data members can be pointers, and it should handle the memory internally

    // composition should be the default when designing a new class

    // some variations on compositions:
    // - deferring creation of parts until needed
    // - using a part given as input rather than creating it yourself
    // - delegating destruction of parts to some other object
    // but the composition always manages its own parts without its user having to do anything

    // when deciding whether to use a composition (i.e. a new class) instead of directly implementing a feature, consider whether: the new class can be kept simple, self-contained, and integrates well into the outer class (i.e. the outer class just focuses on coordinating and delegation to its parts); a class should do one thing, either storage/manipulation of data (like Point2D) or coordination of members (like Creature)
}