#include <algorithm>
#include <iostream>
#include <vector>

struct Data {
    int num, denom;
};

bool operator<(const Data& lhs, const Data& rhs) {
    return lhs.num * rhs.denom < rhs.num * lhs.denom;
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int n;
    std::cin >> n;
    std::vector<Data> a(n);
    for (int i = 0; i < n; ++i) {
        char tmp;
        std::cin >> a[i].num >> tmp >> a[i].denom;
    }
    std::stable_sort(a.begin(), a.end());
    for (const auto& item : a) {
        std::cout << item.num << "/" << item.denom << " ";
    }
}
