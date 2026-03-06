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
		while (!isspace(c) && c != EOF) {
			s[len++] = c;
			c = gc();
		}
		s[len] = '\0';
		return len;
	}
	
	inline string reads() {
		char c = gc();
		string s;
		while (isspace(c)) {
			c = gc();
		}
		while (!isspace(c) && c != EOF) {
			s += c;
			c = gc();
		}
		return s;
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
	
	inline void write(char *s) {
		for (int i = 0; s[i]; ++i) {
			pc(s[i]);
		}
	}
	
	inline void write(const char *s) {
		for (int i = 0; s[i]; ++i) {
			pc(s[i]);
		}
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

const int maxn = 100100;
const int logn = 18;
const int inf = 0x3f3f3f3f;

int n, m, ans[maxn], pt[maxn << 1];
pii b[maxn];

struct node {
	int o, x;
} a[maxn];

struct graph {
	int hd[maxn], to[maxn << 1], nxt[maxn << 1], len;
	
	inline void add_edge(int u, int v) {
		to[++len] = v;
		nxt[len] = hd[u];
		hd[u] = len;
	}
} G, T;

int dfn[maxn], ed[maxn], tim, fa[maxn], st[logn][maxn];

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

void dfs(int u, int t) {
	dfn[u] = ++tim;
	fa[u] = st[0][tim] = t;
	for (int i = G.hd[u]; i; i = G.nxt[i]) {
		int v = G.to[i];
		if (v == t) {
			continue;
		}
		dfs(v, u);
	}
	ed[u] = tim;
}

namespace ST1 {
	int a[maxn << 2], N;
	
	inline void init() {
		N = (1 << (__lg(n + 1) + 1));
	}
	
	inline void update(int x, int y) {
		a[x += N] = y;
		while (x >>= 1) {
			a[x] = max(a[x << 1], a[x << 1 | 1]);
		}
	}
	
	inline int query(int l, int r) {
		int res = 0;
		for (l += N - 1, r += N + 1; l ^ r ^ 1; l >>= 1, r >>= 1) {
			if (!(l & 1)) {
				res = max(res, a[l ^ 1]);
			}
			if (r & 1) {
				res = max(res, a[r ^ 1]);
			}
		}
		return res;
	}
}

namespace ST2 {
	int a[maxn << 2], N;
	
	inline void init() {
		N = (1 << (__lg(n + 1) + 1));
		mems(a, 0x3f);
	}
	
	inline void update(int x, int y) {
		a[x += N] = y;
		while (x >>= 1) {
			a[x] = min(a[x << 1], a[x << 1 | 1]);
		}
	}
	
	inline int query(int l, int r) {
		int res = inf;
		for (l += N - 1, r += N + 1; l ^ r ^ 1; l >>= 1, r >>= 1) {
			if (!(l & 1)) {
				res = min(res, a[l ^ 1]);
			}
			if (r & 1) {
				res = min(res, a[r ^ 1]);
			}
		}
		return res;
	}
}

namespace SGT {
	pii a[maxn << 2];
	int tag[maxn << 2];
	
	inline pii get(pii a, pii b) {
		return (a.fst < b.fst || (a.fst == b.fst && a.scd > b.scd)) ? a : b;
	}
	
	inline void pushup(int x) {
		a[x] = get(a[x << 1], a[x << 1 | 1]);
	}
	
	inline void pushtag(int x, int y) {
		a[x].fst += y;
		tag[x] += y;
	}
	
	inline void pushdown(int x) {
		if (!tag[x]) {
			return;
		}
		pushtag(x << 1, tag[x]);
		pushtag(x << 1 | 1, tag[x]);
		tag[x] = 0;
	}
	
	void build(int rt, int l, int r) {
		tag[rt] = 0;
		if (l == r) {
			a[rt] = pii(0, l);
			return;
		}
		int mid = (l + r) >> 1;
		build(rt << 1, l, mid);
		build(rt << 1 | 1, mid + 1, r);
		pushup(rt);
	}
	
	void update(int rt, int l, int r, int ql, int qr, int x) {
		if (ql <= l && r <= qr) {
			pushtag(rt, x);
			return;
		}
		pushdown(rt);
		int mid = (l + r) >> 1;
		if (ql <= mid) {
			update(rt << 1, l, mid, ql, qr, x);
		}
		if (qr > mid) {
			update(rt << 1 | 1, mid + 1, r, ql, qr, x);
		}
		pushup(rt);
	}
	
	void modify(int rt, int l, int r, int x) {
		if (l == r) {
			a[rt].fst = inf;
			return;
		}
		pushdown(rt);
		int mid = (l + r) >> 1;
		(x <= mid) ? modify(rt << 1, l, mid, x) : modify(rt << 1 | 1, mid + 1, r, x);
		pushup(rt);
	}
}

bool vis[maxn], mk[maxn];
vector<pii> f[maxn];

struct line {
	int l, r, x;
	line(int _l = 0, int _r = 0, int _x = 0) : l(_l), r(_r), x(_x) {}
};

vector<line> vc[maxn];

void conq(int l, int r) {
	if (l == r) {
		return;
	}
	int mid = (l + r) >> 1;
	conq(l, mid);
	conq(mid + 1, r);
	for (int i = l; i <= r; ++i) {
		mk[i] = 0;
		vector<pii>().swap(f[i]);
	}
	int tot = 0;
	for (int i = l; i <= r; ++i) {
		pt[++tot] = a[i].x;
	}
	sort(pt + 1, pt + tot + 1, [&](const int &i, const int &j) {
		return dfn[i] < dfn[j];
	});
	int t = tot;
	for (int i = 1; i < t; ++i) {
		pt[++tot] = qlca(pt[i], pt[i + 1]);
	}
	sort(pt + 1, pt + tot + 1, [&](const int &i, const int &j) {
		return dfn[i] < dfn[j];
	});
	tot = unique(pt + 1, pt + tot + 1) - pt - 1;
	for (int i = 2; i <= tot; ++i) {
		T.add_edge(qlca(pt[i - 1], pt[i]), pt[i]);
	}
	for (int i = mid; i >= l; --i) {
		if (a[i].o) {
			if (vis[a[i].x]) {
				mk[i] = 1;
			}
			vis[a[i].x] = 1;
		}
	}
	for (int i = l; i <= mid; ++i) {
		if (a[i].o) {
			vis[a[i].x] = 0;
		}
	}
	for (int i = mid + 1; i <= r; ++i) {
		if (a[i].o) {
			if (vis[a[i].x]) {
				mk[i] = 1;
			}
			vis[a[i].x] = 1;
		}
	}
	for (int i = mid + 1; i <= r; ++i) {
		if (a[i].o) {
			vis[a[i].x] = 0;
		}
	}
	for (int i = l; i <= r; ++i) {
		if (mk[i]) {
			continue;
		}
		int x = a[i].x;
		if (a[i].o) {
			for (int _ = T.hd[x]; _; _ = T.nxt[_]) {
				int v = T.to[_];
				f[i].pb(ST1::query(dfn[v], ed[v]), 0);
			}
			f[i].pb(ST1::query(dfn[x], dfn[x]), 0);
			f[i].pb(ST1::query(dfn[x], dfn[x]), 0);
			f[i].pb(max(ST1::query(1, dfn[x] - 1), ST1::query(ed[x] + 1, n)), 0);
		} else {
			ST1::update(dfn[x], i);
		}
	}
	for (int i = r; i >= l; --i) {
		if (mk[i]) {
			continue;
		}
		int x = a[i].x;
		if (a[i].o) {
			int k = 0;
			for (int _ = T.hd[x]; _; _ = T.nxt[_]) {
				int v = T.to[_];
				f[i][k++].scd = ST2::query(dfn[v], ed[v]);
			}
			f[i][k++].scd = ST2::query(dfn[x], dfn[x]);
			f[i][k++].scd = ST2::query(dfn[x], dfn[x]);
			f[i][k++].scd = min(ST2::query(1, dfn[x] - 1), ST2::query(ed[x] + 1, n));
		} else {
			ST2::update(dfn[x], i);
		}
	}
	for (int i = l; i <= r; ++i) {
		if (!a[i].o) {
			int x = a[i].x;
			ST1::update(dfn[x], 0);
			ST2::update(dfn[x], inf);
		}
	}
	auto add = [&](int xl, int xr, int yl, int yr, int x) -> void {
		xl = max(xl, l);
		xr = min(xr, mid);
		yl = max(yl, mid + 1);
		yr = min(yr, r);
		if (xl > xr || yl > yr) {
			return;
		}
		vc[xl].pb(yl, yr, x);
		vc[xr + 1].pb(yl, yr, -x);
	};
	for (int i = l - 1; i <= mid + 1; ++i) {
		vector<line>().swap(vc[i]);
	}
	for (int i = l; i <= mid; ++i) {
		if (!a[i].o || mk[i]) {
			continue;
		}
		sort(f[i].begin(), f[i].end(), greater<>());
		int mn = inf, smn = inf;
		for (pii p : f[i]) {
			if (p.scd < mn) {
				smn = mn;
				mn = p.scd;
			} else if (p.scd < smn) {
				smn = p.scd;
			}
		}
		add(f[i][0].fst + 1, i, mid + 1, smn - 1, 1);
		add(f[i][1].fst + 1, f[i][0].fst, mid + 1, (mn == f[i][0].scd ? smn : mn) - 1, 1);
	}
	for (int i = mid + 1; i <= r; ++i) {
		if (!a[i].o || mk[i]) {
			continue;
		}
		sort(f[i].begin(), f[i].end(), greater<>());
		int mn = inf, smn = inf;
		for (pii p : f[i]) {
			if (p.scd < mn) {
				smn = mn;
				mn = p.scd;
			} else if (p.scd < smn) {
				smn = p.scd;
			}
		}
		add(f[i][0].fst + 1, mid, i, smn - 1, 1);
		add(f[i][1].fst + 1, f[i][0].fst, i, (mn == f[i][0].scd ? smn : mn) - 1, 1);
	}
	SGT::build(1, mid + 1, r);
	for (int i = l; i <= mid; ++i) {
		for (line u : vc[i]) {
			SGT::update(1, mid + 1, r, u.l, u.r, u.x);
		}
		if (!SGT::a[1].fst) {
			ans[i] = max(ans[i], SGT::a[1].scd);
		}
	}
	T.len = 0;
	for (int i = 1; i <= tot; ++i) {
		T.hd[pt[i]] = 0;
	}
}

void solve() {
	n = read();
	for (int _ = 1; _ < n; ++_) {
		int u = read();
		int v = read();
		G.add_edge(u, v);
		G.add_edge(v, u);
	}
	m = read();
	for (int i = 1; i <= m; ++i) {
		char o[9];
		reads(o);
		a[i].x = read();
		a[i].o = (o[0] == 'b');
		ans[i] = (a[i].o ? i - 1 : i);
	}
	dfs(1, 0);
	for (int j = 1; (1 << j) <= n; ++j) {
		for (int i = 1; i + (1 << j) - 1 <= n; ++i) {
			st[j][i] = get(st[j - 1][i], st[j - 1][i + (1 << (j - 1))]);
		}
	}
	ST1::init();
	ST2::init();
	conq(1, m);
	for (int i = 1; i <= m; ++i) {
		writeln(ans[i] - i + 1);
	}
}

int main() {
	// freopen("excite.in", "r", stdin);
	// freopen("excite.out", "w", stdout);
	int T = 1;
	// scanf("%d", &T);
	while (T--) {
		solve();
	}
	return 0;
}
