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

int n,m,k;
int head[maxn],tot;
struct nd{
    int nxt,to,l,r;
}e[maxn<<1];
void add(int u,int v,int l,int r){e[++tot]={head[u],v,l,r};head[u]=tot;}
int dis[maxn],dis1[maxn];
bool vis[maxn];
priority_queue<pii> q;
void work(){
    n=read();m=read();k=read();
    for(int i=1;i<=n;i++)head[i]=0;tot=0;
    for(int i=1;i<=m;i++){
        int u=read(),v=read(),l=read(),r=read();
        add(u,v,l,r),add(v,u,l,r);
    }
    for(int i=1;i<=n;i++)dis[i]=inf,vis[i]=0;
    dis[k]=0,q.push({0,k});
    while(!q.empty()){
        int u=q.top().se;q.pop();
        if(vis[u])continue;vis[u]=1;
        for(int i=head[u];i;i=e[i].nxt){
            int v=e[i].to;
            if(dis[v]>dis[u]+e[i].r){
                dis[v]=dis[u]+e[i].r;
                q.push({-dis[v],v});
            }
        }
    }
    for(int i=1;i<=n;i++)dis1[i]=inf,vis[i]=0;
    dis1[1]=-dis[1];q.push({-dis1[1],1});
    while(!q.empty()){
        int u=q.top().se;q.pop();
        // cout<<u<<" "<<dis1[u]<<"\n";
        if(vis[u]||dis1[u]>=dis[u])continue;vis[u]=1;
        for(int i=head[u];i;i=e[i].nxt){
            int v=e[i].to;
            if(!vis[v]&&dis1[v]>max(-dis[v],dis1[u]+e[i].l)){
                dis1[v]=max(-dis[v],dis1[u]+e[i].l);
                q.push({-dis1[v],v});
            }
        }
    }
    // for(int i=1;i<=n;i++)cout<<dis[i]<<" ";cout<<"\n";
    // for(int i=1;i<=n;i++)cout<<dis1[i]<<" ";cout<<"\n";
    puts(dis1[n]<dis[n]?"YES":"NO");
}

bool med;
int T;
signed main(){
    // freopen(".in","r",stdin);
    // freopen(".out","w",stdout);
    
    // cerr<<(&mbe-&med)/1024.0/1024.0<<"\n";
    
    T=read();
    while(T--)work();
}