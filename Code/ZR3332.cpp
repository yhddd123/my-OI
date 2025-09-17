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
const int inf=1e18;
bool mbe;

int n,m;
int a[maxn],b[maxn],c[maxn];
int dis[maxn];
bool vis[maxn];
vector<pii> e[maxn];
priority_queue<pii> q;
void work(){
    n=read();m=read();
    for(int i=2;i<n;i++)a[i]=read(),b[i]=read(),c[i]=read();
    for(int i=1;i<=m;i++){
        int u=read(),v=read(),w=read();
        e[u].pb({v,w});
    }
    for(int i=1;i<=n;i++)dis[i]=inf;
    dis[1]=0,q.push({0,1});
    while(!q.empty()){
        int u=q.top().se;q.pop();
        if(vis[u])continue;vis[u]=1;
        if(u!=1&&u!=n){
            if(dis[u]%c[u]<a[u])dis[u]=dis[u]/c[u]*c[u]+a[u];
            else if(dis[u]%c[u]>b[u])dis[u]=(dis[u]/c[u]+1)*c[u]+a[u];
        }
        for(auto[v,w]:e[u]){
            if(!vis[v]&&dis[v]>dis[u]+w){
                dis[v]=dis[u]+w,q.push({-dis[v],v});
            }
        }
    }
    printf("%lld\n",dis[n]);
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