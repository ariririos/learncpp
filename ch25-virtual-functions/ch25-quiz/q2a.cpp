#include <iostream>

class Shape {
public:
    virtual std::ostream &print(std::ostream &out) const = 0;
    virtual ~Shape() {}
    friend std::ostream &operator<<(std::ostream &out, const Shape &s) {
        return s.print(out);
    }
};
