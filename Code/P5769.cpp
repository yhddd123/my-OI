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
const int maxn=510;

int n,m;
int a[maxn][maxn],b[maxn];
int dis[maxn][maxn];
int head[maxn<<1],tot=1;
struct node{
    int to,nxt,w;
}e[maxn*maxn<<1];
void add(int u,int v,int w){
    e[++tot]={v,head[u],w};head[u]=tot;
    e[++tot]={u,head[v],0};head[v]=tot;
}
int s,t,flow;
int dep[maxn<<1],cur[maxn<<1];
bool bfs(){
    for(int i=1;i<=t;i++)dep[i]=0,cur[i]=head[i];
    queue<int>q;q.push(s);dep[s]=1;
    while(!q.empty()){
        int u=q.front();q.pop();
        for(int i=head[u];i;i=e[i].nxt){
            int v=e[i].to;
            if(!dep[v]&&e[i].w)dep[v]=dep[u]+1,q.push(v);
        }
    }
    return dep[t];
}
int dfs(int u,int res){
    if(u==t)return res;
    int cnt=0;
    for(int i=cur[u];i;i=e[i].nxt){
        int v=e[i].to;cur[u]=i;
        if(dep[v]==dep[u]+1&&e[i].w){
            int out=dfs(v,min(res,e[i].w));
            e[i].w-=out;e[i^1].w+=out;res-=out;cnt+=out;
            if(!res)break;
        }
    }
    return cnt;
}
int dinic(){
    flow=0;while(bfs())flow+=dfs(s,n);
    return flow;
}
int st[maxn],ed[maxn],tim[maxn];
void work(){
    n=read();m=read();
    for(int i=1;i<=n;i++)b[i]=read();
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++)a[i][j]=read();
    }
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++)dis[i][j]=a[i][j]+b[j];
    }
    for(int i=1;i<=n;i++)dis[i][i]=0;
    for(int k=1;k<=n;k++){
        for(int i=1;i<=n;i++){
            for(int j=1;j<=n;j++)dis[i][j]=min(dis[i][j],dis[i][k]+dis[k][j]);
        }
    }
    s=2*m+1;t=2*m+2;
    for(int i=1;i<=m;i++)st[i]=read(),ed[i]=read(),tim[i]=read();
    for(int i=1;i<=m;i++){
        for(int j=1;j<=m;j++)if(i!=j&&tim[i]+a[st[i]][ed[i]]+b[ed[i]]+dis[ed[i]][st[j]]<=tim[j])add(i,j+m,1);
    }
    for(int i=1;i<=m;i++)add(s,i,1),add(i+m,t,1);
    int ans=dinic();
    ans=m-ans;
    printf("%lld\n",ans);
}

int T;
signed main(){
    // freopen("P5769.in","r",stdin);
    // freopen(".out","w",stdout);
    
    T=1;
    while(T--)work();
}