int read_number();
void write_answer(int ans);

int main() {
    int a { read_number() };
    int b { read_number() };

    write_answer(a + b);

    return 0;
}