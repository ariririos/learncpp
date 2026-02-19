#ifndef SIGNED_ARRAY_VIEW_H
#define SIGNED_ARRAY_VIEW_H
#include <cstddef>

// in the same way that string_view can view a string that exists elsewhere (no ownership), a custom wrapper class can provide a signed interface to a container class with unsigned indices; the class will do two things:
// overriding operator[] will allow using a signed integral type as the index
// returning the length of a container as a signed integral type will allow a std::ssize equivalent before c++20
template <typename T>
class SignedArrayView {
private:
    T& m_array;
public:
    SignedArrayView(T& array)
        : m_array { array } {}
    constexpr auto& operator[](std::ptrdiff_t index) { return m_array[static_cast<typename T::size_type>(index)]; }
    constexpr const auto& operator[](std::ptrdiff_t index) const { return m_array[static_cast<typename T::size_type>(index)]; }
    constexpr auto ssize() const { return static_cast<std::ptrdiff_t>(m_array.size()); }
};

#endif