#include<bits/stdc++.h>
#include <cstdio>
#define int long long
#define mod 998244353ll
#define pii pair<int,int>
#define fi first
#define se second
#define pb push_back
using namespace std;
static char buf[1000000],*p1=buf,*p2=buf;
#define getchar() p1==p2&&(p2=(p1=buf)+fread(buf,1,1000000,stdin),p1==p2)?EOF:*p1++
inline int read(){int x=0,f=1;char c=getchar();while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}while(c>='0'&&c<='9'){x=(x<<3)+(x<<1)+c-48;c=getchar();}return x*f;}
inline void write(int x){static char buf[20];static int len=-1;if(x<0)putchar('-'),x=-x;do buf[++len]=x%10,x/=10;while(x);while(len>=0)putchar(buf[len--]+48);}
const int maxn=500010;
const int inf=1e9;

int n,m,a[maxn],ans;
int head[maxn],tot;
struct nd{
    int nxt,to,w;
}e[maxn<<2];
void add(int u,int v,int w){e[++tot]={head[u],v,w};head[u]=tot;}
int dis[maxn],pre[maxn];
bool vis[maxn];
int f[maxn];
int fd(int x){
    if(f[x]==x)return x;
    return f[x]=fd(f[x]);
}
void work(){
    n=read();m=read();ans=0;
    for(int i=1;i<=n;i++)a[i]=read();
    for(int i=1;i<=n;i++)head[i]=0;tot=0;
    for(int i=1;i<=m;i++){
        int u=read(),v=read(),w=read();
        add(u,v,w),add(v,u,w);
    }
    priority_queue<pii> q;
    for(int i=1;i<=n;i++)dis[i]=a[i],pre[i]=i,vis[i]=0,q.push({-dis[i],i});
    while(!q.empty()){
        int u=q.top().se;q.pop();
        if(vis[u])continue;vis[u]=1;
        for(int i=head[u];i;i=e[i].nxt){
            int v=e[i].to;
            if(dis[v]>dis[u]+e[i].w){
                dis[v]=dis[u]+e[i].w;pre[v]=pre[u];
                q.push({-dis[v],v});
            }
        }
    }
    // for(int i=1;i<=n;i++)cout<<pre[i]<<" ";cout<<"\n";
    vector<tuple<int,int,int>> edge;
    for(int i=1;i<=n;i++)if(pre[i]!=i)ans+=dis[i]+a[i];
    for(int i=1;i<=tot;i+=2){
        int u=e[i].to,v=e[i+1].to,w=e[i].w;
        if(pre[u]!=pre[v])edge.pb({dis[u]+dis[v]+w,pre[u],pre[v]});
    }
    sort(edge.begin(),edge.end());
    for(int i=1;i<=n;i++)f[i]=i;
    for(auto[w,u,v]:edge){
        // cout<<u<<" "<<v<<" "<<w<<"\n";
        if(fd(u)!=fd(v)){
            ans+=w;
            f[fd(u)]=fd(v);
        }
    }
    int mn=a[1];for(int i=2;i<=n;i++)mn=min(mn,a[i]);
    for(int i=1;i<=n;i++)ans-=a[i];ans+=mn;
    write(ans),puts("");
}

int T;
signed main(){
    // freopen("A.in","r",stdin);
    // freopen("A.out","w",stdout);
    
    T=read();
    while(T--)work();
}