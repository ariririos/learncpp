#include <iostream>

void do_print() { std::cout << "in do_print\n"; }

int main() {
  std::cout << "in main\n";
  do_print();
  std::cout << "back in main\n";
  return 0;
}