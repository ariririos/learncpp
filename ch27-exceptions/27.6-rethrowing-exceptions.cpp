#include <cassert>
#include <iostream>

class Base {
public:
    virtual ~Base() {}
};

class Derived : public Base {};

class Database {
private:
public:
    void open([[maybe_unused]] std::string_view filename) { throw 1; }
    int get_int_value([[maybe_unused]] std::string table,
                      [[maybe_unused]] std::string key) {
        throw 1;
    }
    int get_int_value_derived([[maybe_unused]] std::string table,
                              [[maybe_unused]] std::string key) {
        throw Derived {};
    }
};

class Log {
public:
    void log_error(std::string_view error) { std::cout << error << "\n"; }
};

Log g_log;

Database *create_database(std::string filename) {
    Database *d {};

    try {
        d = new Database {};
        d->open(filename);
        return d;
    } catch (int exception) {
        delete d;
        g_log.log_error("Creation of Database failed");
    }

    return nullptr;
}

int get_int_value_from_database(Database *d, std::string table,
                                std::string key) {
    assert(d);

    try {
        return d->get_int_value(table, key);
    } catch (int exception) {
        g_log.log_error("get_int_value_from_database failed");
        // if we want to pass an exception back up to the caller, we could pass a new exception back up:
        // throw 'q';
        // but if we want to pass the same exception back up, we could try this first:
        // throw exception;
        // unfortunately this makes a copy-initialized copy of exception, which might be elided, might not
    }
    return 0;
}

int get_int_value_from_database_derived(Database *d, std::string table,
                                        std::string key) {
    assert(d);

    try {
        return d->get_int_value_derived(
            table, key); // throws a Derived exception on failure
    } catch (Base &exception) {
        g_log.log_error("get_int_value_from_database_derived failed");
        // consider what happens here:
        throw exception; // this throws a Base object, not a Derived object
        // a Base reference to a Derived is totally fine but when we copy initialize from exception, which is a Base, we get a Base object out
        // we've just sliced our Derived object
    }
    return 0;
}

namespace Slicing {
    class Base {
    public:
        Base() {}
        virtual void print() { std::cout << "Base"; }
        virtual ~Base() {}
    };

    class Derived : public Base {
    public:
        Derived() {}
        void print() override { std::cout << "Derived"; }
    };
} // namespace Slicing

int main() {
    create_database("database");
    Database *d { new Database };
    get_int_value_from_database(d, "", "");
    try {
        get_int_value_from_database_derived(d, "", "");
    } catch (...) {
    }

    try {
        try {
            throw Slicing::Derived {};
        } catch (Slicing::Base &b) {
            std::cout << "Caught Base b, which is actually a ";
            b.print(); // prints Derived
            std::cout << "\n";
            throw b; // the Derived object gets sliced here
        }
    } catch (Slicing::Base &b) {
        std::cout << "Caught Base b, which is actually a ";
        b.print(); // prints Base
        std::cout << "\n";
    }

    // the right way to rethrow an exception is just use `throw` by itself

    try {
        try {
            throw Slicing::Derived {};
        } catch (Slicing::Base &b) {
            std::cout << "Caught Base b, which is actually a ";
            b.print(); // prints Derived
            std::cout << "\n";
            throw; // we rethrow the object here
        }
    } catch (Slicing::Base &b) {
        std::cout << "Caught Base b, which is actually a ";
        b.print(); // prints Derived
        std::cout << "\n";
    }
    // when we rethrow an exception, no copies are made, and we rethrow the exact same exception that was just caught, preventing a performance hit or slicing

    return 0;
}