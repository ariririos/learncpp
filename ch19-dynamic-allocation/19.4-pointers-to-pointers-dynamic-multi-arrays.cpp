#include <iostream>
int main() {
    int value { 5 };
    int *ptr { &value };
    std::cout << *ptr << "\n";
    int **ptrptr { &ptr };
    std::cout << **ptrptr << "\n";

    // you can't do something like `int** ptrptr { &&value }` to set the pointer directly since operator& requires an lvalue but &value is an rvalue
    // but setting to nullptr is fine:
    int **ptrptr2 { nullptr };

    // dynamically allocating an array of pointers:
    int **array { new int *[10] };

    // dynamically allocating a multidimensional array:
    int x { 7 };
    int (*array2)[5] {
        new int[x][5]
    }; // if the rightmost dimension is constexpr we can do this
    // auto array2 { new int[x][5] }; // this works as well

    // if the rightmost array dimension isn't constexpr, the way to do it is to use an array of pointers and then initialize each one to a dynamic array:
    for (int count { 0 }; count < 10; count++) {
        array[count] = new int[5];
    }
    array[9][4] = 3;
    // this makes it possible to make non-rectangular arrays, e.g. a triangular array by doing `array[count] = new int[count + 1]` above

    // deallocation requires a loop as well:
    for (int count { 0 }; count < 10; count++) {
        delete[] array[count];
    }
    delete[] array;

    // but it's probably better to use a flattened array and do the math like `int get_single_index(int row, int col, int num_cols) { return (row * num_cols) + col; }` and use `array[get_single_index(9, 4, 5)] = 3;`

    // a pointer to a pointer passed to a function can be used to change the value of the pointer it points to; but this is better done using a reference to a pointer instead (12.11)
    return 0;
}