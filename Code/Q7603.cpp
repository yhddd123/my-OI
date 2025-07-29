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
const int maxn=2010;
const int inf=1e9;
bool mbe;

int n;
pii a[maxn],b[maxn];
vector<int> g[maxn];
bool vis[maxn][maxn];
void dfs(int u,int st){
    vis[st][u]=1;
    for(int v:g[u]){
        if(!vis[st][v])dfs(v,st);
    }
}
vector<int> e[maxn<<1];
bool chk(pii u,pii v){return vis[u.se][v.fi]|vis[v.se][u.fi];}
int dfn[maxn<<1],lw[maxn<<1],idx;
int st[maxn<<1],tp;
int scc[maxn<<1],scct;
void tar(int u){
    dfn[u]=lw[u]=++idx;st[++tp]=u;
    for(int v:e[u]){
        if(!dfn[v]){
            tar(v);
            lw[u]=min(lw[u],lw[v]);
        }
        else if(!scc[v])lw[u]=min(lw[u],dfn[v]);
    }
    if(dfn[u]==lw[u]){
        scc[st[tp]]=++scct;
        while(st[tp--]!=u)scc[st[tp]]=scct;
    }
}
bool check(int x){
    for(int i=1;i<=2*x;i++)e[i].clear();
    for(int i=1;i<=x;i++){
        for(int j=i+1;j<=x;j++){
            if(!chk(a[i],a[j]))e[i].pb(j+x),e[j].pb(i+x);
            if(!chk(a[i],b[j]))e[i].pb(j),e[j+x].pb(i+x);
            if(!chk(b[i],a[j]))e[i+x].pb(j+x),e[j].pb(i);
            if(!chk(b[i],b[j]))e[i+x].pb(j),e[j+x].pb(i);
        }
    }
    // cout<<x<<"\n";
    // for(int i=1;i<=2*x;i++){
    //     for(int j:e[i])cout<<i<<" "<<j<<"\n";
    // }
    for(int i=1;i<=2*x;i++)dfn[i]=scc[i]=0;idx=tp=scct=0;
    for(int i=1;i<=2*x;i++)if(!dfn[i])tar(i);
    // cout<<scct<<"\n";
    for(int i=1;i<=x;i++)if(scc[i]==scc[i+x])return 0;
    return 1;
}
void work(){
    n=read();
    for(int i=1;i<=n;i++){
        a[i]={read(),read()};
        b[i]={read(),read()};
        g[a[i].fi].pb(a[i].se),g[b[i].fi].pb(b[i].se);
    }
    for(int i=1;i<=n;i++)dfs(i,i);
    int l=1,r=n,res=1;
    while(l<=r){
        int mid=l+r>>1;
        if(check(mid))res=mid,l=mid+1;
        else r=mid-1;
    }
    printf("%lld\n",res);
}

bool med;
int T;
signed main(){
    // freopen("A.in","r",stdin);
    // freopen("A.out","w",stdout);
    
    // cerr<<(&mbe-&med)/1024.0/1024.0<<"\n";
    
    T=1;
    while(T--)work();
}