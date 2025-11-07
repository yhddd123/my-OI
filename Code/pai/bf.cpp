#include <bits/stdc++.h>
#define pb emplace_back
#define fst first
#define scd second
#define mkp make_pair
#define mems(a, x) memset((a), (x), sizeof(a))

using namespace std;
using ll = long long;
using ull = unsigned long long;
using db = double;
using ldb = long double;
using pii = pair<int, int>;
using pll = pair<ll, ll>;

const int maxn = 400100;

int n, m, a[maxn], b[maxn];
bool f[(1 << 15) + 50];

inline int work() {
    for (int i = 0; i < (1 << n); ++i) {
        f[i] = 0;
    }
    f[(1 << n) - 1] = 1;
    int mn = n;
    for (int S = (1 << n) - 1; S; --S) {
        if (f[S]) {
            mn = min(mn, __builtin_popcount(S));
        } else {
            continue;
        }
        for (int i = 0; i < n; ++i) {
            if (S & (1 << i)) {
                for (int j = 0; j < n; ++j) {
                    if (i == j || !(S & (1 << j))) {
                        continue;
                    }
                    if (a[i] >= b[j]) {
                        f[S ^ (1 << j)] = 1;
                    }
                }
            }
        }
    }
    return mn;
}

void solve() {
    scanf("%d%d", &n, &m);
    for (int i = 0; i < n; ++i) {
        scanf("%d%d", &a[i], &b[i]);
    }
    printf("%d\n", work());
    while (m--) {
        int x, y, z;
        scanf("%d%d%d", &x, &y, &z);
        --x;
        a[x] = y;
        b[x] = z;
        printf("%d\n", work());
    }
}

int main() {
    int T = 1;
    // scanf("%d", &T);
    while (T--) {
        solve();
    }
    return 0;
}
