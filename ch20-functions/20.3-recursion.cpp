#include <iostream>
#include <vector>

void count_down(int count) {
    if (count % 1000000 == 0)
        std::cout << "push " << count << "\n";
    count_down(count - 1);
    // if tail-call optimization isn't done here, this will overflow the stack, otherwise it'll go on forever
}

void count_down1(int count) {
    std::cout << "push " << count << "\n";
    if (count > 1) {
        count_down1(count - 1);
    }
    std::cout << "pop " << count << "\n";
}

int sum_to(int to) {
    if (to <= 0) {
        return 0;
    }
    if (to == 1) {
        return 1;
    }
    return sum_to(to - 1) +
           to; // can't do to-- in this expression because using and modifying a variable in the same expression is undefined
}

int g_total_calls { 0 };

int fibonacci(int count) {
    g_total_calls++;
    if (count == 0) {
        return 0;
    }
    if (count == 1) {
        return 1;
    }
    return fibonacci(count - 1) + fibonacci(count - 2);
}

int g_total_calls2 { 0 };
int fibonacci_memoed(std::size_t count) {
    g_total_calls2++;
    static std::vector results { 0, 1 };
    if (count < std::size(results)) {
        return results[count];
    }
    results.push_back(fibonacci_memoed(count - 1) +
                      fibonacci_memoed(count - 2));
    return results[count];
}

int fibonacci_iter(std::size_t count) {
    int *sum { new int[count] };
    sum[1] = 1;
    for (std::size_t i { 2 }; i < count; i++) {
        sum[i] = sum[i - 1] + sum[i - 2];
    }
    return sum[count - 1];
}

int main() {
    // count_down(5); // this either goes on forever or overflows the stack depending on optimization
    count_down1(5); // this has a base case so it'll terminate properly
    std::cout << sum_to(5) << "\n";

    for (int count { 0 }; count < 13; count++) {
        std::cout << fibonacci(count) << " ";
    }
    std::cout << "\n";
    std::cout << "fibonacci() called " << g_total_calls
              << " times\n"; // 1205 times

    // memoization caches the results of previous calls
    for (int count { 0 }; count < 13; count++) {
        std::cout << fibonacci_memoed(static_cast<std::size_t>(count)) << " ";
    }
    std::cout << "\n";
    std::cout << "fibonacci_memoed() called " << g_total_calls2
              << " times\n"; // 35 times

    // a recursive algorithm can always be rewritten iteratively
    std::cout << "fibonacci_iter(13): " << fibonacci_iter(13) << "\n";

    return 0;
}