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

int n,m,q;
vector<pii> e[maxn];
int dfn[maxn],lw[maxn],idx;
int st[maxn],tp;
int scc[maxn],scct;
vector<int> id[maxn];
void tar(int u){
    dfn[u]=lw[u]=++idx;st[++tp]=u;
    for(auto [v,w]:e[u]){
        if(!dfn[v])tar(v),lw[u]=min(lw[u],lw[v]);
        else if(!scc[v])lw[u]=min(lw[u],dfn[v]);
    }
    if(lw[u]==dfn[u]){
        scc[st[tp]]=++scct;id[scct].pb(st[tp]);
        while(st[tp--]!=u)scc[st[tp]]=scct,id[scct].pb(st[tp]);
    }
}
bool vis[maxn];
int dep[maxn];
int g[maxn];
void work(){
    n=read();m=read();
    for(int i=1;i<=m;i++){
        int u=read(),v=read(),w=read();
        e[u].pb({v,w});
    }
    for(int i=1;i<=n;i++)if(!dfn[i])tar(i);
    for(int i=1;i<=scct;i++){
        vector<tuple<int,int,int>> edge;
        auto ddfs=[&](auto &&self,int u)->void{
            vis[u]=1;
            for(auto[v,w]:e[u]){
                if(scc[v]!=i)continue;
                if(!vis[v])dep[v]=dep[u]+w,self(self,v);
                else edge.pb({u,v,w});
            }
		};
        ddfs(ddfs,id[i].front());
        for(auto[u,v,w]:edge){
            g[i]=__gcd(g[i],abs(dep[u]-dep[v]+w));
        }
        // cout<<i<<" "<<g[i]<<"\n";
        // for(int u:id[i])cout<<u<<" ";cout<<"\n";
    }
    q=read();
    while(q--){
        int u=read(),s=read(),t=read();s=t-s;
        if(s%__gcd(g[scc[u]],t)==0)puts("YES");
        else puts("NO");
    }
}

int T;
signed main(){
    // freopen("A.in","r",stdin);
    // freopen(".out","w",stdout);
    
    T=1;
    while(T--)work();
}