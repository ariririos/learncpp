#include <algorithm>
#include <iostream>
// #include <map>
#include <string>
#include <vector>

struct StudentGrade {
    std::string name {};
    char grade {};
};

class GradeMap {
private:
    std::vector<StudentGrade> m_map {};

public:
    char &operator[](std::string name) {
        auto found = std::find_if(
            m_map.begin(), m_map.end(),
            [name](const auto &student) { return name == student.name; });
        if (found != m_map.end()) {
            return found->grade;
        }
        return m_map.emplace_back(StudentGrade { name }).grade;
    }
};

int main() {
    GradeMap grades {};

    grades["Joe"] = 'A';
    grades["Frank"] = 'B';

    std::cout << "Joe has a grade of " << grades["Joe"] << '\n';
    std::cout << "Frank has a grade of " << grades["Frank"] << '\n';

    // this could've been implemented using std::map like so:
    // std::map<std::string, char> grades2 { { "Joe", 'A' }, { "Frank", 'B' } };
    // grades["Susan"] = 'C';
    // grades["Tom"] = 'D';
    // std::cout << "Joe has a grade of " << grades["Joe"] << "\n";
    // std::cout << "Frank has a grade of " << grades["Frank"] << "\n";

    return 0;
}