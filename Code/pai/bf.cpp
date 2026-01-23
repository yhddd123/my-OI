#include <bits/stdc++.h>
#define pb emplace_back
#define fst first
#define scd second
#define mkp make_pair
#define mems(a, x) memset((a), (x), sizeof(a))

using namespace std;
typedef long long ll;
typedef double db;
typedef unsigned long long ull;
typedef long double ldb;
typedef pair<ll, ll> pii;

namespace IO {
	const int maxn = 1 << 20;
	
	char ibuf[maxn], *iS, *iT, obuf[maxn], *oS = obuf;

	inline char gc() {
		return (iS == iT ? iT = (iS = ibuf) + fread(ibuf, 1, maxn, stdin), (iS == iT ? EOF : *iS++) : *iS++);
	}

	template<typename T = int>
	inline T read() {
		char c = gc();
		T x = 0;
		bool f = 0;
		while (c < '0' || c > '9') {
			f |= (c == '-');
			c = gc();
		}
		while (c >= '0' && c <= '9') {
			x = (x << 1) + (x << 3) + (c ^ 48);
			c = gc();
		}
		return f ? ~(x - 1) : x;
	}
	
	inline int reads(char *s) {
		char c = gc();
		int len = 0;
		while (isspace(c)) {
			c = gc();
		}
		while (!isspace(c) && c != -1) {
			s[len++] = c;
			c = gc();
		}
		return len;
	}

	inline void flush() {
		fwrite(obuf, 1, oS - obuf, stdout);
		oS = obuf;
	}
	
	struct Flusher {
		~Flusher() {
			flush();
		}
	} AutoFlush;

	inline void pc(char ch) {
		if (oS == obuf + maxn) {
			flush();
		}
		*oS++ = ch;
	}

	template<typename T>
	inline void write(T x) {
		static char stk[64], *tp = stk;
		if (x < 0) {
			x = ~(x - 1);
			pc('-');
		}
		do {
			*tp++ = x % 10;
			x /= 10;
		} while (x);
		while (tp != stk) {
			pc((*--tp) | 48);
		}
	}
	
	template<typename T>
	inline void writesp(T x) {
		write(x);
		pc(' ');
	}
	
	template<typename T>
	inline void writeln(T x) {
		write(x);
		pc('\n');
	}
}

using IO::read;
using IO::reads;
using IO::write;
using IO::pc;
using IO::writesp;
using IO::writeln;

const int maxn = 300100;
const int logn = 20;

int n, m, B;

struct graph {
	int hd[maxn], len, to[maxn << 1], nxt[maxn << 1];
	ll dis[maxn << 1];
	
	inline void add_edge(int u, int v, ll d) {
		to[++len] = v;
		dis[len] = d;
		nxt[len] = hd[u];
		hd[u] = len;
	}
} G1, G2;

int st[logn][maxn], dfn[maxn], tim;
ll dep[maxn];

inline int get(int i, int j) {
	return dfn[i] < dfn[j] ? i : j;
}

inline int qlca(int x, int y) {
	if (x == y) {
		return x;
	}
	x = dfn[x];
	y = dfn[y];
	if (x > y) {
		swap(x, y);
	}
	++x;
	int k = __lg(y - x + 1);
	return get(st[k][x], st[k][y - (1 << k) + 1]);
}

inline ll qdis(int x, int y) {
	return dep[x] + dep[y] - dep[qlca(x, y)] * 2;
}

void dfs(int u, int t) {
	dfn[u] = ++tim;
	st[0][tim] = t;
	for (int i = G1.hd[u]; i; i = G1.nxt[i]) {
		int v = G1.to[i], d = G1.dis[i];
		if (v == t) {
			continue;
		}
		dep[v] = dep[u] + d;
		dfs(v, u);
	}
}

int bel[maxn], L[maxn], R[maxn];

struct node {
	int x, y;
	vector<int> vc;
} f[logn][3030];

int bot[maxn], son[maxn], tot;
ll len[maxn];
pii p[maxn];

void dfs2(int u, int fa) {
	son[u] = 0;
	bot[u] = u;
	ll mx = 0;
	for (int i = G2.hd[u]; i; i = G2.nxt[i]) {
		int v = G2.to[i];
		ll d = G2.dis[i];
		if (v == fa) {
			continue;
		}
		dfs2(v, u);
		if (len[v] + d > mx) {
			mx = len[v] + d;
			son[u] = v;
		}
	}
	len[u] = mx;
	if (son[u]) {
		bot[u] = bot[son[u]];
	}
	for (int i = G2.hd[u]; i; i = G2.nxt[i]) {
		int v = G2.to[i];
		ll d = G2.dis[i];
		if (v == fa || v == son[u]) {
			continue;
		}
		p[++tot] = mkp(len[v] + d, bot[v]);
	}
}

inline node operator + (const node &a, const node &b) {
	int c[4] = {a.x, a.y, b.x, b.y};
	ll mx = -1;
	node res;
	for (int i = 0; i < 4; ++i) {
		for (int j = i + 1; j < 4; ++j) {
			int x = c[i], y = c[j];
			ll d = qdis(x, y);
			if (d > mx) {
				mx = d;
				res.x = x;
				res.y = y;
			}
		}
	}
	vector<int> pt = a.vc;
	for (int u : b.vc) {
		pt.pb(u);
	}
	pt.pb(res.x);
	pt.pb(res.y);
	sort(pt.begin(), pt.end(), [&](const int &x, const int &y) {
		return dfn[x] < dfn[y];
	});
	int len = (int)pt.size();
	for (int i = 1; i < len; ++i) {
		pt.pb(qlca(pt[i - 1], pt[i]));
	}
	sort(pt.begin(), pt.end(), [&](const int &x, const int &y) {
		return dfn[x] < dfn[y];
	});
	pt.erase(unique(pt.begin(), pt.end()), pt.end());
	for (int i = 1; i < (int)pt.size(); ++i) {
		int u = qlca(pt[i - 1], pt[i]);
		G2.add_edge(u, pt[i], dep[pt[i]] - dep[u]);
		G2.add_edge(pt[i], u, dep[pt[i]] - dep[u]);
	}
	tot = 0;
	dfs2(res.x, -1);
	p[++tot] = mkp(::len[res.x], bot[res.x]);
	nth_element(p + 1, p + min(tot, 100), p + tot + 1, greater<pii>());
	res.vc.pb(res.x);
	for (int i = 1; i <= min(tot, 100); ++i) {
		res.vc.pb(p[i].scd);
	}
	G2.len = 0;
	for (int u : pt) {
		G2.hd[u] = 0;
	}
	return res;
}

inline node brute(int l, int r) {
	int x = l, y = l;
	ll mx = 0;
	for (int i = l + 1; i <= r; ++i) {
		ll xx = qdis(x, i), yy = qdis(y, i);
		if (xx == max({xx, yy, mx})) {
			y = i;
		} else if (yy == max({xx, yy, mx})) {
			x = i;
		}
		mx = max({xx, yy, mx});
	}
	node res;
	res.x = x;
	res.y = y;
	for (int i = l; i <= r; ++i) {
		res.vc.pb(i);
	}
	return res;
}

inline node query(int l, int r) {
	int k = __lg(r - l + 1);
	return f[k][l] + f[k][r - (1 << k) + 1];
}

void solve() {
	n = read();
	for (int i = 1; i < n; ++i) {
		int u = read();
		int v = read();
		int d = read();
		G1.add_edge(u, v, d);
		G1.add_edge(v, u, d);
	}
	dfs(1, 0);
	for (int j = 1; (1 << j) <= n; ++j) {
		for (int i = 1; i + (1 << j) - 1 <= n; ++i) {
			st[j][i] = get(st[j - 1][i], st[j - 1][i + (1 << (j - 1))]);
		}
	}
	B = min(n, 100);
	for (int i = 1; i <= n; ++i) {
		bel[i] = (i - 1) / B + 1;
		if (!L[bel[i]]) {
			L[bel[i]] = i;
		}
		R[bel[i]] = i;
	}
	for (int k = 1; k <= bel[n]; ++k) {
		f[0][k] = brute(L[k], R[k]);
	}
	for (int j = 1; (1 << j) <= bel[n]; ++j) {
		for (int i = 1; i + (1 << j) - 1 <= bel[n]; ++i) {
			f[j][i] = f[j - 1][i] + f[j - 1][i + (1 << (j - 1))];
		}
	}
	m = read();
	while (m--) {
		int l = read();
		int r = read();
		int k = read();
		node res;
		if (bel[l] == bel[r]) {
			res = brute(l, r);
		} else {
			res = brute(l, R[bel[l]]);
			if (bel[l] + 1 < bel[r]) {
				res = res + query(bel[l] + 1, bel[r] - 1);
			}
			res = res + brute(L[bel[r]], r);
		}
		auto pt = res.vc;
		sort(pt.begin(), pt.end(), [&](const int &x, const int &y) {
			return dfn[x] < dfn[y];
		});
		int len = (int)pt.size();
		for (int i = 1; i < len; ++i) {
			pt.pb(qlca(pt[i - 1], pt[i]));
		}
		sort(pt.begin(), pt.end(), [&](const int &x, const int &y) {
			return dfn[x] < dfn[y];
		});
		pt.erase(unique(pt.begin(), pt.end()), pt.end());
		for (int i = 1; i < (int)pt.size(); ++i) {
			int u = qlca(pt[i - 1], pt[i]);
			G2.add_edge(u, pt[i], dep[pt[i]] - dep[u]);
			G2.add_edge(pt[i], u, dep[pt[i]] - dep[u]);
		}
		tot = 0;
		dfs2(res.x, -1);
		p[++tot] = mkp(::len[res.x], bot[res.x]);
		nth_element(p + 1, p + min(tot, k - 1), p + tot + 1, greater<pii>());
		ll ans = 0;
		for (int i = 1; i <= min(tot, k - 1); ++i) {
			ans += p[i].fst;
		}
		writeln(ans);
		G2.len = 0;
		for (int u : pt) {
			G2.hd[u] = 0;
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
