#include "26.1-Array-no-defs.h"
// the name of the class above is Array<T> unless used within the class (like for the copy constructor and assignment operator which can just use Array)
template <typename T> T &Array<T>::operator[](int index) {
    assert(index >= 0 && index < m_length);
    return m_data[index];
}
