#include<bits/stdc++.h>
#define int __int128
#define pii pair<int, int>
#define mp make_pair
#define pb push_back
#define fi first
#define se second

using namespace std;

template <typename T>
inline void read(T &tr){
    tr=0;char ch=getchar();bool f=false;
    while(!isdigit(ch)){if(ch=='-'){f=true;}ch=getchar();}
    while(isdigit(ch)){tr=(tr<<1)+(tr<<3)+(ch^48);ch=getchar();}
    tr=f?-tr:tr;
    return ;
}
template <typename T>
inline void write(T tr){
    if(tr<0) putchar('-'),tr=-tr;
    if(tr>9) write(tr/10);
    putchar(tr%10^48);
    return ;
}
template <typename T>
inline void print(T tr){write(tr);putchar('\n');}

const int N = 5e5 + 10, inf = 1e20;

int t, n, k;
int a[N], b[N], s1[N], s2[N];
int f[N], g[N];

inline int w(int l, int r){return (s1[r] - s1[l]) * (s2[r] - s2[l]) + f[l];}
struct S{int l, r, ls;};

void solve(int wt){
    deque<S> dq;
    dq.pb({1, n, 0});
    for(int i = 1; i <= n; i++){
        S now = dq.front();
        f[i] = wt + w(now.ls, i);g[i] = g[now.ls] + 1;
        dq.front().l++;
        if(dq.front().r <= i) dq.pop_front();
        int lt = n + 1;
        while(!dq.empty()){
            S to = dq.back();
            if(w(i, to.l) <= w(to.ls, to.l)) lt = to.l, dq.pop_back();
            else if(w(i, to.r) >= w(to.ls, to.r)) break;
            else{
                int l = to.l, r = to.r;
                while(l <= r){
                    int mid = (l + r) >> 1;
                    if(w(i, mid) <= w(to.ls, mid)) r = mid - 1;
                    else l = mid + 1;
                }
                lt = r + 1;dq.back().r = r;break;
            }
        }
        if(lt <= n) dq.pb({lt, n, i});
    }
}

signed main(){
    read(t);
    while(t--){
        read(n); read(k);
        for(int i = 1; i <= n; i++) read(a[i]), b[i] = 1;
        sort(a + 1, a + n + 1);
        int cnt = 0;
        for(int i = 1; i <= n; i++) if(a[i] < 0) cnt++;
        if(n - cnt + 1 <= k){
            int ans = 0, sum = 0, len = 0;
            for(int i = n; i >= 1; i--){
                if(k > 1) ans += a[i], k--;
                else sum += a[i], len++;
            }
            print(ans + sum * len);
            continue;
        }
        int m = 1;
        for(int i = 2; i <= n; i++){
            if(a[i] < 0) a[1] += a[i], b[1]++;
            else a[++m] = a[i];
        }
        n = m;
        for(int i = 1; i <= n; i++) s1[i] = s1[i - 1] + a[i], s2[i] = s2[i - 1] + b[i];
        int l = -inf, r = inf;
        while(l <= r){
            int mid = (l + r) >> 1;
            solve(-mid);
            if(g[n] < k) l = mid + 1;
            else r = mid - 1;
        }
        // print(n);
        solve(-r - 1);
        // print(f[n]);
        // print(g[n]);
        // print(r+1);
        print(f[n] + k * (r + 1));
    }
    return 0;
}
