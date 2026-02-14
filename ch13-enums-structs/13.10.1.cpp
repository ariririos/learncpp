#include <iostream>

struct AdRevenue {
    int ads_watched {};
    int clickthru_rate {};
    double earnings_per_ad {};
};

AdRevenue get_stats() {
    AdRevenue rev {};
    std::cout << "Ads watched: ";
    std::cin >> rev.ads_watched;

    std::cout << "Clickthrough rate (%): ";
    std::cin >> rev.clickthru_rate;

    std::cout << "Average earnings per ad ($): ";
    std::cin >> rev.earnings_per_ad;

    return rev;
}

void print_ad_revenue(const AdRevenue& rev) {
    std::cout << "Ads watched:\t" << rev.ads_watched << "\n";
    std::cout << "Clickthru %:\t" << rev.clickthru_rate << "%\n";
    std::cout << "Avg $ per ad:\t$" << rev.earnings_per_ad << "\n";
    std::cout << "\nTotal revenue: $" << rev.ads_watched * rev.clickthru_rate / 100.0 * rev.earnings_per_ad << "\n";
}

int main() {
    std::cout << "Enter ad statistics.\n";

    AdRevenue rev { get_stats() };
    print_ad_revenue(rev);

    return 0;
}