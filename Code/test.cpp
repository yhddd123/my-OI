#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#define mems(x, v) memset(x, v, sizeof x)
#define mcpy(x, y) memcpy(x, y, sizeof x)
using namespace std;
typedef unsigned int ui;
typedef pair <int, int> pii;
typedef long long ll;
typedef unsigned long long ull;
typedef long double wisdom;

char buf[1 << 21], *p1 = buf, *p2 = buf;
#define getchar() p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, 1 << 21, stdin), p1 == p2) ? EOF : *p1++
inline ui read() {char op = getchar(); ui x = 0; while (op < 48 || op > 57) op = getchar(); while (48 <= op && op <= 57) x = (x << 1) + (x << 3) + (op ^ 48), op = getchar(); return x;}

const int N = 5e5 + 5;
int n, cur; ui a[N], tt[N], X, Y, Z, ans;
struct BIT {
	ui idx[N];
	inline void add(int i, ui k) {for (; i <= cur; i += i & -i) idx[i] += k;}
	inline ui qry(int i) {ui ans = 0; for (; i; i -= i & -i) ans += idx[i]; return ans;}
	inline ui qry(int l, int r) {return qry(r) - qry(l - 1);}
} CL, CR, SL, SR;

#define fi first
#define se second

struct SGT {
	#define ls pos << 1
	#define rs pos << 1 | 1

	pair <ui, ui> tr[N << 2], add[N << 2];
	inline void build() {for (int i = 1; i <= (cur << 1); i++) tr[i].fi = tr[i].se = add[i].fi = add[i].se = 0;}
	inline void up(int pos) {if (pos) tr[pos].fi = tr[ls].fi + tr[rs].fi, tr[pos].se = tr[ls].se + tr[rs].se;}
	inline void dw(int pos) {
		if (add[pos].fi) tr[ls].se += tr[ls].fi * add[pos].fi, add[ls].fi += add[pos].fi, tr[rs].se += tr[rs].fi * add[pos].fi, add[rs].fi += add[pos].fi, add[pos].fi = 0;
		if (add[pos].se) tr[ls].fi += add[pos].se, tr[rs].fi += add[pos].se, add[pos].se = 0;
	}
	void upd(int id, ui x20) {
		int l = id + cur, r = id + cur + 1;
		for (int i = __lg(l); i; i--) dw(l >> i);
		for (int i = __lg(r); i; i--) dw(r >> i);

		for (int u = 0, v = 0; l < r; l >>= 1, r >>= 1) {
			if (l & 1) u = l, tr[l].fi += x20, l++;
			if (r & 1) v = r, r--, tr[r].fi += x20;
			do up(u >>= 1); while (l == r && u);
			do up(v >>= 1); while (l == r && v);
		}
	}
	void mdf(int l, int r, ui x01) {
		if (l > r) return; l += cur, r += cur + 1;
		for (int i = __lg(l); i; i--) dw(l >> i);
		for (int i = __lg(r); i; i--) dw(r >> i);

		for (int u = 0, v = 0; l < r; l >>= 1, r >>= 1) {
			if (l & 1) u = l, tr[l].se += tr[l].fi * x01, add[l].fi += x01, l++;
			if (r & 1) v = r, r--, tr[r].se += tr[r].fi * x01, add[r].fi += x01;
			do up(u >>= 1); while (l == r && u);
			do up(v >>= 1); while (l == r && v);
		}
	}
	ui qry(int l, int r) {
		if (l > r) return 0; l += cur, r += cur + 1;
		for (int i = __lg(l); i; i--) dw(l >> i);
		for (int i = __lg(r); i; i--) dw(r >> i);

		ui ans = 0;
		for (; l < r; l >>= 1, r >>= 1) {
			if (l & 1) ans += tr[l++].se;
			if (r & 1) ans += tr[--r].se;
		}
		return ans;
	}
} F;

#include<ctime>
int main() {
	// freopen("data.txt", "r", stdin);
	double STA=clock();
	n = read(), X = read(), Y = read(), Z = read();
	const ui mXZ = (X < Z ? X : Z);
	const ui mYZ = (Y < Z ? Y : Z);
	for (int i = 1; i <= n; i++) tt[i] = a[i] = read();
	sort(tt + 1, tt + n + 1), cur = unique(tt + 1, tt + n + 1) - tt - 1;
	for (int i = 1; i <= n; i++) a[i] = lower_bound(tt + 1, tt + cur + 1, a[i]) - tt;

	//1.
	F.build();
	for (int i = n; i; i--) {
		int ai = a[i]; ui aval = tt[ai]; ui q = F.qry(1, ai - 1);
		ans += mXZ * aval * q;
		F.mdf(ai, cur, 1); F.upd(ai, 1);
	}
	F.build();
	for (int i = n; i; i--) {
		int ai = a[i]; ui q = F.qry(1, ai - 1);
		ans -= mXZ * q;
		F.mdf(ai, cur, 1); F.upd(ai, tt[ai]);
	}

	//2.
	F.build();
	for (int i = n; i; i--) {
		int ai = a[i]; ui q = F.qry(ai, cur); ui aval = tt[ai];
		ans += mYZ * q;
		F.mdf(1, ai - 1, aval); F.upd(ai, 1);
	}
	F.build();
	for (int i = n; i; i--) {
		int ai = a[i]; ui q = F.qry(ai, cur);
		ans -= mYZ * q;
		F.mdf(1, ai - 1, 1); F.upd(ai, tt[ai]);
	}

	//3.
	F.build();
	const ui coefA = (Y <= Z ? (X + Y >= Z ? Z : X + Y) : Z);
	for (int k = 1; k <= n; k++) {
		int ai = a[k]; ui aval = tt[ai]; ui q = F.qry(ai + 1, cur);
		ans -= coefA * aval * q;
		F.mdf(1, ai, 1); F.upd(ai, 1);
	}
	if (Y <= Z) {
		F.build();
		const ui coefB = (X + Y >= Z ? Z - Y : X);
		for (int k = 1; k <= n; k++) {
			int ai = a[k]; ui q = F.qry(ai + 1, cur);
			ans += coefB * q;
			F.mdf(1, ai, 1); F.upd(ai, tt[ai]);
		}
	}
	F.build();
	const ui coefC = (Y <= Z ? Y : Z);
	for (int k = 1; k <= n; k++) {
		int ai = a[k]; ui q = F.qry(ai + 1, cur); ui aval = tt[ai];
		ans += coefC * q;
		F.mdf(1, ai, aval); F.upd(ai, 1);
	}

	//4.
	for (int i = 1; i <= n; i++) CR.add(a[i], 1), SR.add(a[i], tt[a[i]]);
	const bool case1 = (X <= Z && X + Y >= Z);
	const bool case2 = (X <= Z && X + Y < Z);
	for (int i = 1; i <= n; i++) {
		int ai = a[i]; ui aval = tt[ai];
		CR.add(ai, -1), SR.add(ai, -aval);
		ui lcnt = CL.qry(ai + 1, cur), rcnt = CR.qry(1, ai - 1), ltot = SL.qry(ai + 1, cur), rtot = SR.qry(1, ai - 1);
		if (case1) {
			ans += X * ltot * rcnt + (Z - X) * aval * lcnt * rcnt - Z * rtot * lcnt;
		}
		else if (case2) {
			ans += X * ltot * rcnt + Y * aval * lcnt * rcnt - (X + Y) * rtot * lcnt;
		}
		else {
			ans += Z * ltot * rcnt - Z * rtot * lcnt;
		}
		CL.add(ai, 1), SL.add(ai, aval);
	}
	cout << ans;
	cerr<<'\n'<<(clock()-STA)/CLOCKS_PER_SEC,STA=clock();
	return 0;
}