#include <iostream>

class Cents {
private:
    int m_cents {};

public:
    Cents(int cents) : m_cents { cents } {}
    friend std::ostream &operator<<(std::ostream &ostr, const Cents &c) {
        ostr << c.m_cents;
        return ostr;
    }
};

template <typename T> const T &max(const T &x, const T &y) {
    return (x < y) ? y : x;
}

template <typename T> T average(const T *my_array, int num_values) {
    T sum { 0 };
    for (int count { 0 }; count < num_values; count++) {
        sum += my_array[count];
    }
    sum /= num_values;
    return sum;
}

int main() {
    Cents nickel { 5 };
    Cents dime { 10 };

    // this won't compile due to missing operator<
    // Cents bigger { max(nickel, dime) };
    // std::cout << bigger << " is bigger\n";

    Cents cents_array[] { Cents { 5 }, Cents { 10 }, Cents { 15 },
                          Cents { 14 } };

    // and this won't compile because of missing operator+= and operator /=
    // std::cout << average(cents_array, 4) << "\n";

    return 0;
}