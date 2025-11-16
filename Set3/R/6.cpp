#pragma GCC optimize("Ofast,unroll-loops")

#include <algorithm>
#include <chrono>
#include <iostream>
#include <unordered_map>
#include <numeric>
#include <random>
#include <vector>
#include <memory.h>

using namespace std;

int n;
vector<int> cnt_r, cnt_l;

inline int f(const vector<int>& p) {
    const int sz = 2 * n - 1;
    memset(cnt_r.data(), 0, sz * sizeof(int));
    memset(cnt_l.data(), 0, sz * sizeof(int));

    const int shift = n - 1;

    for (int i = 0; i < n; ++i) {
        ++cnt_r[i + p[i]];
        ++cnt_l[i - p[i] + shift];
    }

    int ans = 0;
    for (int i = 0; i < sz; ++i) {
        int c = cnt_r[i];
        ans += (c * (c - 1)) >> 1;
        c = cnt_l[i];
        ans += (c * (c - 1)) >> 1;
    }
    return ans;
}

inline double P(mt19937& rnd) {
    return (double)rnd() / (double)rnd.max();
}

int solve() {
    auto start = chrono::high_resolution_clock::now();
    mt19937 rnd((uint64_t)chrono::steady_clock::now().time_since_epoch().count());

    vector<int> ans(n);
    iota(ans.begin(), ans.end(), 0);

    shuffle(ans.begin(), ans.end(), rnd);
    shuffle(ans.begin(), ans.end(), rnd);

    int best = f(ans);
    double t = 1.0;

    while (true) {
        for (int _ = 0; _ < 100; ++_) {
            int p1 = rnd() % n;
            int p2 = rnd() % n;
            if (p1 == p2) continue;

            swap(ans[p1], ans[p2]);
            int nf = f(ans);

            if (nf < best || exp((double)(best - nf) / t) > P(rnd)) {
                best = nf;
            } else {
                swap(ans[p1], ans[p2]);
            }

            if (best == 0) break;
            t *= 0.99;
        }

        auto cur = chrono::high_resolution_clock::now();
        if (best == 0 ||
            chrono::duration_cast<chrono::milliseconds>(cur - start).count() > 950) {
            break;
        }
    }

    if (best != 0) return 0;

    for (int x : ans) {
        cout << x + 1 << ' ';
    }
    cout << '\n';
    return 1;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    long long tt = 3;
    cin >> n;

    cnt_r.assign(2 * n - 1, 0);
    cnt_l.assign(2 * n - 1, 0);

    while (tt--) {
        if (solve()) return 0;
    }
    return 0;
}
