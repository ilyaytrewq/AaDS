#include <algorithm>
#include <iostream>
#include <vector>
#include <random>

struct Circle {
    double x, y, r;
};

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::vector<Circle> c(3);
    for (int i = 0; i < 3; ++i) {
        std::cin >> c[i].x >> c[i].y >> c[i].r;
    }

    double xmin = 1e18, ymin = 1e18;
    double xmax = -1e18, ymax = -1e18;

    for (int i = 0; i < 3; ++i) {
        xmin = std::min(xmin, c[i].x - c[i].r);
        xmax = std::max(xmax, c[i].x + c[i].r);
        ymin = std::min(ymin, c[i].y - c[i].r);
        ymax = std::max(ymax, c[i].y + c[i].r);
    }

    double Srec = (xmax - xmin) * (ymax - ymin);

    const int N = 2000000;

    std::mt19937_64 rng(449205784203485);
    std::uniform_real_distribution<double> dx(xmin, xmax);
    std::uniform_real_distribution<double> dy(ymin, ymax);

    long long M = 0;
    for (int i = 0; i < N; ++i) {
        double x = dx(rng);
        double y = dy(rng);
        bool ok = true;
        for (int j = 0; j < 3; ++j) {
            double dx_ = x - c[j].x;
            double dy_ = y - c[j].y;
            if (dx_ * dx_ + dy_ * dy_ > c[j].r * c[j].r) {
                ok = false;
                break;
            }
        }
        if (ok)
            ++M;
    }

    double S = (double)M / N * Srec;
    std::cout.precision(30);
    std::cout << S << "\n";
    return 0;
}
