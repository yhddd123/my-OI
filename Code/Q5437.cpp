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

int n,m,ans=1;
int head[maxn],tot;
struct nd{
    int nxt,to;
}e[maxn<<2];
void add(int u,int v){e[++tot]={head[u],v};head[u]=tot;}
int dfn[maxn],lw[maxn],idx;
int st[maxn],tp;
int scc[maxn],scct;
void tar(int u,int fa){
    dfn[u]=lw[u]=++idx;st[++tp]=u;
    for(int i=head[u];i;i=e[i].nxt){
        int v=e[i].to;if(v==fa)continue;
        if(!dfn[v]){
            tar(v,u);
            lw[u]=min(lw[u],lw[v]);
        }
        else if(!scc[v])lw[u]=min(lw[u],dfn[v]);
    }
    if(dfn[u]==lw[u]){
        scc[st[tp]]=++scct;
        while(st[tp--]!=u)scc[st[tp]]=scct;
    }
}
int pw[maxn*maxn];
int num[maxn],cnt[maxn];
int dp[maxn][maxn],siz[maxn],f[maxn];
void dfs(int u,int fa){
    dp[u][num[u]]=1,siz[u]=num[u];
    for(int i=head[u];i;i=e[i].nxt){
        int v=e[i].to;if(v==fa)continue;
        dfs(v,u);
        for(int j=1;j<=siz[u];j++){
            for(int k=1;k<=siz[v];k++){
                (f[j+k]+=dp[u][j]*dp[v][k]%mod*pw[j*k-1])%=mod;
                (f[j]+=mod-dp[u][j]*dp[v][k]%mod)%=mod;
            }
        }
        siz[u]+=siz[v];
        for(int j=1;j<=siz[u];j++)dp[u][j]=f[j],f[j]=0;
    }
    // for(int j=1;j<=siz[u];j++)cout<<dp[u][j]<<" ";cout<<"\n";
}
void work(){
    n=read();m=read();
    for(int i=1;i<=m;i++){
        int u=read(),v=read();
        add(u,v),add(v,u);
    }
    tar(1,0);
    // for(int i=1;i<=n;i++)cout<<scc[i]<<" ";cout<<"\n";
    pw[0]=1;for(int i=1;i<=n*n;i++)pw[i]=pw[i-1]*2%mod;
    vector<pii> edge;
    for(int u=1;u<=n;u++){
        num[scc[u]]++;
        for(int i=head[u];i;i=e[i].nxt){
            int v=e[i].to;
            if(scc[u]==scc[v])cnt[scc[u]]+=u<v;
            else edge.pb({scc[u],scc[v]});
        }
    }
    for(int i=1;i<=scct;i++)ans=ans*pw[num[i]*(num[i]-1)/2-cnt[i]]%mod;
    for(int i=1;i<=n;i++)head[i]=0;tot=0;
    for(auto[u,v]:edge)add(u,v);
    dfs(1,0);
    int sum=0;for(int i=1;i<=n;i++)(sum+=dp[1][i])%=mod;
    ans=ans*sum%mod;
    printf("%lld\n",ans);
}

bool med;
int T;
signed main(){
    // freopen("A.in","r",stdin);
    // freopen(".out","w",stdout);
    
    // cerr<<(&mbe-&med)/1024.0/1024.0<<"\n";
    
    T=1;
    while(T--)work();
}