#include <algorithm>
#include <array>
#include <chrono>
#include <cstddef>
#include <iostream>
#include <numeric>

const int g_array_elements { 10000 };

class Timer {
private:
    using Clock = std::chrono::steady_clock;
    using Second = std::chrono::duration<double, std::ratio<1>>;
    std::chrono::time_point<Clock> m_beg { Clock::now() };

public:
    void reset() { m_beg = Clock::now(); }

    double elapsed() const {
        return std::chrono::duration_cast<Second>(Clock::now() - m_beg).count();
    }
};

void sort_array(std::array<int, g_array_elements> &array) {
    for (std::size_t start_index { 0 }; start_index < g_array_elements - 1;
         start_index++) {
        // smallest_index is the smallest value we've seen so far
        std::size_t smallest_index { start_index };
        // look for a smaller value
        for (std::size_t curr_index { start_index + 1 };
             curr_index < g_array_elements; curr_index++) {
            // if we found a smaller one, store its index
            if (array[curr_index] < array[smallest_index]) {
                smallest_index = curr_index;
            }
        }
        // at this point smallest_index holds the smallest value
        // so we can do the swap
        std::swap(array[start_index], array[smallest_index]);
    }
}

int main() {
    std::array<int, g_array_elements> array;
    std::iota(array.rbegin(), array.rend(), 1);

    Timer t;
    sort_array(array);
    std::cout << "Time elapsed: " << t.elapsed() << " seconds\n";

    std::array<int, g_array_elements> array2;
    std::iota(array2.rbegin(), array2.rend(), 1);

    Timer t2;
    std::ranges::sort(array2);
    std::cout << "Time elapsed: " << t2.elapsed() << " seconds\n";

    return 0;
}
