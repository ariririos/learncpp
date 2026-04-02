class Base {
public:
    int m_public {};

protected:
    int m_protected {};

private:
    int m_private {};
};

class Derived : public Base {
public:
    Derived() {
        m_public = 1; // allowed: anyone can access public members
        m_protected =
            2; // allowed: protected base members can be accessed from derived classes
        // m_private = 3; // not allowed: private base members can't be accessed from derived classes
    }
};

class Pub : public Base {
public:
    Pub() {
        m_public = 1;
        m_protected = 2;
        // m_private = 3; // won't work
    }
};

class Pri : private Base {
public:
    Pri() {
        m_public = 1;
        m_protected = 2;
        // m_private = 3; // won't work
    }
};

class D2 : private Base {
    // D2 can access its own members without restriction; it can access Base's m_public and m_protected, which are now private when accessed through D2
public:
    int m_public2 {};

protected:
    int m_protected2 {};

private:
    int m_private2 {};
};

class D3 : public D2 {
    // D3 can access its own members without restriction; D3 can access D2's m_public2 and m_protected2, but not m_private2; m_public2 and m_protected2 keep their access specifiers due to the public inheritance; D3 has no access to Base's m_private, which was already private in Base, nor does it have access to m_protected or m_public, both of which became private when D2 inherited them
public:
    int m_public3 {};

protected:
    int m_protected3 {};

private:
    int m_private3 {};
};

int main() {
    // the protected access specifier allows the class the member belongs to, friends, and derived classes to access the member; but protected members are not accessible from outside the class
    Base base;
    base.m_public = 1; // allowed: anyone can access public members
    // base.m_protected = 2; // not allowed: protected members can't be accessed from outside class
    // base.m_private = 3; // not allowed: private members can't be accessed from outside class

    // protected attributes can be accessed by a derived class directly, but if you later change anything about that protected attribute (e.g. type, semantics), you'll likely need to change both the base class and all derived classes
    // so protected is most useful when you control both the base class and derived classes; private members promote encapsulation but require a larger public API surface
    // **prefer using private** and only use protected when derived classes are planned and the cost to build an interface to private members is too high

    // there are three types of inheritance: public, protected, private; if you don't specify one, it defaults to private

    // so there are three types of member access specifiers and three types of inheritance, giving nine combinations; the types of inheritance change, in the derived class only, the access specifiers of inherited members -- specifically only public and protected members, since private members always stay private
    // - a class can always access its own non-inherited members
    // - the public accesses the members of a class based on the access specifiers of the class it's accessing
    // - a derived class accesses inherited members based on the access specifier inherited from the parent class, which varies depending on the access specifier and the type of inheritance used

    // public inheritance is the most commonly used
    // it doesn't change the access specifier for inherited members: public members stay public, protected members stay protected, and private members are inaccessible to the derived class
    Pub pub;
    pub.m_public = 1;
    // pub.m_protected = 2; // won't work
    // pub.m_private = 3; // won't work
    // **prefer public inheritance unless there's a specific reason not to use it**

    // protected inheritance is rarely used
    // public and protected members become protected, and private members stay inaccessible

    // private inheritance is sometimes used
    // all members from the base class are inherited as private; public and protected members become private, and private members stay inaccessible
    Pri pri;
    // none of these will work, since all inherited members are private or inaccessible:
    // pri.m_public = 1;
    // pri.m_protected = 2;
    // pri.m_private = 3;
    // private inheritance is useful when the derived class has no obvious relationship to the base class but uses it internally

    // the same rules apply for all members, including member functions and types declared inside the class
    return 0;
}