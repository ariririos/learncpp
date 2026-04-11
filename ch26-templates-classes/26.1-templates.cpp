#include "26.1-Array-no-defs.h"
#include "26.1-Array.cpp" // not recommended to include a .cpp file but just this once

template class Array<int>;
template class Array<double>;
// the `template class` syntax causes the compiler to explicitly instantiate the specific template classes we want
