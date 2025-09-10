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
const int maxn=200010;
const int inf=1e9;
bool mbe;

int n,q;
int head[maxn],tot;
struct nd{
    int nxt,to;
}e[maxn<<1];
void add(int u,int v){e[++tot]={head[u],v};head[u]=tot;}
int fa[maxn],dep[maxn],siz[maxn],son[maxn];
void dfs(int u){
    dep[u]=dep[fa[u]]+1,siz[u]=1,son[u]=0;
    for(int i=head[u];i;i=e[i].nxt){
        int v=e[i].to;if(v==fa[u])continue;
        fa[v]=u,dfs(v);siz[u]+=siz[v];
        if(siz[son[u]]<siz[v])son[u]=v;
    }
}
int dfn[maxn],rnk[maxn],idx,tp[maxn];
void dfs(int u,int lst){
    rnk[dfn[u]=++idx]=u;tp[u]=lst;
    if(!son[u])return ;dfs(son[u],lst);
    for(int i=head[u];i;i=e[i].nxt){
        int v=e[i].to;if(v==fa[u]||v==son[u])continue;
        dfs(v,v);
    }
}
int lca(int u,int v){
    while(tp[u]!=tp[v]){
        if(dep[tp[u]]<dep[tp[v]])swap(u,v);
        u=fa[tp[u]];
    }
    if(dep[u]<dep[v])swap(u,v);
    return v;
}
vector<tuple<int,int,int>> updf[maxn],updg[maxn],updh[maxn];
void upd(int u,int v,int d,int id){
    updg[u].pb({1,d,id}),updg[fa[v]].pb({-1,d,id});
    updf[son[u]].pb({1,d-1,id});
    while(tp[u]!=tp[v]){
        updf[tp[u]].pb({-1,d-1,id}),updf[son[fa[tp[u]]]].pb({1,d-1,id});
        u=fa[tp[u]];
    }
}
int ans[maxn];
#define lb(x) (x&(-x))
int tree[maxn];
void upd(int x,int w){
    while(x<=n)tree[x]+=w,x+=lb(x);
}
int que(int x){
    int res=0;while(x)res+=tree[x],x-=lb(x);
    return res;
}
int que(int l,int r){
	if(l>r)return 0;
	return que(r)-que(l-1);}
void clr(){for(int i=1;i<=n;i++)tree[i]=0;}
void dfsf(int u,int fa){
    for(auto[op,d,id]:updf[u])ans[id]-=op*que(dep[u],min(n,dep[u]+d));
    upd(dep[u],1);
    for(int i=head[u];i;i=e[i].nxt){
        int v=e[i].to;if(v==fa)continue;
        dfsf(v,u);
    }
    for(auto[op,d,id]:updf[u])ans[id]+=op*que(dep[u],min(n,dep[u]+d));
}
void dfsg(int u,int fa){
    for(int i=max(dfn[u]+1,dfn[son[u]]+siz[son[u]]);i<dfn[u]+siz[u];i++)upd(dep[rnk[i]]-dep[u],1);
    for(auto[op,d,id]:updg[u])ans[id]+=op*que(1,d);
    for(int i=head[u];i;i=e[i].nxt){
        int v=e[i].to;if(v==fa)continue;
        dfsg(v,u);
    }
    for(int i=max(dfn[u]+1,dfn[son[u]]+siz[son[u]]);i<dfn[u]+siz[u];i++)upd(dep[rnk[i]]-dep[u],-1);
}
int w[maxn],sum,rt;
bool vis[maxn];
void getrt(int u,int fa){
    siz[u]=1;w[u]=0;
    for(int i=head[u];i;i=e[i].nxt){
        int v=e[i].to;if(v==fa||vis[v])continue;
        getrt(v,u);siz[u]+=siz[v];
        w[u]=max(w[u],siz[v]);
    }
    w[u]=max(w[u],sum-siz[u]);
    if(w[u]<=sum/2)rt=u;
}
void dfs1(int u,int fa){
    rnk[dfn[u]=++idx]=u;
    siz[u]=1;dep[u]=dep[fa]+1;
    for(int i=head[u];i;i=e[i].nxt){
        int v=e[i].to;if(v==fa||vis[v])continue;
        dfs1(v,u);siz[u]+=siz[v];
    }
}
int val[maxn];
void sovle(int u){
    vis[u]=1;dep[0]=-1;idx=0;dfs1(u,0);
    for(int i=1;i<=siz[u];i++)val[dep[rnk[i]]]++;
    for(int i=1;i<=siz[u];i++)val[i]+=val[i-1];
    for(int i=1;i<=siz[u];i++){
    	int v=rnk[i];
	    for(auto[op,d,id]:updh[v])if(d>=dep[v])ans[id]+=op*val[min(siz[u],d-dep[v])];
    }
    for(int i=0;i<=siz[u];i++)val[i]=0;
    for(int i=head[u];i;i=e[i].nxt){
        int v=e[i].to;if(vis[v])continue;
        for(int j=dfn[v];j<dfn[v]+siz[v];j++)val[dep[rnk[j]]]++;
	    for(int j=1;j<=siz[v];j++)val[j]+=val[j-1];
        for(int j=dfn[v];j<dfn[v]+siz[v];j++){
            int vv=rnk[j];
            for(auto[op,d,id]:updh[vv])if(d>=dep[vv])ans[id]-=op*val[min(siz[v],d-dep[vv])];
        }
	    for(int j=1;j<=siz[v];j++)val[j]=0;
    }
    for(int i=head[u];i;i=e[i].nxt){
        int v=e[i].to;if(vis[v])continue;
        sum=siz[v];getrt(v,u);
        sovle(rt);
    }
}
void work(){
    n=read();
    for(int i=1;i<n;i++){
        int u=read(),v=read();
        add(u,v),add(v,u);
    }
    dfs(1),dfs(1,1);
    q=read();
    for(int i=1;i<=q;i++){
        int u=read(),v=read(),d=read(),tp=lca(u,v);
        updf[tp].pb({-2,d,i}),updh[tp].pb({1,d,i});
        upd(u,tp,d,i),upd(v,tp,d,i);
        ans[i]=dep[u]+dep[v]-2*dep[tp]+2;
    }
    dfsf(1,0);clr();dfsg(1,0);
    sum=n;getrt(1,0);sovle(rt);
    for(int i=1;i<=q;i++)printf("%lld\n",ans[i]);
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