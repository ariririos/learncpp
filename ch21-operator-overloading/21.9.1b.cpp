#include <string>
#include <vector>

struct StudentGrade {
    std::string name {};
    char grade {};
};

class GradeMap {
private:
    std::vector<StudentGrade> m_map {};
};