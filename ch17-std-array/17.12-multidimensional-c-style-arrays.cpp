#include "../print.h"

int main() {
    // C-style arrays can be multidimensional:
    [[maybe_unused]] int a[3][5] {};
    a[2][3] = 7;

    [[maybe_unused]] int tictactoe[3][3][3] {};
    // multidimensional arrays are actually stored as 1D arrays in *row-major* order (row-by-row, left to right, top to bottom)
    // e.g. [0][0], [0][1], [1][0], [1][1], ...

    // aggregate initialization:
    int array[3][5] { { 1, 2, 3, 4, 5 }, { 6, 7, 8 }, { 9, 10, 11, 12 } };
    // missing initializers will be value initialized

    // we can omit (only) the leftmost length specification:
    [[maybe_unused]] int array2[][5] { { 1, 2, 3, 4, 5 },
                                       { 6, 7, 8 },
                                       { 9, 10, 11, 12 } };

    // iteration needs two loops:
    for (std::size_t row { 0 }; row < std::size(array); row++) {
        for (std::size_t col { 0 }; col < std::size(array[0]); col++) {
            std::cout << array[row][col] << " ";
        }
        std::cout << "\n";
    }
    for (const auto &arow : array) {
        for (const auto &e : arow) {
            std::cout << e << " ";
        }
        std::cout << "\n";
    }

    // another example
    constexpr int num_rows { 10 };
    constexpr int num_cols { 10 };
    int product[num_rows][num_cols] {};
    for (std::size_t row { 1 }; row < num_rows; row++) {
        for (std::size_t col { 1 }; col < num_cols; col++) {
            product[row][col] =
                static_cast<int>(row * col); // prevent conversion warning
        }
    }

    for (std::size_t row { 1 }; row < num_rows; row++) {
        for (std::size_t col { 1 }; col < num_cols; col++) {
            std::cout << product[row][col] << "\t";
        }
        std::cout << "\n";
    }

    // when working with Cartesian coordinates as 2D arrays, the x-coordinate selects the column and the y is the row: (x, y) -> [y][x]

    return 0;
}