#ifndef INTARRAY_H
#define INTARRAY_H

#include <algorithm>
#include <cassert>
#include <cstddef>

class IntArray {
private:
    int m_length {};
    int *m_data {};

public:
    // constructor for empty container
    IntArray() = default;

    // constructor for container of predetermined size
    IntArray(int length) : m_length { length } {
        assert(length >= 0);
        if (length > 0) {
            m_data = new int[static_cast<std::size_t>(length)] {};
        }
    }

    ~IntArray() {
        delete[] m_data;
        // no need to set m_data to null or m_length to 0 because the object is about to be destroyed here
    }

    void erase() {
        delete[] m_data;
        // need to set m_data to nullptr and m_length to zero here or we will be left pointing at deallocated memory
        m_data = nullptr;
        m_length = 0;
    }

    int &operator[](int index) {
        assert(index >= 0 && index < m_length);
        return m_data[index];
    }

    int get_length() const { return m_length; }

    // two functions to resize the array: reallocate to destroy any current elements and resize (fast) and resize to keep any current elements then resize (slow)
    void reallocate(int new_length) {
        erase();

        if (new_length <= 0) {
            return;
        }

        m_data = new int[static_cast<std::size_t>(new_length)];
        m_length = new_length;
    }

    void resize(int new_length) {
        if (new_length == m_length) {
            return;
        }

        if (new_length <= 0) {
            erase();
            return;
        }

        int *data { new int[static_cast<std::size_t>(new_length)] };

        if (m_length > 0) {
            int elements_to_copy { (new_length > m_length) ? m_length
                                                           : new_length };
            std::copy_n(m_data, elements_to_copy, data);
        }

        delete[] m_data;

        m_data = data;
        m_length = new_length;
    }

    // copy constructor and copy assignment
    IntArray(const IntArray &a)
        : IntArray(a.get_length()) { // delegate to the length constructor above
        // then copy over
        std::copy_n(a.m_data, m_length, m_data);
    }

    IntArray &operator=(const IntArray &a) {
        if (&a == this) {
            return *this;
        }

        reallocate(a.get_length());
        std::copy_n(a.m_data, m_length, m_data);

        return *this;
    }

    // optional insert and remove functions
    void insert_before(int value, int index) {
        assert(index >= 0 && index <= m_length);
        // we need a new array one larger than the previous array
        int *data { new int[static_cast<std::size_t>(m_length + 1)] };
        // copy elements up until the index
        std::copy_n(m_data, index, data);
        // do the insertion
        data[index] = value;
        // copy elements after the index
        std::copy_n(m_data + index, m_length - index, data + index + 1);
        // finally delete the old array and use the new one instead
        delete[] m_data;
        m_data = data;
        ++m_length;
    }

    void remove(int index) {
        assert(index >= 0 && index < m_length);
        // if this is the last remaining element, empty the array and bail out
        if (m_length == 1) {
            erase();
            return;
        }
        // otherwise create a new array one smaller than the old one
        int *data { new int[static_cast<std::size_t>(m_length - 1)] };
        // copy elements up until the index
        std::copy_n(m_data, index, data);
        // copy elements after the removed element
        std::copy_n(m_data + index + 1, m_length - index - 1, data + index);
        // finally delete the old array and use the new one instead
        delete[] m_data;
        m_data = data;
        --m_length;
    }

    void insert_at_beginning(int value) { insert_before(value, 0); }
    void insert_at_end(int value) { insert_before(value, m_length); }
};

#endif