#include "../print.h"
#include <array>

template <typename T, std::size_t Row, std::size_t Col>
void print_array(const std::array<std::array<T, Col>, Row> &arr) {
    for (const auto &arow : arr) {
        for (const auto &e : arow) {
            std::cout << e << " ";
        }
        std::cout << "\n";
    }
}

template <typename T, std::size_t Row, std::size_t Col>
using Array2d = std::array<std::array<T, Col>, Row>;

template <typename T, std::size_t Row, std::size_t Col>
void print_array2d(const Array2d<T, Col, Row> &arr) {
    for (const auto &arow : arr) {
        for (const auto &e : arow) {
            std::cout << e << " ";
        }
        std::cout << "\n";
    }
}

template <typename T, std::size_t Row, std::size_t Col>
constexpr int row_length(const Array2d<T, Row, Col> &) {
    return Row;
}

template <typename T, std::size_t Row, std::size_t Col>
constexpr int col_length(const Array2d<T, Row, Col> &) {
    return Col;
}

template <typename T, std::size_t Row, std::size_t Col>
using ArrayFlat2d = std::array<T, Row * Col>;

template <typename T, std::size_t Row, std::size_t Col> class ArrayView2d {
private:
    std::reference_wrapper<ArrayFlat2d<T, Row, Col>> m_arr {};

public:
    ArrayView2d(ArrayFlat2d<T, Row, Col> &arr) : m_arr { arr } {}

    T &operator[](int i) { return m_arr.get()[static_cast<std::size_t>(i)]; }
    const T &operator[](int i) const {
        return m_arr.get()[static_cast<std::size_t>(i)];
    }

    // pre-c++23 we have to use operator() because multidimensional operator[] isn't supported:
    // T &operator()(int row, int col) {
    //     return m_arr.get()[static_cast<std::size_t>(row * cols() + col)];
    // }
    // const T &operator()(int row, int col) const {
    //     return m_arr.get()[static_cast<std::size_t>(row * cols() + col)];
    // }

    T &operator[](int row, int col) {
        return m_arr.get()[static_cast<std::size_t>(row * cols() + col)];
    }
    const T &operator[](int row, int col) const {
        return m_arr.get()[static_cast<std::size_t>(row * cols() + col)];
    }

    int rows() const { return static_cast<int>(Row); }
    int cols() const { return static_cast<int>(Col); }
    int length() const { return static_cast<int>(Row * Col); }
};

int main() {
    // there isn't a built-in multidimensional std::array, but we can use an array with another array as the template argument:
    std::array<std::array<int, 4>, 3> arr {
        { { 1, 2, 3, 4 }, { 5, 6, 7, 8 }, { 9, 10, 11, 12 } }
    };
    // double braces are required because std::array is a class type (no brace elision)
    // nesting means the array dimensions are switched when declaring but not when accessing
    print(arr[1][2]);

    // using a template to print the array:
    print_array(arr);

    // using an alias template to simplify the declaration:
    Array2d<int, 3, 4> arr2 {
        { { 1, 2, 3, 4 }, { 5, 6, 7, 8 }, { 9, 10, 11, 12 } }
    };
    print_array2d(arr2);
    // and we could keep going to higher dimensions

    // to get the dimensional lengths of a 2D array, we could use std::size() on the array and then again on its first element, but this would result in undefined behavior if any dimension other than the last has a length other than zero
    // a better idea is to use a function template and extract the dimensions directly from the non-type template parameters:
    print(row_length(arr2));
    print(col_length(arr2));

    // to flatten an array and avoid having nested loops to work with it, we can use a view class instead (see ArrayView2d above):
    ArrayFlat2d<int, 3, 4> arr3 { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12 };
    ArrayView2d<int, 3, 4> arr_view { arr3 };

    print(arr_view.rows());
    print(arr_view.cols());

    // iterating through using 1 dimension:
    for (int i { 0 }; i < arr_view.length(); i++) {
        std::cout << arr_view[i] << " ";
    }
    std::cout << "\n";

    // or two dimensions:
    for (int row { 0 }; row < arr_view.rows(); row++) {
        for (int col { 0 }; col < arr_view.cols(); col++) {
            std::cout << arr_view[row, col] << " ";
        }
        std::cout << "\n";
    }

    // as of c++23, std::mdspan provides a modifiable view into a multidimensional array
    // not in a stable version of GCC yet so not showing it here

    return 0;
}