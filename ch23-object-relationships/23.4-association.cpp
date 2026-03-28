#include <iostream>
#include <vector>

class Patient;

class Doctor {
private:
    std::string m_name {};
    std::vector<std::reference_wrapper<const Patient>> m_patient {};

public:
    Doctor(std::string_view name) : m_name { name } {}
    void add_patient(Patient &patient);
    // can't implement here since Doctor hasn't been defined
    friend std::ostream &operator<<(std::ostream &out, const Doctor &doctor);
    const std::string &get_name() const { return m_name; }
};

class Patient {
private:
    std::string m_name {};
    std::vector<std::reference_wrapper<const Doctor>> m_doctor {};
    // this is private because we want users to call Doctor::add_patient() instead
    void add_doctor(const Doctor &doctor) { m_doctor.push_back(doctor); }

public:
    Patient(std::string_view name) : m_name { name } {}
    friend std::ostream &operator<<(std::ostream &out, const Patient &patient);
    const std::string &get_name() const { return m_name; }
    friend void Doctor::add_patient(Patient &patient);
};

void Doctor::add_patient(Patient &patient) {
    // doctor adds patient
    m_patient.push_back(patient);
    // and patient adds doctor
    patient.add_doctor(*this);
}

std::ostream &operator<<(std::ostream &out, const Doctor &doctor) {
    if (doctor.m_patient.empty()) {
        out << doctor.m_name << " has no patients right now";
        return out;
    }
    out << doctor.m_name << " is seeing patients: ";
    for (const auto &patient : doctor.m_patient) {
        out << patient.get().get_name() << " ";
    }
    return out;
}

std::ostream &operator<<(std::ostream &out, const Patient &patient) {
    if (patient.m_doctor.empty()) {
        out << patient.get_name() << " has no doctors right now";
        return out;
    }
    out << patient.m_name << " is seeing doctors: ";
    for (const auto &doctor : patient.m_doctor) {
        out << doctor.get().get_name() << " ";
    }
    return out;
}

class Course {
private:
    std::string m_name {};
    const Course *m_prereq {};

public:
    Course(std::string_view name, const Course *prereq = nullptr)
        : m_name { name }, m_prereq { prereq } {}
};

class Car {
private:
    std::string m_name {};
    int m_id {};

public:
    Car(std::string_view name, int id) : m_name { name }, m_id { id } {}
    const std::string &get_name() const { return m_name; }
    int get_id() const { return m_id; }
};

namespace CarLot {
    Car car_lot[4] {
        { "Prius", 4 }, { "Corolla", 17 }, { "Accord", 84 }, { "Matrix", 62 }
    };
    Car *get_car(int id) {
        for (auto &car : car_lot) {
            if (car.get_id() == id) {
                return &car;
            }
        }
        return nullptr;
    }
}; // namespace CarLot

class Driver {
private:
    std::string m_name {};
    int m_car_id {};

public:
    Driver(std::string_view name, int car_id)
        : m_name { name }, m_car_id { car_id } {}
    const std::string &get_name() const { return m_name; }
    int get_car_id() const { return m_car_id; }
};

int main() {
    // aside from object composition, there are weaker types of relationships, for example association, which implies no whole/part relationship

    // an object/class and another object/member are related by association if:
    // - the associated object (member) is otherwise unrelated to the object (class)
    // - the associated object can belong to more than one object at a time
    // - the associated object does not have its existence managed by the object
    // - the associated object may or may not know about the existence of the object

    // the associated object is otherwise unrelated to the object; it can belong to multiple objects simultaneously, its existence isn't managed by the object, and the two may or may not know about each other
    // the relationship is a "uses-a" relationship

    // associations are often implemented using pointers:
    Patient dave { "Dave" };
    Patient frank { "Frank" };
    Patient betsy { "Betsy" };

    Doctor james { "James" };
    Doctor scott { "Scott" };

    james.add_patient(dave);

    scott.add_patient(dave);
    scott.add_patient(betsy);

    std::cout << james << '\n';
    std::cout << scott << '\n';
    std::cout << dave << '\n';
    std::cout << frank << '\n';
    std::cout << betsy << '\n';

    // but it's better to avoid bidirectional associations if possible

    // objects can have a relationship with objects of the same type (a "reflexive association"), e.g. the relationship between a university course and its prerequisites:
    Course calculus { "18.01" };
    Course physics_with_calculus { "8.01", &calculus };

    // associations can be indirect (not using direct pointers or references), using any sort of data that links two objects together
    Driver d { "Franz", 17 }; // Franz is driving car with ID 17
    Car *car { CarLot::get_car(d.get_car_id()) };

    if (car) {
        std::cout << d.get_name() << " is driving a " << car->get_name()
                  << "\n";
    } else {
        std::cout << d.get_name() << " couldn't find his car\n";
    }
    // this kind of indirect association means we can reference things that don't currently exist (maybe they're in a file or database); pointers are also 4 or 8 bytes compared to an 8- or 16-bit integer

    // composition vs aggregation vs association:
    /*
    +----------------------|-------------|-------------|-------------+
    | Property             | Composition | Aggregation | Association |
    |----------------------|-------------|-------------|-------------|
    | Relationship type    | Whole-part  | Whole-part  | Unrelated   |
    | Members can belong   | No          | Yes         | Yes         |
    | to multiple classes  |             |             |             |
    | Members' existence   | Yes         | No          | No          |
    | managed by class     |             |             |             |
    | Directionality       | Uni         | Uni         | Uni or bi   |
    | Relationship verb    | Part-of     | Has-a       | Uses-a      |
    +----------------------|-------------|-------------|-------------+
    */

    return 0;
}