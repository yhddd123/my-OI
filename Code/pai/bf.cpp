#include <bits/stdc++.h>

using namespace std;

namespace FastRead{
    char buf[1000005], *s = buf, *t = buf;
    #define gc() s == t && (t = (s = buf) + fread(buf, 1, 1000000, stdin), s == t) ? EOF : *s ++ 
    template <typename T>
    inline void Read(T &x)
    {
        x = 0;
        int f = 0;
        char ch = gc();
        while(ch < '0' || ch > '9') f = ch == '-', ch = gc();
        while('0' <= ch && ch <= '9') x = x * 10 + ch - 48, ch = gc();
        f && (x = -x);
    }
    inline void Read(char* str)
    {
        char ch = gc();
        while(ch <= 32 || ch > 126) ch = gc();
        while(32 < ch && ch <= 126) *(str ++ ) = ch, ch = gc();
    }
};
using FastRead::Read;

typedef unsigned long long ULL;

const int N = 1.1e5 + 5, B = 128;

int n, m;
int x[N];
int m0;
struct Query{
    int l, r, b, i;
}q0[N];
vector<Query> q1[B];
int ans[N];

int cnt[N];
ULL a[N], b[N];

inline void Init(int n)
{
    for(int i = 0; i < n >> 6; i ++ ) a[i] = -1;
    a[(n >> 6)] = (1ULL << (n & 63)) - 1;
}
inline int Any(int n)
{
    ULL res = 0;
    for(int i = 0; i <= n >> 6; i ++ ) res |= a[i];
    return !!res;
}
inline void Flip(int i)
{
    b[i >> 6] ^= 1ULL << (i & 63);
}
inline void Split(int l, int r)
{
    if(l >> 6 == r >> 6)
    {
        a[0] &= (b[l >> 6] >> l) & ((1ULL << (r - l)) - 1);
    }
    else if(l & 63)
    {
        for(int i = l >> 6; i <= r >> 6; i ++ )
        {
            a[i - (l >> 6)] &= ~((1ULL << (64 - (l & 63))) - 1) | (b[i] >> (l & 63));
        }
        for(int i = (l >> 6) + 1; i <= r >> 6; i ++ )
        {
            a[i - (l >> 6) - 1] &= ((1ULL << (64 - (l & 63))) - 1) | (b[i] & ((1ULL << (l & 63)) - 1)) << (64 - (l & 63));
        }
    }
    else
    {
        for(int i = l >> 6; i <= r >> 6; i ++ )
        {
            a[i - (l >> 6)] &= b[i];
        }
    }
}

inline void Add(int i)
{
    if(!cnt[x[i]]) Flip(x[i]);
    cnt[x[i]] ++ ;
}
inline void Del(int i)
{
    cnt[x[i]] -- ;
    if(!cnt[x[i]]) Flip(x[i]);
}
inline int Get(int b)
{
    Init(b);
    for(int i = 0; ; i ++ )
    {
        Split(i * b, (i + 1) * b);
        if(!Any(b)) return i;
    }
}

inline void Solve0()
{
    int siz = n / sqrt(m0) + 1;
    sort(q0 + 1, q0 + m0 + 1, [&](const Query &x, const Query &y) {
        return x.l / siz == y.l / siz ? x.r == y.r ? 0 : (x.r < y.r) ^ ((x.l / siz) & 1) : x.l < y.l;
    });
    for(int l = 1, r = 0, i = 1; i <= m0; i ++ )
    {
        while(r < q0[i].r) Add( ++ r);
        while(l > q0[i].l) Add( -- l);
        while(r > q0[i].r) Del(r -- );
        while(l < q0[i].l) Del(l ++ );
        ans[q0[i].i] = Get(q0[i].b);
    }
}

struct SGT{
    int m;
    vector<int> t;

    inline void Build(int n)
    {
        m = 1;
        while(m < n) m <<= 1;
        t.assign(m * 2, N);
    }
    inline void Modify(int i, int d)
    {
        for(i += m; i; i >>= 1) t[i] = d, d = max(d, t[i ^ 1]);
    }
    inline int Query(int k)
    {
        int u = 1;
        while(u < m)
        {
            if(t[u << 1] > k) u = u << 1;
            else u = u << 1 | 1;
        }
        return u - m;
    }
}t[B];

inline void Solve1(int k)
{
    if(q1[k].empty()) return ;
    const int m = 1e5;
    for(int i = 0; i < k; i ++ ) t[i].Build(m / k + 1);
    sort(q1[k].begin(), q1[k].end(), [&](const Query &x, const Query &y) {return x.l > y.l;});
    for(int i = 0, j = n; i < (int)q1[k].size(); i ++ )
    {
        while(j >= q1[k][i].l)
        {
            t[x[j] % k].Modify(x[j] / k, j);
            j -- ;
        }
        for(int j = 0; j < k; j ++ )
        {
            ans[q1[k][i].i] = max(ans[q1[k][i].i], t[j].Query(q1[k][i].r));
        }
    }
}

int main()
{
    Read(n);
    for(int i = 1; i <= n; i ++ ) Read(x[i]);
    Read(m);
    for(int i = 1; i <= m; i ++ )
    {
        int l, r, b;
        Read(l), Read(r), Read(b);
        if(b < B) q1[b].push_back({l, r, b, i});
        else q0[ ++ m0] = {l, r, b, i};
    }
    Solve0();
    for(int i = 1; i < B; i ++ ) Solve1(i);
    for(int i = 1; i <= m; i ++ ) printf("%d\n", ans[i]);
    return 0;
}