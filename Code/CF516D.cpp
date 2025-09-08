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
const int inf=1e12;
bool mbe;

int n,q;
int head[maxn],tot;
struct nd{
    int nxt,to,w;
}e[maxn<<1];
void add(int u,int v,int w){e[++tot]={head[u],v,w};head[u]=tot;}
int dis[maxn],dis1[maxn],s,t;
void dfs(int u,int fa){
    for(int i=head[u];i;i=e[i].nxt){
        int v=e[i].to;if(v==fa)continue;
        dis[v]=dis[u]+e[i].w;dfs(v,u);
    }
}
int id[maxn];
bool vis[maxn];
int f[maxn],siz[maxn];
int fd(int x){
    if(f[x]==x)return x;
    return f[x]=fd(f[x]);
}
void merge(int u,int v){
    u=fd(u),v=fd(v);
    if(u==v)return ;
    f[u]=v,siz[v]+=siz[u];
}
void work(){
    n=read();
    for(int i=1;i<n;i++){
        int u=read(),v=read(),w=read();
        add(u,v,w),add(v,u,w);
    }
    dfs(1,0);
    pii mx={0,0};for(int i=1;i<=n;i++)mx=max(mx,{dis[i],i});
    t=mx.se;dis[t]=0;dfs(t,0);
    mx={0,0};for(int i=1;i<=n;i++)mx=max(mx,{dis[i],i}),dis1[i]=dis[i];
    s=mx.se;dis[s]=0;dfs(s,0);
    // cout<<s<<" "<<t<<"\n";
    for(int i=1;i<=n;i++)dis[i]=max(dis[i],dis1[i]);
    // for(int i=1;i<=n;i++)cout<<dis[i]<<" ";cout<<"\n";
    for(int i=1;i<=n;i++)id[i]=i;
    sort(id+1,id+n+1,[&](int u,int v){return dis[u]<dis[v];});
    q=read();
    while(q--){
        int l=read(),ans=0;
        for(int i=1;i<=n;i++)f[i]=i,siz[i]=vis[i]=0;
        for(int i=n,j=n+1;i;i--){
            while(j>1&&(j>i||dis[id[i]]-dis[id[j-1]]<=l)){
                j--;
                int u=id[j];
                siz[u]=1,vis[u]=1;
                for(int ii=head[u];ii;ii=e[ii].nxt){
                    int v=e[ii].to;
                    if(vis[v])merge(u,v);
                }
                ans=max(ans,siz[fd(u)]);
            }
            siz[fd(id[i])]--,vis[id[i]]=0;
            // cout<<i<<" "<<j<<" "<<ans<<"\n";
        }
        printf("%lld\n",ans);
    }
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