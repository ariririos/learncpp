#include "26.1-Array.h"
#include <iostream>

int main() {
    // template classes are commonly used for container classes; if you don't actually ever use a template class, the compiler won't even compile it
    const int length { 12 };
    Array<int> int_array { length };
    Array<double> double_array { length };

    for (int count { 0 }; count < length; ++count) {
        int_array[count] = count;
        double_array[count] = count + 0.5;
    }

    for (int count { length - 1 }; count >= 0; --count) {
        std::cout << int_array[count] << "\t" << double_array[count] << "\n";
    }

    // if we tried to separate out the Array<T>::operator[] definition into a separate .cpp file, we'd get linker errors about "undefined reference to Array<int>::operator[](int)" etc.
    // this is because of the requirement that the compiler must see both a full class template definition (not just a declaration) and the specific template types needed, combined with the fact that files are compiled individually
    // when main.cpp is compiled, Array.h gets copied into it; it sees Array<double> and Array<int> and instantiates them, and a declaration for Array<T>::operator[], so it allows the call assuming it will be defined elsewhere
    // when Array.cpp gets compiled separately, Array.h gets copied into it, but the compiler won't see any code in the file that actually requires the Array class template or Array<int>::operator[] function template to be instantiated, so it won't do anything
    // and finally, we get a linker error because we tried to use Array<int>::operator[] but that template never got instantiated

    // how to work around this:
    // - preferred solution: just include all template class code into the header (no separate Array.cpp); this causes separate local instances of the template class in each file that includes the header, which increases compile/link times (but the linker should deduplicate and keep the executable the same size), but this is fine unless these times get excessive
    // - we can put the Array.cpp code into a file called Array.inl (for "inline") and include that at the end of Array.h (inside the header guard) -- this is the same as actually putting the code in the header but keeps it more organized
    // - one last solution is a three-file approach, with the template class definition in the header, the template class member functions in the code file, and a third file that contains all of the instantiated classes we need (see 26.1-templates.cpp)
    // the last approach would need to be compiled like `g++ -o 26.1 26.1-intro.cpp 26.1-Array.cpp 26.1-templates.cpp`
    return 0;
}