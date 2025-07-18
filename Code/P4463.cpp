#include<bits/stdc++.h>
#define int long long
// #define mod 998244353ll
#define pii pair<int,int>
#define fi first
#define se second
#define pb push_back
using namespace std;
inline int read(){
    int x=0,fl=1;char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')fl=-1;ch=getchar();}
    while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    return x*fl;
}
const int maxn=510;
const int inf=1e9;

int n,k,mod;
inline int ksm(int a,int b=mod-2){
    int ans=1;
    while(b){
        if(b&1)ans=ans*a%mod;
        a=a*a%mod;
        b>>=1;
    }
    return ans;
}
int fac[maxn],inv[maxn],ni[maxn];
void inc(int &u,int v){((u+=v)>=mod)&&(u-=mod);}
namespace poly{
    vector<int> mul(const vector<int> a, const vector<int> b) {
        int n = a.size(), m = b.size();
        vector<int> res(n + m - 1, 0);
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < m; ++j)
                res[i + j] = (res[i + j] + a[i] * b[j] % mod) % mod;
        return res;
    }
    vector<int> exp(const vector<int>& a) {
        int n = a.size() - 1;
        vector<int> g(n + 1, 0);
        g[0] = 1;
        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= i; ++j) {
                g[i] = (g[i] + a[j] * j % mod * g[i - j] % mod) % mod;
            }
            g[i] = g[i] * ni[i] % mod;
        }
        return g;
    }
}
vector<int> f;
int pw[maxn];
void calc_f(int n) {
    for (int l = 0; l <= n; ++l) {
        for (int i = 0; i < l; ++i) {
            f[l] = (f[l] + f[i] * inv[i] % mod * inv[l - i + 1] % mod) % mod;
        }
        f[l] = ni[l + 1] * ((pw[l + 1] + mod - fac[l + 1] * f[l] % mod) % mod) % mod;
    }
}
void work(){
    k=read();n=read();mod=read();
    f.resize(n+1);
    fac[0]=1;for(int i=1;i<=n+1;i++)fac[i]=fac[i-1]*i%mod;
    inv[n+1]=ksm(fac[n+1]);for(int i=n;~i;i--)inv[i]=inv[i+1]*(i+1)%mod;
    ni[0]=1;for(int i=1;i<=n+1;i++)ni[i]=fac[i-1]*inv[i]%mod;
    pw[0]=1;for(int i=1;i<=n+1;i++)pw[i]=pw[i-1]*(k+1)%mod;
    calc_f(n);
    f[0]=0;for(int i=1;i<=n;i++)f[i]=(((i+1)&1)?mod-1:1)*ni[i]%mod*f[i]%mod;
    f=poly::exp(f);
    printf("%lld\n",f[n]*fac[n]%mod);
}

int T;
signed main(){
    // freopen("A.in","r",stdin);
    // freopen(".out","w",stdout);
    
    T=1;
    while(T--)work();
}