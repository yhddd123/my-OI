#pragma GCC optimize("Ofast", "unroll-loops", "no-stack-protector")
#define atsum(l, r) accumulate(l, r, 0)
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/hash_policy.hpp>
using namespace std;
using ll = long long;
using ull = unsigned long long;
constexpr int inf = 0x3f3f3f3f;
constexpr ll INF = 0x3f3f3f3f3f3f3f3f;
template <typename T>
inline void chkmin(T &x, T y) { x = min(x, y); }
template <typename T>
inline void chkmax(T &x, T y) { x = max(x, y); }
namespace FastIO
{
// ------------------------------
#define IN_HAS_NEG
#define OUT_HAS_NEG
#define CHK_EOF
#define DISABLE_MMAP
// ------------------------------
#if __cplusplus < 201400
#error Please use C++14 or higher.
#endif
#if __cplusplus > 201700
#define INLINE_V inline
#else
#define INLINE_V
#endif
#if ( defined(LOCAL) || defined (_WIN32) ) && !defined(DISABLE_MMAP)
#define DISABLE_MMAP
#endif
#ifndef DISABLE_MMAP
#include<sys/mman.h>
#endif
#ifdef LOCAL
    inline char gc() { return getchar(); }
    inline void pc(char c) { putchar(c); }
#else
#ifdef DISABLE_MMAP
    INLINE_V constexpr int _READ_SIZE = 1 << 18;
    INLINE_V static char _read_buffer[_READ_SIZE], *_read_ptr = nullptr, *_read_ptr_end = nullptr;
    inline char gc()
    {
        if ( __builtin_expect(_read_ptr == _read_ptr_end, false) )
        {
            _read_ptr = _read_buffer;
            _read_ptr_end = _read_buffer + fread(_read_buffer, 1, _READ_SIZE, stdin);
#ifdef CHK_EOF
            if ( __builtin_expect(_read_ptr == _read_ptr_end, false) ) return EOF;
#endif
        }
        return *_read_ptr++;
    }
#else
    INLINE_V static const char *_read_ptr = (const char *)mmap(nullptr, INT_MAX, 1, 2, 0, 0);
    inline char gc() { return *_read_ptr++; }
#endif
    INLINE_V constexpr int _WRITE_SIZE = 1 << 18;
    INLINE_V static char _write_buffer[_WRITE_SIZE], *_write_ptr = _write_buffer;
    inline void pc(char c)
    {
        *_write_ptr++ = c;
        if ( __builtin_expect(_write_buffer + _WRITE_SIZE == _write_ptr, false) )
        {
            fwrite(_write_buffer, 1, _write_ptr - _write_buffer, stdout);
            _write_ptr = _write_buffer;
        }
    }
    INLINE_V struct _auto_flush
    {
        ~_auto_flush() { fwrite(_write_buffer, 1, _write_ptr - _write_buffer, stdout); }
    }	_auto_flush;
#endif
#ifdef CHK_EOF
    inline bool _isdigit(char c) { return ( c & 16 ) && c != EOF; }
    inline bool _isgraph(char c) { return c > 32 && c != EOF; }
#else
    inline bool _isdigit(char c) { return c & 16; }
    inline bool _isgraph(char c) { return c > 32; }
#endif
    template < class T >
    INLINE_V constexpr bool _is_integer = numeric_limits < T >::is_integer;
    template < class T >
    INLINE_V constexpr bool _is_signed = numeric_limits < T >::is_signed;
    template < class T >
    INLINE_V constexpr bool _is_unsigned = _is_integer < T > && !_is_signed < T >;
    template <> INLINE_V constexpr bool _is_integer < __int128 > = true;
    template <> INLINE_V constexpr bool _is_integer < __uint128_t > = true;
    template <> INLINE_V constexpr bool _is_signed < __int128 > = true;
    template <> INLINE_V constexpr bool _is_unsigned < __uint128_t > = true;
#undef INLINE_V
    inline void read(char &c) { do c = gc(); while ( !_isgraph(c) ); }
    inline void read_cstr(char *s)
    {
        char c = gc(); while ( !_isgraph(c) ) c = gc();
        while ( _isgraph(c) ) *s++ = c, c = gc();
        *s = 0;
    }
    inline void read(string &s)
    {
        char c = gc(); s.clear(); while ( !_isgraph(c) ) c = gc();
        while ( _isgraph(c) ) s.push_back(c), c = gc();
    }
#ifdef IN_HAS_NEG
    template < class T, enable_if_t < _is_signed < T >, int > = 0 >
    inline void read(T &x)
    {
        char c = gc(); bool f = true; x = 0;
        while ( !_isdigit(c) ) { if ( c == 45 ) f = false; c = gc(); }
        if ( f ) while ( _isdigit(c) ) x = x * 10 + ( c & 15 ), c = gc();
        else     while ( _isdigit(c) ) x = x * 10 - ( c & 15 ), c = gc();
    }
    template < class T, enable_if_t < _is_unsigned < T >, int > = 0 >
#else
    template < class T, enable_if_t < _is_integer < T >, int > = 0 >
#endif
    inline void read(T &x)
    {
        char c = gc(); while ( !_isdigit(c) ) c = gc();
        x = 0; while ( _isdigit(c) ) x = x * 10 + ( c & 15 ), c = gc();
    }
    inline void write(char c) { pc(c); }
    inline void write_cstr(const char *s) { while ( *s ) pc(*s++); }
    inline void write(const string &s) { for ( char c : s ) pc(c); }
#ifdef OUT_HAS_NEG
    template < class T, enable_if_t < _is_signed < T >, int > = 0 >
    inline void write(T x)
    {
        char buffer[numeric_limits < T >::digits10 + 1]; int digits = 0;
        if ( x >= 0 )  do buffer[digits++] =  ( x % 10 ) | 48, x /= 10; while ( x );
        else { pc(45); do buffer[digits++] = -( x % 10 ) | 48, x /= 10; while ( x ); }
        while ( digits ) pc(buffer[--digits]);
    }
    template < class T, enable_if_t < _is_unsigned < T >, int > = 0 >
#else
    template < class T, enable_if_t < _is_integer < T >, int > = 0 >
#endif
    inline void write(T x)
    {
        char buffer[numeric_limits < T >::digits10 + 1]; int digits = 0;
        do buffer[digits++] = ( x % 10 ) | 48, x /= 10; while ( x );
        while ( digits ) pc(buffer[--digits]);
    }
    template < int N > struct _tuple_io_helper
    {
        template < class ...T >
        static inline void _read(tuple < T... > &x)
        { _tuple_io_helper < N - 1 >::_read(x), read(get < N - 1 > (x)); }
        template < class ...T >
        static inline void _write(const tuple < T... > &x)
        { _tuple_io_helper < N - 1 >::_write(x), pc(32), write(get < N - 1 > (x)); }
    };
    template <> struct _tuple_io_helper < 1 >
    {
        template < class ...T >
        static inline void _read(tuple < T... > &x) { read(get < 0 > (x)); }
        template < class ...T >
        static inline void _write(const tuple < T... > &x) { write(get < 0 > (x)); }
    };
    template < class ...T >
    inline void read(tuple < T... > &x) { _tuple_io_helper < sizeof...(T) >::_read(x); }
    template < class ...T >
    inline void write(const tuple < T... > &x) { _tuple_io_helper < sizeof...(T) >::_write(x); }
    template < class T1, class T2 >
    inline void read(pair < T1, T2 > &x) { read(x.first), read(x.second); }
    template < class T1, class T2 >
    inline void write(const pair < T1, T2 > &x) { write(x.first), pc(32), write(x.second); }
    template < class T1, class ...T2 >
    inline void read(T1 &x, T2 &...y) { read(x), read(y...); }
    template < class ...T >
    inline void read_cstr(char *x, T *...y) { read_cstr(x), read_cstr(y...); }
    template < class T1, class ...T2 >
    inline void write(const T1 &x, const T2 &...y) { write(x), write(y...); }
    template < class ...T >
    inline void write_cstr(const char *x, const T *...y) { write_cstr(x), write_cstr(y...); }
    template < class T >
    inline void print(const T &x) { write(x); }
    inline void print_cstr(const char *x) { write_cstr(x); }
    template < class T1, class ...T2 >
    inline void print(const T1 &x, const T2 &...y) { print(x), pc(32), print(y...); }
    template < class ...T >
    inline void print_cstr(const char *x, const T *...y) { print_cstr(x), pc(32), print_cstr(y...); }
    inline void println() { pc(10); }
    inline void println_cstr() { pc(10); }
    template < class ...T >
    inline void println(const T &...x) { print(x...), pc(10); }
    template < class ...T >
    inline void println_cstr(const T *...x) { print_cstr(x...), pc(10); }
}
using namespace FastIO;
template <typename T>
inline void clear(T &x) {
    T y;
    swap(x, y);
}
const int N = 5e5 + 10;
bool o1;
int m;
struct BIT {
#define low(x) ((x) & -(x))
    int w[N];
    inline void update(int u) {
        while (u <= m) w[u] ^= 1, u += low(u);
    }
    inline int query(int u) {
        int ans = 0;
        while (u) ans ^= w[u], u ^= low(u);
        return ans;
    }
} S;
namespace SequenceSolver {
    struct Node{
        int sum;
        int type;
    };
    int timer[N << 1], len, a[N << 1], s;
    int cursum;
    inline Node operator+(Node a, Node b) {
        if (a.type) return {a.sum + cursum - b.sum, !b.type};
        return {a.sum + b.sum, b.type};
    }
    Node qwq[30000000];
    Node *per;
    Node *val[N];
    vector<int> al[N], ar[N], bl[N], br[N];
    int all[N];
    tuple<int, vector<int>, Node* > solve(int u, int L, int R) {
        if (L == R) {
            if (timer[L]) {
                auto c = per++;
                *c = {0, 1};
                return make_tuple(all[u] = 0, vector<int>{timer[L]}, val[u] = c);
            } else {
                return make_tuple(all[u] = a[L], vector<int>{}, val[u] = per);
            }
        }
        int M = L + R >> 1;
        auto [sa, ta, fa] = solve(u << 1, L, M);
        auto [sb, tb, fb] = solve(u << 1 | 1, M + 1, R);
        int siz = ta.size() + tb.size(), sum = sa + sb, sizl = ta.size(), sizr = tb.size();
        cursum = sb;
        // vector<vector<Node> > fans(siz, vector<Node>(siz));
        Node *fans = per;
        per += siz * siz;
        // vector<int> al(siz), ar(siz), bl(siz), br(siz);
        al[u].resize(siz), ar[u].resize(siz), bl[u].resize(siz), br[u].resize(siz);
        vector<int> res = ta;
        res.insert(res.end(), tb.begin(), tb.end());
        inplace_merge(res.begin(), res.begin() + ta.size(), res.end());
        int pa = 0, pb = 0;
        for (int i = 0; i < siz; i++) {
            while (pa < ta.size() && ta[pa] < res[i]) ++pa; 
            while (pb < tb.size() && tb[pb] < res[i]) ++pb;
            al[u][i] = pa, bl[u][i] = pb; 
        }
        pa = 0, pb = 0;
        for (int i = 0; i < siz; i++) {
            while (pa < ta.size() && ta[pa] <= res[i]) ++pa; 
            while (pb < tb.size() && tb[pb] <= res[i]) ++pb;
            ar[u][i] = pa - 1, br[u][i] = pb - 1; 
        }
        Node Emp = {};
        for (int i = 0; i < siz; i++)
            for (int j = i; j < siz; j++) {
                if (al[u][i] <= ar[u][j]) {
                    if (bl[u][i] <= br[u][j]) fans[i * siz + j] = fa[al[u][i] * sizl + ar[u][j]] + fb[bl[u][i] * sizr + br[u][j]];
                    else fans[i * siz + j] = fa[al[u][i] * sizl + ar[u][j]] + Emp;
                } else {
                    if (bl[u][i] <= br[u][j]) fans[i * siz + j] = fb[bl[u][i] * sizr + br[u][j]];
                    else fans[i * siz + j] = {};
                }
            }
        return {all[u] = sum, res, val[u] = fans};
    }
    tuple<int, int, Node> que[N];
    pair<int, int> AL[N];
    pair<int, int> AR[N];
    int quecnt, fl[N], fr[N], pres[N << 1];
    inline void dp(int u, int L, int R, int x, int cl, int cr, Node &v) {
        if (cl > cr) {
            v.sum += v.type * (pres[min(x, R)] - pres[L - 1]);
            return;
        }
        if (R <= x) {
            cursum = all[u];
            v = v + val[u][cl * al[u].size() + cr];
            return;
        }
        int M = L + R >> 1;
        dp(u << 1, L, M, x, al[u][cl], ar[u][cr], v);
        if (x > M) dp(u << 1 | 1, M + 1, R, x, bl[u][cl], br[u][cr], v);
    }
    inline void focus(int L, int R) {
        per = qwq;
        auto [sum, lis, f] = solve(1, L, R);
        int cl = 0;
        pres[L - 1] = 0;
        for (int i = L; i <= R; i++) pres[i] = pres[i - 1] + a[i];
        for (int i = 1; i <= quecnt; i++) {
            while (cl < lis.size() && lis[cl] < AL[i].first) ++cl;
            fl[AL[i].second] = cl;
        }
        cl = 0;
        for (int i = 1; i <= quecnt; i++) {
            while (cl < lis.size() && lis[cl] <= AR[i].first) ++cl;
            fr[AR[i].second] = cl - 1;
        }

        // return;

        for (int _ = 1; _ <= quecnt; _++) {
            auto &[x, id, res] = que[_];
            int cql = fl[_], cqr = fr[_];
            if (x >= R) {
                cursum = sum;
                if (cql <= cqr) res = res + f[cql * lis.size() + cqr];
                else res.sum += res.type * cursum;
            } else if (x >= L && x < R) {
                dp(1, L, R, x, cql, cqr, res);
            }
        }
    }
    inline void solve() {
        s = max(1.0, sqrt(len) * 1.28);
        if (len <= 800) {
            for (int i = 1; i <= quecnt; i++) {
                int type = 0;
                int sum = 0, L = AL[i].first, R = AR[i].first, x = get<0>(que[i]);
#pragma GCC unroll 8
                for (int j = len; j > x; j--)
                    if (timer[j] >= L && timer[j] <= R) type ^= 1;
#pragma GCC unroll 8
                for (int j = x; j; j--) {
                    if (timer[j] >= L && timer[j] <= R) type ^= 1;
                    sum += type * a[j];
                }
                get<2>(que[i]) = {sum, type};
            }
            return;
        }
        // if (len <= 200) s = len;
        // if (len > 200) cerr << "fsiasgfgafg" << ' ' << len << endl;
        int cc = 0;
        for (int i = 1; i <= len; i++)
            if (timer[i]) S.update(timer[i]);
        for (int i = 1; i <= quecnt; i++)  get<2>(que[i]).type = S.query(AR[i].first) ^ S.query(AL[i].first - 1);

        sort(AL + 1, AL + quecnt + 1);
        sort(AR + 1, AR + quecnt + 1);

        for (int L = 1, R; L <= len; L = R + 1)
            R = min(len, L + s - 1), focus(L, R);
        for (int i = 1; i <= len; i++)
            if (timer[i]) S.update(timer[i]);
    }
};
using namespace SequenceSolver;
basic_string<int> vec[N];
int w[N], n, q, rej[N], f[N], ql[N], qr[N], ans[N];
int top[N], son[N], siz[N], dfn[N], dfncnt, fa[N], dep[N];
basic_string<int> ask[N];
basic_string<int> changetime[N];
void dfs(int u) {
    siz[u] = rej[u];
    for (int v : vec[u])
        if (v != fa[u]) {
            fa[v] = u, dep[v] = dep[u] + 1, dfs(v), siz[u] += siz[v];
            if (siz[v] > siz[son[u]]) son[u] = v;
        }
}
void dfs2(int u) {
    dfn[u] = ++dfncnt;
    if (son[u]) top[son[u]] = top[u], dfs2(son[u]);
    for (int v : vec[u])
        if (v != fa[u] && v != son[u]) dfs2(top[v] = v);
}
inline int lca(int u, int v) {
    while (top[u] != top[v]) dep[top[u]] > dep[top[v]] ? u = fa[top[u]] : v = fa[top[v]];
    return dep[u] < dep[v] ? u : v; 
}
inline int dist(int u, int v) { return dep[u] + dep[v] - 2 * dep[lca(u, v)]; }
bool o2;
int main() {
    // cerr << (&o1 - &o2) / 1048576. << endl;
    // freopen("in2", "r", stdin);
    // freopen("1.out", "w", stdout);
    read(n, m, q);
    for (int i = 1; i <= n; i++) rej[i] = 1;
    for (int i = 2, x; i <= n; i++) read(x), vec[x] += i;
    for (int i = 1; i <= n; i++) read(w[i]);
    for (int i = 1; i <= m; i++) read(f[i]), ++rej[f[i]];
    dfs(1), dfs2(top[1] = 1);
    for (int i = 1; i <= m; i++) {
        int u = f[i];
        while (u) changetime[u] += i, u = fa[top[u]];
    }
    for (int i = 1, x; i <= q; i++) {
        read(ql[i], qr[i], x);
        while (x)
            ask[x] += i, x = fa[top[x]];
    }
    for (int i = 1; i <= n; i++)
        if (top[i] == i) {
            len = 0, quecnt = 0;
            int u = i;
            while (u) {
                ++len, a[len] = w[u], timer[len] = 0;
                for (int v : changetime[u]) ++len, a[len] = 0, timer[len] = v;
                for (int v : ask[u]) {
                    ++quecnt;
                    que[quecnt] = {len, v, Node{}};
                    AL[quecnt] = {ql[v], quecnt};
                    AR[quecnt] = {qr[v], quecnt};
                }
                u = son[u];
            }
            solve();
            for (int i = 1; i <= quecnt; i++) ans[get<1>(que[i])] += get<2>(que[i]).sum;
        }
    for (int i = 1; i <= q; i++) println(ans[i]);
    // cerr << double(clock()) / CLOCKS_PER_SEC << endl;
    return 0;
}
/*
5 3 1
1 2 3 3
907 609 48 670 184
2
3
5
1 3 3

5 3 1
1 2 3 3
907 609 48 670 184
2
3
5
1 2 5
*/