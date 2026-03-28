#include <functional>
#include <iostream>
#include <vector>

class Teacher {
private:
    std::string m_name {};

public:
    Teacher(std::string_view name) : m_name { name } {}
    const std::string &get_name() const { return m_name; }
};

class Department {
private:
    const Teacher &m_teacher;

public:
    Department(const Teacher &teacher) : m_teacher { teacher } {}
};

int main() {
    // aggregation is another form of object composition

    // an aggregation relates an object/class and a part/member when:
    // - the part is part of the class
    // - the part can belong to more than one object at a time
    // - the part does *not* have its existence managed by the object
    // - the part does not know about the existence of the object

    // like a composition, an aggregation is still a part-whole relationship and unidirectional; but unlike one, parts can belong to more than one object at a time, and the whole object isn't responsible for the existence and lifetime of its parts

    // aggregation is implemented similarly to composition but with pointers/references to objects created outside the scope of the class; it typically takes the objects it'll point it at constructor parameters or starts empty and has member functions/operators to add subobjects later
    // when the aggregation object is destroyed, the pointer/references to its parts will be destroyed but the parts themselves will still exist
    Teacher bob { "Bob" };
    {
        Department department { bob };
    }
    std::cout << bob.get_name() << " still exists\n";

    // composition and aggregation could be mixed in one single class, e.g. a Department that holds a name (handled by composition) and a Teacher (handled by aggregation)

    // when using an aggregation, we have to be careful to deallocate parts separately from the parent object; for this reason, compositions should be favored over aggregations

    // if we want to hold references in a vector (e.g. for multiple Teachers in a Department), we can't do it directly, because the elements of a fixed array or stdlib list must be assignable, and references can't be assigned
    // for example this is illegal:
    // std::vector<const Teacher &> m_teachers {};

    // we can use std::reference_wrapper instead (from <functional>), which acts like a reference but allows assignment and copying
    // the object being wrapped in a std::reference_wrapper can't be an anonymous object, otherwise the reference would be left dangling
    // you use .get() to get the object back out of the wrapper
    std::string tom { "Tom" };
    std::string berta { "Berta" };
    std::vector<std::reference_wrapper<std::string>> names { tom, berta };

    std::string jim { "Jim" };
    names.emplace_back(jim);

    for (auto name : names) {
        name.get() += " Beam";
    }

    std::cout << jim << "\n"; // Jim Beam (Tom and Berta were also modified)

    // if we want a vector of const references, we can do it like this:
    std::vector<std::reference_wrapper<const std::string>> names2 { tom,
                                                                    berta };
    return 0;
}