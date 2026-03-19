#include <cassert>
#include <iostream>
class Matrix {
private:
    double m_data[4][4] {};

public:
    double &operator()(int row, int col) {
        assert(row >= 0 && row < 4);
        assert(col >= 0 && col < 4);
        return m_data[row][col];
    }
    double operator()(int row, int col) const {
        assert(row >= 0 && row < 4);
        assert(col >= 0 && col < 4);
        return m_data[row][col];
    }
    void operator()() {
        for (int row { 0 }; row < 4; ++row) {
            for (int col { 0 }; col < 4; ++col) {
                m_data[row][col] = 0.0;
            }
        }
    }
};

class Accumulator {
private:
    int m_counter { 0 };

public:
    int operator()(int i) { return (m_counter += i); }
    void reset() { m_counter = 0; }
};

int main() {
    // operator() can take as many parameters as we declare
    // it can be used to simultate multidimensional overloaded operator[] before c++23
    Matrix matrix;
    matrix(1, 2) = 4.5;
    std::cout << matrix(1, 2) << "\n";
    matrix(); // erase matrix
    std::cout << matrix(1, 2) << "\n";

    // operator() can also be used to create "functors" -- objects that can be called like functions but maintain additional state in their data members, as well as allow additional member functions
    Accumulator acc {};
    std::cout << acc(1) << "\n";
    std::cout << acc(3) << "\n";

    Accumulator acc2 {};
    std::cout << acc2(10) << "\n";
    std::cout << acc2(20) << "\n";
    acc2.reset();
    std::cout << acc2(0) << "\n";

    return 0;
}