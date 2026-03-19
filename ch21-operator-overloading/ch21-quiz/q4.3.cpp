#include <cassert>
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
    explicit operator double() const {
        return m_base + static_cast<double>(m_decimal) / 100;
    }
    friend bool test_decimal(const FixedPoint2 &fp);
};

std::ostream &operator<<(std::ostream &out, const FixedPoint2 &num) {
    out << static_cast<double>(num);
    return out;
}

bool test_decimal(const FixedPoint2 &fp) {
    if (fp.m_base >= 0) {
        return fp.m_decimal >= 0 && fp.m_decimal < 100;
    } else {
        return fp.m_decimal <= 0 && fp.m_decimal > -100;
    }
}

int main() {
    FixedPoint2 a { 34, 56 };
    std::cout << a << '\n';
    std::cout << static_cast<double>(a) << '\n';
    assert(static_cast<double>(a) == 34.56);

    FixedPoint2 b { -2, 8 };
    assert(static_cast<double>(b) == -2.08);

    FixedPoint2 c { 2, -8 };
    assert(static_cast<double>(c) == -2.08);

    FixedPoint2 d { -2, -8 };
    assert(static_cast<double>(d) == -2.08);

    FixedPoint2 e { 0, -5 };
    assert(static_cast<double>(e) == -0.05);

    FixedPoint2 f { 0, 10 };
    assert(static_cast<double>(f) == 0.1);

    FixedPoint2 g { 1, 104 };
    std::cout << g << '\n';
    std::cout << static_cast<double>(g) << '\n';
    assert(static_cast<double>(g) == 2.04);
    assert(test_decimal(g));

    FixedPoint2 h { 1, -104 };
    assert(static_cast<double>(h) == -2.04);
    assert(test_decimal(h));

    FixedPoint2 i { -1, 104 };
    assert(static_cast<double>(i) == -2.04);
    assert(test_decimal(i));

    FixedPoint2 j { -1, -104 };
    assert(static_cast<double>(j) == -2.04);
    assert(test_decimal(j));

    return 0;
}