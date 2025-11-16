#include <algorithm>
#include <iostream>
#include <vector>

void countingSort(std::vector<int>& a) {
    if (a.empty())
        return;
    int max_val = *std::max_element(a.begin(), a.end());
    int min_val = *std::min_element(a.begin(), a.end());
    std::vector<int> cnt(max_val - min_val + 1, 0);
    for (int x : a) {
        cnt[x - min_val]++;
    }
    int index = 0;
    for (size_t i = 0; i < cnt.size(); ++i) {
        while (cnt[i] > 0) {
            a[index++] = i + min_val;
            cnt[i]--;
        }
    }
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    int n;
    std::cin >> n;
    std::vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> a[i];
    }
    countingSort(a);
    for (int i : a) {
        std::cout << i << " ";
    }
}
