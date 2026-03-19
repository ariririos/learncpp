#include <cassert>
#include <cstring>
#include <iostream>

class MyString {
private:
    char *m_data {};
    int m_length {};

public:
    MyString(const char *source = "") {
        assert(source); // check source isn't null
        m_length = std::strlen(source) + 1;
        m_data = new char[m_length];
        // copy source into the internal buffer
        for (int i { 0 }; i < m_length; i++) {
            m_data[i] = source[i];
        }
    }
    ~MyString() { delete[] m_data; }
    char *get_string() { return m_data; }
    int get_length() { return m_length; }
    // the implicit copy constructor will look like:
    // MyString(const MyString &source)
    //     : m_length { source.m_length }, m_data { source.m_data } {}
};

class MyString2 {
private:
    char *m_data {};
    int m_length {};

public:
    MyString2(const char *source = "") {
        assert(source); // check source isn't null
        m_length = std::strlen(source) + 1;
        m_data = new char[m_length];
        // copy source into the internal buffer
        for (int i { 0 }; i < m_length; i++) {
            m_data[i] = source[i];
        }
    }
    ~MyString2() { delete[] m_data; }
    char *get_string() { return m_data; }
    int get_length() { return m_length; }
    void deep_copy(const MyString2 &source) {
        // first deallocate our internal buffer
        delete[] m_data;
        // length isn't a pointer so we can shallow copy is
        m_length = source.m_length;
        // but for the pointer we need to deep copy
        // first check that it's non-null
        if (source.m_data) {
            m_data = new char[m_length];
            for (int i { 0 }; i < m_length; i++) {
                m_data[i] = source.m_data[i];
            }
        } else {
            m_data = nullptr;
        }
    }
    MyString2(const MyString2 &source) { deep_copy(source); }
    MyString2 &operator=(const MyString2 &source) {
        if (this != &source) { // self-assignment check
            // in deep_copy we deallocate the existing buffer to prevent a memory leak
            deep_copy(source);
        }
        return *this;
    }
};

int main() {
    // the implicit copy constructor and implicit assignment operator provided by default are fine for classes that don't dynamically allocate memory
    // they will just do memberwise initialization and assignment

    // for example:
    /*
    MyString hello { "Hello world!" };
    {
        // this one's m_data points to the same memory as hello above
        MyString copy { hello };
        // so it is destroyed here
    }
    // and the array they both points to has been deallocated
    std::cout << hello.get_string() << "\n"; // undefined behavior
    // and we get a double free "here" (at the end of the enclosing block)
    */

    // with updated copy constructor and assignment:
    MyString2 hello { "Hello world!" };
    {
        // deep copy
        MyString2 copy { hello };
    }
    std::cout << hello.get_string() << "\n"; // fine

    // rule of three: if we define any of user-defined destructor, copy constructor, or copy assignment operator, then we probably require all three
    // this is because we're probably dealing with dynamic memory
    // copy constuctor and copy assignment need to handle deep copies; destructor needs to deallocate

    // but overall prefer using a standard library class over rolling your own

    return 0;
}