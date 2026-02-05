#include <iostream>
int read_number();
void write_answer(int ans);

int read_number() {
    int x {};
    std::cout << "Enter an integer: ";
    std::cin >> x;
    return x;
}

void write_answer(int ans) { std::cout << "The sum is " << ans << "\n"; }

int main() {
    int a { read_number() };
    int b { read_number() };

    write_answer(a + b);

    return 0;
}