#include<bits/stdc++.h>
#define int long long
#define mod 998244353ll
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
const int maxn=5010;
const int inf=1e9;
bool mbe;

int n,ans;
vector<int> e[maxn];
int dp[maxn][maxn],f[maxn],siz[maxn];
void dfs(int u){
    dp[u][0]=1;
    for(int v:e[u]){
        dfs(v);
        for(int i=0;i<=siz[u];i++){
            for(int j=0;j<=siz[v];j++){
                (f[i+j]+=dp[u][i]*dp[v][j])%=mod;
            }
        }
        for(int i=0;i<=siz[u]+siz[v];i++)dp[u][i]=f[i],f[i]=0;
        siz[u]+=siz[v];
    }
    siz[u]++;
    for(int i=siz[u];i;i--)(dp[u][i]+=dp[u][i-1]*(siz[u]-i))%=mod;
}
int fac[maxn];
void work(){
    n=read();
    for(int i=2;i<=n;i++)e[read()].pb(i);
    dfs(1);
    fac[0]=1;for(int i=1;i<=n;i++)fac[i]=fac[i-1]*i%mod;
    for(int i=0;i<=n;i++)(ans+=((i&1)?mod-1:1)*dp[1][i]%mod*fac[n-i])%=mod;
    printf("%lld\n",ans);
}

bool med;
int T;
signed main(){
    // freopen(".in","r",stdin);
    // freopen(".out","w",stdout);
    
    // cerr<<(&mbe-&med)/1024.0/1024.0<<"\n";
    
    T=1;
    while(T--)work();
}