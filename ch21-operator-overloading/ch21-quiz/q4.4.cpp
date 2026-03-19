#include <cassert>
#include <cmath>
#include <cstdint>
#include <iostream>

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
};

std::ostream &operator<<(std::ostream &out, const FixedPoint2 &num) {
    out << static_cast<double>(num);
    return out;
}

int main() {
    FixedPoint2 a { 0.01 };
    assert(static_cast<double>(a) == 0.01);

    FixedPoint2 b { -0.01 };
    assert(static_cast<double>(b) == -0.01);

    FixedPoint2 c { 1.9 }; // make sure we handle single digit decimal
    assert(static_cast<double>(c) == 1.9);

    FixedPoint2 d {
        5.01
    }; // stored as 5.0099999... so we'll need to round this
    assert(static_cast<double>(d) == 5.01);

    FixedPoint2 e {
        -5.01
    }; // stored as -5.0099999... so we'll need to round this
    assert(static_cast<double>(e) == -5.01);

    // Handle case where the argument's decimal rounds to 100 (need to increase base by 1)
    FixedPoint2 f { 106.9978 }; // should be stored with base 107 and decimal 0
    assert(static_cast<double>(f) == 107.0);

    // Handle case where the argument's decimal rounds to -100 (need to decrease base by 1)
    FixedPoint2 g {
        -106.9978
    }; // should be stored with base -107 and decimal 0
    assert(static_cast<double>(g) == -107.0);

    std::cout << a << " " << b << " " << c << " " << d << " " << e << " " << f
              << " " << g << "\n";
    return 0;
}