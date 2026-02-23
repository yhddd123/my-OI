#include <bits/stdc++.h>

using namespace std;

const int N = 2e5 + 5;

int n, in[N], fa[N], L[N], R[N];

int find(int x) {
    return (fa[x] == x ? x : fa[x] = find(fa[x]));
}

int mn[N], mx[N], is_l[N], is_r[N];

signed main() {
    scanf("%d", &n);
    iota(fa + 1, fa + n + 1, 1);
    iota(L + 1, L + n + 1, 1), iota(R + 1, R + n + 1, 1);
    for (int i = 1; i <= n; ++i) mn[i] = mx[i] = i, is_l[i] = is_r[i] = 1;
    for (int i = 1, x, y; i < n; ++i) {
        scanf("%d%d", &x, &y);
        if (in[y]++) return 0 & puts("Bad oriented forest");
        assert(find(y) == y);
        if (find(x) == find(y)) return 0 & puts("Bad oriented forest");
        if (R[find(x)] + 1 != L[find(y)] && L[find(x)] - 1 != R[find(y)]) {
            return 0 & printf("Bad segment at %d\n", find(x));
        }
        if (R[find(x)] + 1 == L[find(y)]) {
            if (!is_r[x]) return 0 & printf("Bad segment at %d\n", x);
        }
        if (L[find(x)] - 1 == R[find(y)]) {
            if (!is_l[x]) return 0 & printf("Bad segment at %d\n", x);
        }
        if (y > mx[x]) {
            if (mx[x] != x) {
                int t = mx[x];
                while (is_r[t]) is_r[t] = 0, t = mx[t];
            }
            mx[x] = y;
        } else {
            int t = y;
            while (is_r[t]) is_r[t] = 0, t = mx[t];
        }
        if (y < mn[x]) {
            if (mn[x] != x) {
                int t = mn[x];
                while (is_l[t]) is_l[t] = 0, t = mn[t];
            }
            mn[x] = y;
        } else {
            int t = y;
            while (is_l[t]) is_l[t] = 0, t = mn[t];
        }
        L[find(x)] = min(L[find(x)], L[find(y)]), R[find(x)] = max(R[find(x)], R[find(y)]);
        fa[find(y)] = find(x);
        puts("Good"), fflush(stdout);
    }
    return 0;
}