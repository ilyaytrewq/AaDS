

#include <cstdint>
#include <iostream>
#include <random>
#include <string>
#include <vector>

std::vector<std::vector<unsigned long long>> read(int n, int words) {
    std::vector<std::vector<unsigned long long>> m(n, std::vector<unsigned long long>(words, 0));
    for (int i = 0; i < n; ++i) {
        std::string s;
        std::cin >> s;
        int bit = 0;
        for (char c : s) {
            int v;
            if ('0' <= c && c <= '9')
                v = c - '0';
            else if ('A' <= c && c <= 'F')
                v = 10 + (c - 'A');
            else
                v = 10 + (c - 'a');
            for (int k = 3; k >= 0 && bit < n; --k, ++bit) {
                if (v & (1 << k)) {
                    int w = bit / 64;
                    int b = bit % 64;
                    m[i][w] |= (1ull << b);
                }
            }
            if (bit >= n)
                break;
        }
    }
    return m;
}

inline int parity_row(const std::vector<unsigned long long>& row,
                      const std::vector<unsigned long long>& vec, int words) {
    int p = 0;
    for (int i = 0; i < words; ++i) {
        unsigned long long x = row[i] & vec[i];
        p ^= (__builtin_popcountll(x) & 1);
    }
    return p;
}

void mult(const std::vector<std::vector<unsigned long long>>& M,
                 const std::vector<unsigned long long>& v, std::vector<unsigned long long>& res,
                 int n, int words) {
    std::fill(res.begin(), res.end(), 0);
    for (int i = 0; i < n; ++i) {
        int p = parity_row(M[i], v, words);
        if (p) {
            int w = i / 64;
            int b = i % 64;
            res[w] |= (1ull << b);
        }
    }
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n;
    std::cin >> n;

    int words = (n + 63) / 64;

    auto A = read(n, words);
    auto B = read(n, words);
    auto C = read(n, words);

    std::mt19937_64 rng(712367);

    std::vector<unsigned long long> r(words), Br(words), Cr(words), ABr(words);

    int cnt = 50;

    for (int it = 0; it < cnt; ++it) {
        for (int i = 0; i < words; ++i) {
            r[i] = rng();
        }

        mult(B, r, Br, n, words);
        mult(C, r, Cr, n, words);
        mult(A, Br, ABr, n, words);

        bool ok = true;
        for (int i = 0; i < words; ++i) {
            if (ABr[i] != Cr[i]) {
                ok = false;
                break;
            }
        }
        if (!ok) {
            std::cout << "NO";
            return 0;
        }
    }

    std::cout << "YES";
    return 0;
}
