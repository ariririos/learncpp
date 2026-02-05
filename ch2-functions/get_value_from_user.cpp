#include <iostream>

void unreferenced_parameter(int) {}
int get_value_from_user();
void print_doubled(int num);

int main() {
  print_doubled(get_value_from_user());
  return 0;
}

int get_value_from_user() {
  std::cout << "Enter an integer: ";
  int input {};
  std::cin >> input;
  return input;
}

void print_doubled(int num) {
  std::cout << num << " doubled is " << num * 2 << "\n";
}
