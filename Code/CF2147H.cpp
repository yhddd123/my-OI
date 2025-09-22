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
const int maxn=55;
const int inf=1e9;
bool mbe;

int n,m;
int head[maxn],tot=1;
struct nd{
    int nxt,to,w;
}e[maxn*maxn<<1];
void add(int u,int v,int w){
    e[++tot]={head[u],v,w};head[u]=tot;
    e[++tot]={head[v],u,0};head[v]=tot;
}
int id[maxn];
int s,t;
int dis[maxn],rad[maxn];bool vis[maxn];
queue<int> q;
bool bfs(){
    for(int i=1;i<=n;i++)dis[i]=0,rad[i]=head[i],vis[i]=0;
    dis[s]=1;q.push(s);
    while(!q.empty()){
        int u=q.front();q.pop();
        for(int i=head[u];i;i=e[i].nxt){
            int v=e[i].to;
            if(e[i].w&&!dis[v])dis[v]=dis[u]+1,q.push(v);
        }
    }
    return dis[t];
}
int dfs(int u,int res){
    if(u==t)return res;
    int cnt=0;vis[u]=1;
    for(int &i=rad[u];i;i=e[i].nxt){
        int v=e[i].to;
        if(!vis[v]&&dis[v]==dis[u]+1){
            int out=dfs(v,min(e[i].w,res));
            res-=out,cnt+=out;
            e[i].w-=out,e[i^1].w+=out;
            if(!res)break;
        }
    }
    vis[u]=0;return cnt;
}
int mp[maxn][maxn];
void sovle(int l,int r){
    if(l==r)return ;
    s=id[l],t=id[l+1];int ss=s,tt=t;
    for(int i=2;i<=tot;i+=2)e[i].w+=e[i^1].w,e[i^1].w=0;
    int ans=0;while(bfs())ans+=dfs(s,inf);
    mp[s][t]=mp[t][s]=ans;
    // cout<<s<<" "<<t<<" "<<ans<<"\n";
    vector<int> tmp1,tmp2;
    for(int i=l;i<=r;i++){
        if(dis[id[i]])tmp1.push_back(id[i]);
        else tmp2.push_back(id[i]);
    }
    int p=l,mid=l;for(int i:tmp1)id[p++]=i;
    mid=p-1;for(int i:tmp2)id[p++]=i;
    for(int i=0;i<=n;i++)if(dis[i]){
        for(int j=0;j<=n;j++)if(!dis[j]){
            mp[i][j]=mp[j][i]=min(mp[i][j],ans);
        }
    }
    sovle(l,mid),sovle(mid+1,r);
}
int ans[maxn];
bool g[maxn][maxn];
int d(int u){
    int res=0;for(int i=1;i<=n;i++)if(g[u][i])res++;
    return res;
}
void dfs(int p){
    for(int i=1;i<p;i++)if(d(id[i])&1){swap(id[i],id[p]);break;}
    // cout<<p<<" "<<id[p]<<" "<<d(id[p])<<"\n";
    if(!(d(id[p])&1)){
        for(int i=1;i<=p;i++)ans[id[i]]=1;
        return ;
    }
    vector<int> son;
    for(int i=1;i<p;i++)if(g[id[p]][id[i]])son.pb(id[i]);
    for(int v1:son){
    	g[v1][id[p]]^=1;
        for(int v2:son)if(v1!=v2)g[v1][v2]^=1;
    }
    dfs(p-1);
    for(int v1:son){
    	g[v1][id[p]]^=1;
        for(int v2:son)if(v1!=v2)g[v1][v2]^=1;
    }
    int num=0;
    for(int v:son)num+=(ans[v]==1);
    if(num&1)ans[id[p]]=2;
    else ans[id[p]]=1;
}
void work(){
    n=read();m=read();
    for(int i=1;i<=n;i++)head[i]=0;tot=1;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++)g[i][j]=0;
    }
    for(int i=1;i<=m;i++){
        int u=read(),v=read(),w=read();
        add(u,v,w),add(v,u,w);
        if(w&1)g[u][v]=1,g[v][u]=1;
    }
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++)mp[i][j]=0;
    }
    for(int i=1;i<=n;i++)id[i]=i;
    sovle(1,n);
    int g=0;for(int i=1;i<=n;i++){
        for(int j=i;j<=n;j++)g=__gcd(g,mp[i][j]);
    }
    if(g!=1){
        printf("1\n%d\n",n);
        for(int i=1;i<=n;i++)printf("%d ",i);puts("");
        return ;
    }
    for(int i=1;i<=n;i++)id[i]=i;
    dfs(n);
    // for(int i=1;i<=n;i++)cout<<ans[i]<<" ";cout<<"\n";
    int num=0;for(int i=1;i<=n;i++)num+=(ans[i]==1);
    printf("2\n%d\n",num);
    for(int i=1;i<=n;i++)if(ans[i]==1)printf("%d ",i);puts("");
    printf("%d\n",n-num);
    for(int i=1;i<=n;i++)if(ans[i]==2)printf("%d ",i);puts("");
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