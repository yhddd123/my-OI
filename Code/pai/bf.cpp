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

const int maxn = 200100;

int A, B, C, a[maxn], b[maxn], c[maxn];

void solve() {
    scanf("%d%d%d", &A, &B, &C);
    for (int i = 1; i <= A; ++i) {
        scanf("%d", &a[i]);
    }
    for (int i = 1; i <= B; ++i) {
        scanf("%d", &b[i]);
    }
    for (int i = 1; i <= C; ++i) {
        scanf("%d", &c[i]);
    }
    sort(c + 1, c + C + 1);
    do {
        bool fl = 0;
        for (int i = 1; i + A - 1 <= C; ++i) {
            bool f = 1;
            for (int j = 0; j < A && f; ++j) {
                f &= (a[j + 1] == c[i + j]);
            }
            if (f) {
                fl = 1;
                break;
            }
        }
        if (!fl) {
            continue;
        }
        fl = 0;
        for (int i = 1; i + B - 1 <= C; ++i) {
            bool f = 1;
            for (int j = 0; j < B && f; ++j) {
                f &= (b[j + 1] == c[i + j]);
            }
            if (f) {
                fl = 1;
                break;
            }
        }
        if (!fl) {
            continue;
        }
        for (int i = 1; i <= C; ++i) {
            printf("%d ", c[i]);
        }
        putchar('\n');
        return;
    } while (next_permutation(c + 1, c + C + 1));
    puts("-1");
}

int main() {
    int T = 1;
    scanf("%d", &T);
    while (T--) {
        solve();
    }
    return 0;
}