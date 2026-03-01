#include <bits/stdc++.h>
#define pb emplace_back
#define fst first
#define scd second
#define mkp make_pair
#define uint unsigned
#define mems(a, x) memset((a), (x), sizeof(a))

using namespace std;
typedef long long ll;
typedef double db;
typedef unsigned long long ull;
typedef long double ldb;
typedef pair<int, int> pii;

mt19937_64 rnd(chrono::steady_clock::now().time_since_epoch().count());

inline ll get(ll l, ll r) {
    return l + rnd() % (r - l + 1);
}

void solve() {
    int T = 10000;
    printf("%d\n", T);
    while (T--) {
        int n = get(1, 9), m = get(1, 9), k = get(1, 9);
        if (n > m) {
            swap(n, m);
        }
        if (n > k) {
            swap(n, k);
        }
        if (m > k) {
            swap(m, k);
        }
        printf("%d %d %d\n", n, m, k);
		int kk=min(k,4);
        for (int i = 1; i <= n; ++i) {
            printf("%lld%c", get(1, kk), " \n"[i == n]);
        }
        for (int i = 1; i <= m; ++i) {
            printf("%lld%c", get(1, kk), " \n"[i == m]);
        }
        for (int i = 1; i <= k; ++i) {
            printf("%lld%c", get(1, kk), " \n"[i == k]);
        }
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