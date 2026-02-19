#include <iostream>
#include <vector>

template <typename T>
class NoisyVec {
private:
    std::vector<T> m_arr {};
public:
    NoisyVec() {}
    NoisyVec(std::vector<T> arr)
        : m_arr { arr } {}

    void push(T val) {
        m_arr.push_back(val);
        std::cout << "Push " << val;
        print_stack();
    }

    void pop() {
        m_arr.pop_back();
        std::cout << "Pop";
        print_stack();
    }

    void print_stack() const {
        std::cout << "\t(Stack:";
        if (m_arr.empty()) {
            std::cout << " empty";
        }
        for (const auto& elem : m_arr) {
            std::cout << " " << elem;
        }
        std::cout << ")\n";
    }

};



int main() {
    NoisyVec<int> arr {};
    arr.print_stack();

    arr.push(1);
    arr.push(2);
    arr.push(3);
    arr.pop();
    arr.push(4);
    arr.pop();
    arr.pop();
    arr.pop();

    return 0;
}