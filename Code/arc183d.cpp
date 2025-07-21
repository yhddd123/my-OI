#include<bits/stdc++.h>
// #define int long long
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
const int maxn=250010;
const int inf=1e9;

int n;
int head[maxn],tot;
struct nd{
    int nxt,to;
}e[maxn<<1];
void add(int u,int v){e[++tot]={head[u],v};head[u]=tot;}
int siz[maxn],w[maxn],rt;
void getrt(int u,int fa){
    siz[u]=1;
    for(int i=head[u];i;i=e[i].nxt){
        int v=e[i].to;if(v==fa)continue;
        getrt(v,u);siz[u]+=siz[v];w[u]=max(w[u],siz[v]);
    }
    w[u]=max(w[u],n-siz[u]);
    if(w[u]<=n/2)rt=u;
}
vector<int> id[maxn];
void dfs(int u,int fa,int tp){
    id[tp].pb(u);
    for(int i=head[u];i;i=e[i].nxt){
        int v=e[i].to;if(v==fa||v==((u-1)^1)+1)continue;
        dfs(v,u,tp);
    }
    if(((u-1)^1)+1!=fa)dfs(((u-1)^1)+1,u,tp);
}
priority_queue<pii> q[2];
void work(){
    n=read();
    for(int i=1;i<n;i++){
        int u=read(),v=read();
        add(u,v),add(v,u);
    }
    getrt(1,0);
    for(int i=head[rt];i;i=e[i].nxt){
        int v=e[i].to;
        dfs(v,rt,v);
        q[id[v].size()&1].push({id[v].size(),v});
    }
    for(int i=1;i<n/2;i++){
        int u=q[0].top().se,v=q[1].top().se;q[0].pop(),q[1].pop();
        printf("%d %d\n",id[u].back(),id[v].back());id[u].pop_back(),id[v].pop_back();
        if(id[u].size())q[1].push({id[u].size(),u});
        if(id[v].size())q[0].push({id[v].size(),v});
    }
    printf("%d %d\n",rt,q[1].top().se);
}

int T;
signed main(){
    // freopen("A.in","r",stdin);
    // freopen(".out","w",stdout);
    
    T=1;
    while(T--)work();
}