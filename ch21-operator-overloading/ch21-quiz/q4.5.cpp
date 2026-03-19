#include <cassert>
#include <cmath>
#include <cstdint>
#include <iostream>
#include <limits>

class FixedPoint2 {
private:
    std::int16_t m_base {};
    std::int8_t m_decimal {};

public:
    explicit FixedPoint2(std::int16_t base = 0, std::int8_t decimal = 0)
        : m_base { base }, m_decimal { decimal } {
        if (m_base < 0 || m_decimal < 0) {
            if (m_base > 0) {
                m_base = -m_base;
            }
            if (m_decimal > 0) {
                m_decimal = -m_decimal;
            }
        }
        m_base += m_decimal / 100;
        m_decimal = m_decimal % 100;
    }
    explicit FixedPoint2(double num) // delegate
        : FixedPoint2 { static_cast<std::int16_t>(num),
                        static_cast<std::int8_t>(std::round(
                            (num - static_cast<std::int16_t>(num)) * 100)) } {}
    explicit operator double() const {
        return m_base + static_cast<double>(m_decimal) / 100;
    }
    friend bool operator==(const FixedPoint2 &fp1, const FixedPoint2 &fp2);
};

std::ostream &operator<<(std::ostream &out, const FixedPoint2 &num) {
    out << static_cast<double>(num);
    return out;
}

bool operator==(const FixedPoint2 &fp1, const FixedPoint2 &fp2) {
    return fp1.m_base == fp2.m_base && fp1.m_decimal == fp2.m_decimal;
}

std::istream &operator>>(std::istream &in, FixedPoint2 &fp) {
    double input {};
    std::cin >> input;
    if (!std::cin) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    fp = FixedPoint2 { input };
    return in;
}

FixedPoint2 operator-(const FixedPoint2 &fp) {
    return FixedPoint2 { -static_cast<double>(fp) };
}

FixedPoint2 operator+(const FixedPoint2 &fp1, const FixedPoint2 &fp2) {
    return FixedPoint2 { static_cast<double>(fp1) + static_cast<double>(fp2) };
}

int main() {
    assert(FixedPoint2 { 0.75 } == FixedPoint2 { 0.75 }); // Test equality true
    assert(
        !(FixedPoint2 { 0.75 } == FixedPoint2 { 0.76 })); // Test equality false

    // Test additional cases -- h/t to reader Sharjeel Safdar for these test cases
    assert(FixedPoint2 { 0.75 } + FixedPoint2 { 1.23 } ==
           FixedPoint2 { 1.98 }); // both positive, no decimal overflow
    assert(FixedPoint2 { 0.75 } + FixedPoint2 { 1.50 } ==
           FixedPoint2 { 2.25 }); // both positive, with decimal overflow
    assert(FixedPoint2 { -0.75 } + FixedPoint2 { -1.23 } ==
           FixedPoint2 { -1.98 }); // both negative, no decimal overflow
    assert(FixedPoint2 { -0.75 } + FixedPoint2 { -1.50 } ==
           FixedPoint2 { -2.25 }); // both negative, with decimal overflow
    assert(FixedPoint2 { 0.75 } + FixedPoint2 { -1.23 } ==
           FixedPoint2 { -0.48 }); // second negative, no decimal overflow
    assert(FixedPoint2 { 0.75 } + FixedPoint2 { -1.50 } ==
           FixedPoint2 { -0.75 }); // second negative, possible decimal overflow
    assert(FixedPoint2 { -0.75 } + FixedPoint2 { 1.23 } ==
           FixedPoint2 { 0.48 }); // first negative, no decimal overflow
    assert(FixedPoint2 { -0.75 } + FixedPoint2 { 1.50 } ==
           FixedPoint2 { 0.75 }); // first negative, possible decimal overflow

    FixedPoint2 a { -0.48 };
    assert(static_cast<double>(a) == -0.48);
    assert(static_cast<double>(-a) == 0.48);

    std::cout << "Enter a number: "; // enter 5.678
    std::cin >> a;
    std::cout << "You entered: " << a << '\n';
    assert(static_cast<double>(a) == 5.68);

    return 0;
}