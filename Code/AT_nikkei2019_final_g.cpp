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
const int inf=1e9;

int n,q;
vector<pii> que[maxn];
int ans[maxn];
int head[maxn],tot;
struct edge{
    int to,nxt,w;
}e[maxn<<1];
void add(int u,int v,int w){e[++tot]={v,head[u],w};head[u]=tot;}
int siz[maxn],w[maxn],sum,rt;
bool vis[maxn];
void getrt(int u,int fa){
    siz[u]=1,w[u]=0;
    for(int i=head[u];i;i=e[i].nxt){
        int v=e[i].to;if(v==fa||vis[v])continue;
        getrt(v,u);
        siz[u]+=siz[v];
        w[u]=max(w[u],siz[v]);
    }
    w[u]=max(w[u],sum-siz[u]);
    if(w[u]<=sum/2)rt=u;
}
vector<int> id;
int dep[maxn],dis[maxn],val[maxn];
void dfs(int u,int fa){
    siz[u]=1;id.pb(u);
    for(int i=head[u];i;i=e[i].nxt){
        int v=e[i].to;if(v==fa||vis[v])continue;
        dep[v]=dep[u]+1;dis[v]=dis[u]+e[i].w;val[v]=e[i].w;
        dfs(v,u);siz[u]+=siz[v];
    }
}
pii line[maxn];
#define mid ((l+r)>>1)
#define ls lc[nd]
#define rs rc[nd]
int tree[maxn<<5];
int lc[maxn<<5],rc[maxn<<5],idx,rrt;
int calc(int id,int x){return line[id].fi*x+line[id].se;}
void updata(int &nd,int l,int r,int id){
    if(!nd)nd=++idx;
    if(l==r){
        if(calc(id,l)>calc(tree[nd],l))tree[nd]=id;
        return;
    }
    if(calc(id,mid)>calc(tree[nd],mid))swap(id,tree[nd]);
    if(calc(id,l)>calc(tree[nd],l))updata(ls,l,mid,id);
    else updata(rs,mid+1,r,id);
}
int query(int nd,int l,int r,int x){
    if(l==r)return calc(tree[nd],x);
    if(x<=mid)return max(calc(tree[nd],x),query(ls,l,mid,x));
    else return max(calc(tree[nd],x),query(rs,mid+1,r,x));
}
void clr(){
    while(idx)tree[idx]=lc[idx]=rc[idx]=0,idx--;rrt=0;
}
void solve(int u){
    vis[u]=1;id.clear();dep[u]=dis[u]=0;dfs(u,0);
    vector<tuple<int,int,int>> ask;
    for(int v:id){
        if(u!=v)ask.pb({dep[v],0,v});
        for(auto[l,id]:que[v])if(l-dep[v]>=0)ask.pb({l-dep[v],id,v});
    }
    sort(ask.begin(),ask.end());
    // cout<<u<<endl;
    for(auto[l,id,v]:ask){
        // cout<<l<<' '<<id<<' '<<v<<" "<<val[v]<<endl;
        if(id==0){
            line[v]={val[v],dis[v]-dep[v]*val[v]};
            updata(rrt,0,inf,v);
        }
        else ans[id]=max(ans[id],query(rrt,0,inf,l)+dis[v]);
    }
    clr();
    for(int i=head[u];i;i=e[i].nxt){
        int v=e[i].to;if(vis[v])continue;
        sum=siz[v];getrt(v,u);solve(rt);
    }
}
void work(){
    n=read();
    for(int i=1;i<n;i++){
        int u=read(),v=read(),w=read();
        add(u,v,w),add(v,u,w);
    }
    q=read();
    for(int i=1;i<=q;i++){
        int u=read(),l=read();
        que[u].pb({l,i});
    }
    sum=n;rt=0;getrt(1,0);solve(rt);
    for(int i=1;i<=q;i++)printf("%lld\n",ans[i]);
}

int T;
signed main(){
    // freopen("AT_nikkei2019_final_g.in","r",stdin);
    // freopen(".out","w",stdout);
    
    T=1;
    while(T--)work();
}