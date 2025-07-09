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
const int maxn=100010;

int n,q;
int head[maxn],tot;
struct nd{
    int nxt,to;
}e[maxn<<1];
void add(int u,int v){e[++tot]={head[u],v};head[u]=tot;}
int siz[maxn],w[maxn],rt,sum;
bool vis[maxn];
void getrt(int u,int fa){
    siz[u]=1,w[u]=0;
    for(int i=head[u];i;i=e[i].nxt){
        int v=e[i].to;if(v==fa||vis[v])continue;
        getrt(v,u),siz[u]+=siz[v],w[u]=max(w[u],siz[v]);
    }
    w[u]=max(w[u],sum-siz[u]);
    if(w[u]<=sum/2)rt=u;
}
int fa[maxn];
void sovle(int u){
    vis[u]=1;getrt(u,0);
    for(int i=head[u];i;i=e[i].nxt){
        int v=e[i].to;if(vis[v])continue;
        sum=siz[v];getrt(v,u);fa[rt]=u;sovle(rt);
    }
}
int dep[maxn],st[17][maxn],dfn[maxn],idx;
void dfs(int u,int fa){
    dep[u]=dep[fa]+1;st[0][dfn[u]=++idx]=fa;
    for(int i=head[u];i;i=e[i].nxt){
        int v=e[i].to;if(v==fa)continue;
        dfs(v,u);
    }
}
int mmax(int u,int v){return dfn[u]<dfn[v]?u:v;}
int lca(int u,int v){
    if(u==v)return u;
    u=dfn[u],v=dfn[v];
    if(u>v)swap(u,v);u++;
    int k=__lg(v-u+1);
    return mmax(st[k][u],st[k][v-(1<<k)+1]);
}
int dis(int u,int v){return dep[u]+dep[v]-2*dep[lca(u,v)];}
void work(){
    n=read();
    for(int i=1;i<=n;i++)
}

int T;
signed main(){
    // freopen(".in","r",stdin);
    // freopen(".out","w",stdout);
    
    T=1;
    while(T--)work();
}