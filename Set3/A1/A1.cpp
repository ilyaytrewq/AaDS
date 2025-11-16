#include <algorithm>
#include <cmath>
#include <iostream>
#include <random>
#include <vector>

struct Circle {
    double x, y, r;
};

struct Rectangle {
    double x1, x2, y1, y2;
};

const double Sarea = 0.25 * M_PI + 1.25 * std::asin(0.8) - 1;

Rectangle small(std::vector<Circle> c) {
    Rectangle r;
    r.x1 = 0.7;
    r.x2 = 2.3;
    r.y1 = 0.7;
    r.y2 = 2.3;
    return r;
}

Rectangle big(std::vector<Circle> c) {
    double xmin = 1e18, ymin = 1e18;
    double xmax = -1e18, ymax = -1e18;

    for (int i = 0; i < 3; ++i) {
        xmin = std::min(xmin, c[i].x - c[i].r);
        xmax = std::max(xmax, c[i].x + c[i].r);
        ymin = std::min(ymin, c[i].y - c[i].r);
        ymax = std::max(ymax, c[i].y + c[i].r);
    }

    Rectangle r;
    r.x1 = xmin;
    r.x2 = xmax;
    r.y1 = ymin;
    r.y2 = ymax;
    return r;
}

double getS(const int N, const std::vector<Circle>& c, Rectangle r) {
    double xmin = r.x1, ymin = r.y1;
    double xmax = r.x2, ymax = r.y2;

    double Srec = (xmax - xmin) * (ymax - ymin);

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
    return S;
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::cout.precision(12);

    std::cout << Sarea << std::endl;

    std::vector<std::vector<double>> v{
        {1, 1, 1}, {1.5, 2, std::sqrt(5) / 2}, {2, 1.5, sqrt(5) / 2}};
    std::vector<Circle> c(3);
    for (int i = 0; i < 3; ++i) {
        c[i].x = v[i][0];
        c[i].y = v[i][1];
        c[i].r = v[i][2];
    }

    for (int N = 100; N <= 100000; N += 500) {
        auto Ssmall = getS(N, c, small(c));
        auto Sbig = getS(N, c, big(c));
        std::cout.precision(12);
        std::cout << N << ' ' << Ssmall << ' ' << Sbig << ' ' << fabs(Ssmall - Sarea) << ' '
                  << fabs((Sbig - Sarea)) << '\n';
    }
}
