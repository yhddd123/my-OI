// Problem: P9623 [ICPC2020 Nanjing R] Baby's First Suffix Array Problem
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P9623
// Memory Limit: 256 MB
// Time Limit: 5000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

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
typedef pair<ll, ll> pii;

const int maxn = 100100;
const int logn = 20;

int n, m;
char s[maxn];

int sa[maxn], rk[maxn], id[maxn], cnt[maxn], old[maxn], h[maxn], st[logn][maxn];

inline int qmin(int l, int r) {
	int k = __lg(r - l + 1);
	return min(st[k][l], st[k][r - (1 << k) + 1]);
}

inline void build() {
	int m = max(n, 127);
	for (int i = 1; i <= m * 2; ++i) {
		sa[i] = rk[i] = id[i] = cnt[i] = old[i] = h[i] = 0;
	}
	for (int i = 1; i <= n; ++i) {
		rk[i] = s[i];
		++cnt[rk[i]];
	}
	for (int i = 1; i <= m; ++i) {
		cnt[i] += cnt[i - 1];
	}
	for (int i = n; i; --i) {
		sa[cnt[rk[i]]--] = i;
	}
	for (int w = 1; w < n; w <<= 1) {
		int tot = 0;
		for (int i = n - w + 1; i <= n; ++i) {
			id[++tot] = i;
		}
		for (int i = 1; i <= n; ++i) {
			if (sa[i] > w) {
				id[++tot] = sa[i] - w;
			}
		}
		for (int i = 1; i <= m; ++i) {
			cnt[i] = 0;
		}
		for (int i = 1; i <= n; ++i) {
			old[i] = rk[i];
			++cnt[rk[id[i]]];
		}
		for (int i = 1; i <= m; ++i) {
			cnt[i] += cnt[i - 1];
		}
		for (int i = n; i; --i) {
			sa[cnt[rk[id[i]]]--] = id[i];
		}
		for (int i = 1, p = 0; i <= n; ++i) {
			if (old[sa[i]] == old[sa[i - 1]] && old[sa[i] + w] == old[sa[i - 1] + w]) {
				rk[sa[i]] = p;
			} else {
				rk[sa[i]] = ++p;
			}
		}
	}
	h[1] = 0;
	for (int i = 1, k = 0; i <= n; ++i) {
		if (rk[i] == 1) {
			continue;
		}
		if (k) {
			--k;
		}
		while (i + k <= n && sa[rk[i] - 1] + k <= n && s[i + k] == s[sa[rk[i] - 1] + k]) {
			++k;
		}
		h[rk[i]] = k;
	}
	for (int i = 1; i <= n; ++i) {
		st[0][i] = h[i];
	}
	for (int j = 1; (1 << j) <= n; ++j) {
		for (int i = 1; i + (1 << j) - 1 <= n; ++i) {
			st[j][i] = min(st[j - 1][i], st[j - 1][i + (1 << (j - 1))]);
		}
	}
}

struct node {
	int l, r, o, i;
	node(int a = 0, int b = 0, int c = 0, int d = 0) : l(a), r(b), o(c), i(d) {}
};

vector<node> md[maxn];
vector<int> vc[maxn];
int ans[maxn];

struct que {
	int l, r, k;
} a[maxn];

namespace BIT {
	int c[maxn];
	
	inline void init() {
		for (int i = 0; i <= n; ++i) {
			c[i] = 0;
		}
	}
	
	inline void update(int x, int d) {
		for (int i = x; i <= n; i += (i & (-i))) {
			c[i] += d;
		}
	}
	
	inline int query(int x) {
		int res = 0;
		for (int i = x; i; i -= (i & (-i))) {
			res += c[i];
		}
		return res;
	}
	
	inline int query(int l, int r) {
		return l <= r ? query(r) - query(l - 1) : 0;
	}
}

int f[maxn], g[maxn];

struct wwh {
	int x, i;
	wwh(int a = 0, int b = 0) : x(a), i(b) {}
} b[maxn];

void dfs(int l, int r) {
	if (l == r) {
		return;
	}
	int mid = (l + r) >> 1;
	dfs(l, mid);
	dfs(mid + 1, r);
	f[mid + 1] = g[mid] = 1e9;
	for (int i = mid; i >= l; --i) {
		f[i] = min(f[i + 1], h[i]);
	}
	for (int i = mid + 1; i <= r; ++i) {
		g[i] = min(g[i - 1], h[i]);
	}
	int tot = 0;
	for (int i = mid + 1; i <= r; ++i) {
		b[++tot] = wwh(g[i] + sa[i], -i);
	}
	for (int i = l; i <= mid; ++i) {
		for (int j : vc[i]) {
			b[++tot] = wwh(a[j].r + 1, j);
		}
	}
	sort(b + 1, b + tot + 1, [&](const wwh &a, const wwh &b) {
		return a.x > b.x || (a.x == b.x && a.i < b.i);
	});
	for (int i = 1; i <= tot; ++i) {
		int j = b[i].i;
		if (j > 0) {
			ans[j] += BIT::query(max(a[j].r + 1 - f[rk[a[j].k] + 1], a[j].k + 1), a[j].r);
		} else {
			j = -j;
			BIT::update(sa[j], 1);
		}
	}
	for (int i = 1; i <= tot; ++i) {
		int j = b[i].i;
		if (j < 0) {
			j = -j;
			BIT::update(sa[j], -1);
		}
	}
}

void solve() {
	scanf("%d%d%s", &n, &m, s + 1);
	build();
	for (int i = 1; i <= n; ++i) {
		vector<node>().swap(md[i]);
		vector<int>().swap(vc[i]);
	}
	for (int i = 1; i <= m; ++i) {
		ans[i] = 1;
		scanf("%d%d%d", &a[i].l, &a[i].r, &a[i].k);
		md[rk[a[i].k] - 1].pb(a[i].l, a[i].r, 1, i);
		vc[rk[a[i].k]].pb(i);
		int l = 1, r = rk[a[i].k] - 1, p = -1;
		while (l <= r) {
			int mid = (l + r) >> 1;
			if (qmin(mid + 1, rk[a[i].k]) >= a[i].r - a[i].k + 1) {
				p = mid;
				r = mid - 1;
			} else {
				l = mid + 1;
			}
		}
		if (p != -1) {
			md[p - 1].pb(a[i].l, a[i].k - 1, 1, i);
			md[rk[a[i].k] - 1].pb(a[i].l, a[i].k - 1, -1, i);
		}
	}
	BIT::init();
	dfs(1, n);
	BIT::init();
	for (int i = 1; i <= n; ++i) {
		BIT::update(sa[i], 1);
		for (node u : md[i]) {
			if (u.l > u.r) {
				continue;
			}
			ans[u.i] += u.o * BIT::query(u.l, u.r);
		}
	}
	for (int i = 1; i <= m; ++i) {
		printf("%d\n", ans[i]);
	}
}

int main() {
	int T = 1;
	scanf("%d", &T);
	while (T--) {
		solve();
	}
	return 0;
}
