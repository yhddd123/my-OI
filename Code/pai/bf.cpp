#include <bits/stdc++.h>
typedef long long LL;
typedef unsigned long long ULL;
typedef std::pair<int, int> pii;
#define fi first
#define se second
#define MP std::make_pair

LL read()
{
	LL s = 0; int f = 1, c = getchar();
	for (; !isdigit(c); c = getchar()) f ^= (c == '-');
	for (; isdigit(c); c = getchar()) s = s * 10 + (c ^ 48);
	return f ? s : -s;
}
const int inf = 0x3f3f3f3f;
const LL INF = 0x3f3f3f3f3f3f3f3fll;
template<typename T> void Fmin(T &x, T y){ if (y < x) x = y; }
template<typename T> void Fmax(T &x, T y){ if (x < y) x = y; }
const int MAXN = 600005; 
int n, K, m, cnt[MAXN], id[MAXN];
struct Segment{ int l, r, w; } a[MAXN];
#define ls (x << 1)
#define rs (x << 1 | 1)
namespace SGT1
{
	int N;
	int sgt[MAXN << 2], lzy[MAXN << 2];
	void maintain(int x){ sgt[x] = std::max(sgt[ls], sgt[rs]) + lzy[x]; }
	void hard(int x, int v){ sgt[x] += v, lzy[x] += v; }
	void build(int n)
	{
		for (N = 1; N < n; N <<= 1);
		memset(sgt, 0, N << 3), memset(lzy, 0, N << 3);
	}
	void add(int l, int r, int v)
	{
		if (l == r) hard(l += N - 1, v);
		else 
		{
			hard(l += N - 1, v), hard(r += N - 1, v);
			for (; l ^ r ^ 1; maintain(l >>= 1), maintain(r >>= 1))
			{
				if (!(l & 1)) hard(l ^ 1, v);
				if (r & 1) hard(r ^ 1, v);
			}
		}
		for (l >>= 1; l; l >>= 1) maintain(l);
	}
	int Left(int lim)
	{
		if (sgt[1] < lim) return m + 1;
		int x = 1, l = 1, r = N;
		while (l < r)
		{
			int mid = (l + r) >> 1; lim -= lzy[x];
			if (sgt[ls] >= lim) x = ls, r = mid;
			else x = rs, l = mid + 1;
		}
		return l;
	}
	int Right(int lim)
	{
		if (sgt[1] < lim) return 0;
		int x = 1, l = 1, r = N;
		while (l < r)
		{
			int mid = (l + r) >> 1; lim -= lzy[x];
			if (sgt[rs] >= lim) x = rs, l = mid + 1;
			else x = ls, r = mid;
		}
		return l;
	}
}
template<typename T> 
struct SGT2
{
	T sgt[MAXN << 2]; int N;
	void build(int n)
	{ for (N = 1; N < n; N <<= 1) ; }
	void modify(int x, T v)
	{
		sgt[x += N - 1] = v;
		for (x >>= 1; x; x >>= 1)
			sgt[x] = sgt[ls] + sgt[rs];
	}
	T query(int l, int r)
	{
		l += N - 1, r += N - 1;
		if (l == r) return sgt[l];
		T res = sgt[l] + sgt[r];
		for (; l ^ r ^ 1; l >>= 1, r >>= 1)
		{
			if (!(l & 1)) res += sgt[l ^ 1];
			if (r & 1) res += sgt[r ^ 1];
		}
		return res;
	}
} ;
#undef ls
#undef rs
struct SegIn
{
	int id, val;
	SegIn(int _id = 0, int _val = inf) 
	: id(_id), val(_val){}
	friend SegIn operator+(SegIn a, SegIn b)
	{ return a.val < b.val ? a : b; }
	void operator+=(SegIn a)
	{ if (a.val < val) id = a.id, val = a.val; }
} ;
struct SegOut
{
	int id, val;
	SegOut(int _id = 0, int _val = -inf) 
	: id(_id), val(_val){}
	friend SegOut operator+(SegOut a, SegOut b)
	{ return a.val > b.val ? a : b; }
	void operator+=(SegOut a)
	{ if (a.val > val) id = a.id, val = a.val; }
} ;
SGT2<SegIn> IN;
SGT2<SegOut> OUT;
bool in[MAXN];
void init()
{
	n = read(), K = read();
	m = n * 2;
	LL sum = 0;
	for (int i = 1; i <= n; i++)
	{
		a[i].l = read(), a[i].r = read(), a[i].w = read();
		id[a[i].l] = -i, id[a[i].r] = i;
		sum += a[i].w; 
	}
	IN.build(m), OUT.build(m);
	SGT1::build(m);
}
int L, R;
LL sum = 0;
void add(int i, int v){ SGT1::add(a[i].l, a[i].r - 1, v); }
std::set<pii> S;
void putin(int x)
{
	in[x] = true, IN.modify(a[x].r, SegIn(x, a[x].w)), OUT.modify(a[x].r, SegOut());
	add(x, 1), sum += a[x].w;
}
void putout(int x)
{
	in[x] = false, IN.modify(a[x].r, SegIn()), OUT.modify(a[x].r, SegOut(x, a[x].w));
	add(x, -1), sum -= a[x].w;
}
void getin(int x)
{ 
	putin(x);
	if (SGT1::sgt[1] > K)
	{
		int lim = SGT1::Right(K + 1);
		int y = IN.query(lim + 1, m).id;
		putout(y);
	}
}
void try_add()
{
	int lim = SGT1::Left(K);
	int y = OUT.query(1, lim).id;
	if (y) putin(y);
} 
void getout(int x)
{ 
	if (in[x]) 
	{
		sum -= a[x].w, add(x, -1);
		IN.modify(a[x].r, SegIn());
		in[x] = false;
		try_add();
	}
	else OUT.modify(a[x].r, SegOut());
}
bool pushR()
{
	if (id[R] < 0 && R > L)
	{
		add(-id[R], 1);
		if (SGT1::sgt[1] > K) 
			return add(-id[R], -1), false; 
	}
	int x = id[++R];
	if (x > 0)
	{
		if (a[x].l > L) sum += a[x].w;
		else getin(x);
	}
	return true;
}
void pushL()
{
	if (id[L] > 0) getout(id[L]);
	int x = -id[++L];
	if (x > 0 && L < R)
	{
		add(x, -1), try_add();
		if (a[x].r <= R) sum -= a[x].w, getin(x);
	}
}
int main()
{	
	init();
	LL ans = 0;
	for (L = R = 1; L <= m; pushL())
	{
		while (R < m && pushR());
		Fmax(ans, sum);
	}
	printf("%lld\n", ans);
	return 0;
}