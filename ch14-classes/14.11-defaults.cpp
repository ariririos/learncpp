#include <iostream>

class Foo {
private:
  int m_x{};
  int m_y{};

public:
  Foo() { // default constructor with no arguments
    std::cout << "Foo default constructed\n";
  }
  Foo(int x, int y) : m_x{x}, m_y{y} {
    std::cout << "Foo(" << x << ", " << y << ") constructed\n";
  }
};

class Foo2 {
private:
  int m_x{};
  int m_y{};

public:
  Foo2(int x = 0, int y = 0) : m_x{x}, m_y{y} {
    std::cout << "Foo2(" << m_x << ", " << m_y << ") constructed\n";
  }
  // having a default constructor with no arguments here would lead to ambiguity
  // if trying to construct Foo2 like `Foo2 {}`
};

// if no constructor is provided then the implicit default constructor will be
// generated
class Foo3 {
private:
  int m_x{};
  int m_y{};
  /*
  it would look like:
  public:
      Foo3() {}
  */
};

class Foo4 {
private:
  int m_x{};
  int m_y{};

public:
  Foo4() = default; // explicitly generates the implicit default constructor. if
                    // this wasn't here then `Foo4 foo {}` wouldn't work
  Foo4(int x, int y) : m_x{x}, m_y{y} {
    std::cout << "Foo4(" << m_x << ", " << m_y << ") constructed\n";
  }
};

// the implicit default constructor and the explicitly defaulted default
// constructor will zero-initialize the object and then default-initialize as of
// c++20, all three options below make the class a non-aggregate. previously the
// user-defined default constructor made the class a non-aggregate but the
// implicit and explicitly defaulted default constructors would not.
class User {
private:
  int m_a;
  int m_b{};

public:
  User() {}
  int a() const { return m_a; }
  int b() const { return m_b; }
};

class Default {
private:
  int m_a;
  int m_b{};

public:
  Default() = default;
  int a() const { return m_a; }
  int b() const { return m_b; }
};

class Implicit {
private:
  int m_a;
  int m_b{};

public:
  int a() const { return m_a; }
  int b() const { return m_b; }
};

template <typename T> void print_obj(const T &obj) {
  std::cout << obj.a() << " " << obj.b() << "\n";
}

int main() {
  Foo foo{};
  Foo foo2{}; // same thing as above
  Foo foo3{1, 2};

  Foo2 foo2_1{};     // initializer with all default arguments specified
  Foo2 foo2_2{6, 7}; // specifying the arguments is allowed ofc
  Foo2 foo2_3{6};

  Foo3 foo3_1{}; // implicit default initializer used here

  Foo4 foo4_1{};
  Foo4 foo4_2{1, 2};

  User user{}; // only default-initialized (m_a will be left uninialized)
  print_obj(user);

  Default def{}; // zero-initialized then default-initialized (both m_a and m_b
                 // will be initialized)
  print_obj(def);

  Implicit imp{}; // zero-initialized then default-initialized (both m_a and m_b
                  // will be initialized)
  print_obj(imp);

  return 0;
}