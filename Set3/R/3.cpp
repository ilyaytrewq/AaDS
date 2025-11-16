#include <algorithm>
#include <iostream>
#include <vector>

void countSort(std::vector<unsigned int>& a, int exp) {
    std::vector<unsigned int> output(a.size());
    int count[256] = {0};

    for (int i = 0; i < a.size(); ++i) {
        count[(a[i] / exp) % 256]++;
    }

    for (int i = 1; i < 256; ++i) {
        count[i] += count[i - 1];
    }

    for (int i = a.size() - 1; i >= 0; --i) {
        output[count[(a[i] / exp) % 256] - 1] = a[i];
        count[(a[i] / exp) % 256]--;
    }

    for (int i = 0; i < a.size(); ++i) {
        a[i] = output[i];
    }
}
    
void radixSort(std::vector<int>& a) {
    if (a.empty())
        return;
    std::vector<unsigned int> tmp;
    for (int x : a) {
        tmp.push_back(static_cast<unsigned int>(x) ^ 0x80000000);
    }
    int exp = 1;
    for (int i = 0; i < 4; ++i, exp <<= 8) {
        countSort(tmp, exp);
    }
    for (int i = 0; i < a.size(); ++i) {
        a[i] = static_cast<int>(tmp[i] ^ 0x80000000);
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
    radixSort(a);
    for (int i : a) {
        std::cout << i << " ";
    }
    return 0;
}
