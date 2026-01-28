

#include <cstdio>
#define ull unsigned long long

using namespace std;

int N;
ull A[49][49];
int n;
ull f[21][1048579];
int id[1048579];
ull g[2][1048579][41];

int main () {
    scanf("%d", &N);
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++) scanf("%llu", &A[i][j]);
    int t = (N >> 1);
    if (N & 1) N++;
    n = (N >> 1);
    for (int i = 0; i < (1 << n); i++) id[i] = (i & 1) ? id[i >> 1] + 1 : 0;
    f[0][0] = 1;
    int s, p;
    ull v0, v1;
    for (int i = 0; i <= n; i++)
        for (int j = 0; j < (1 << (n - i)); j++) {
            s = ((j << i) ^ ((1 << i) - 1)), p = id[s];
            g[0][s][p << 1] += f[i][s];
            for (int k = (p << 1); k < N; k++) g[1][s][p << 1 | 1] += g[0][s][k];
            for (int k = (p << 1); k < N; k++)
                if (g[0][s][k] || g[1][s][k]) {
                    v0 = g[0][s][k], v1 = g[1][s][k];
                    f[i + 1][s ^ (1 << p)] += v1;
                    f[i][s ^ (1 << p)] += (v0 * A[k][p << 1 | 1]);
                    for (int l = p + 1; l < n; l++)
                        if (!((s >> l) & 1)) {
                            g[0][s ^ (1 << l)][l << 1 | 1] += (v0 * A[k][l << 1]);
                            g[0][s ^ (1 << l)][l << 1] += (v0 * A[k][l << 1 | 1]);
                            g[1][s ^ (1 << l)][l << 1 | 1] += (v1 * A[k][l << 1]);
                            g[1][s ^ (1 << l)][l << 1] += (v1 * A[k][l << 1 | 1]);
                        }
                    g[0][s][k] = g[1][s][k] = 0;
                }
        }
    for (int i = 0; i <= t; i++) printf("%llu ", f[n - i][(1 << n) - 1]);
    puts("");
    return 0;
}
