#include <algorithm>
#include <iostream>
#include <vector>

int n;

void heapfy(std::vector<int>& a, int i) {
    int root = i;
    int l = 2 * i + 1;
    int r = 2 * i + 2;
    if (l < n && a[l] > a[root]) {
        root = l;
    }
    if (r < n && a[r] > a[root]) {
        root = r;
    }
    if (root != i) {
        std::swap(a[i], a[root]);
        heapfy(a, root);
    }
}

void buildMaxHeap(std::vector<int>& a) {
    for (int i = n / 2 - 1; i >= 0; --i) {
        heapfy(a, i);
    }
}

void heapSort(std::vector<int>& a) {
    buildMaxHeap(a);
    for (int i = n - 1; i >= 1; --i) {
        std::swap(a[0], a[i]);
        --n;
        heapfy(a, 0);
    }
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::cin >> n;
    std::vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> a[i];
    }
    heapSort(a);
    for (int i : a) {
        std::cout << i << " ";
    }
}
