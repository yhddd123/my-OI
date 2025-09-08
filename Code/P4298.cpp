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
const int maxn=110;
const int inf=1e9;
bool mbe;

int n,m,ans;
bitset<maxn> f[maxn];
int head[maxn<<1],tot=1;
struct nd{
    int nxt,to,w;
}e[maxn*maxn<<1];
void add(int u,int v,int w){
    // cout<<u<<" "<<v<<" "<<w<<"\n";
    e[++tot]={head[u],v,w};head[u]=tot;
    e[++tot]={head[v],u,0};head[v]=tot;
}
int s,t,flow;
int rad[maxn<<1],dis[maxn<<1];
queue<int> q;
bool bfs(){
	for(int i=1;i<=t;i++)rad[i]=head[i],dis[i]=0;
	dis[s]=1;q.push(s);
	while(!q.empty()){
		int u=q.front();q.pop();
		for(int i=head[u];i;i=e[i].nxt){
			int v=e[i].to;
			if(!dis[v]&&e[i].w)dis[v]=dis[u]+1,q.push(v);
		}
	}
	return dis[t];
}
int dfs(int u,int res){
	if(u==t)return res;
	int cnt=0;
	for(int i=rad[u];i;i=e[i].nxt){
		int v=e[i].to;rad[u]=i;
		if(dis[v]==dis[u]+1&&e[i].w){
			int out=dfs(v,min(e[i].w,res));
			e[i].w-=out;e[i^1].w+=out;
			cnt+=out;res-=out;
			if(!res)break;
		}
	}
	return cnt;
}
int dinic(){
    flow=0;while(bfs())flow+=dfs(s,inf);
    return flow;
}
bool vis[maxn<<1];
void init(){
	// for(int i=1;i<=n;i++)cout<<vis[i];cout<<"\n";
    for(int i=1;i<=t;i++)head[i]=0;tot=1;
    for(int i=1;i<=n;i++)if(!vis[i]){
        add(s,i,1),add(i+n,t,1);
        for(int j=1;j<=n;j++)if(f[i][j]&&!vis[j])add(i,j+n,1);
    }
}
void dfs(int u){
    vis[u]=1;
    for(int i=head[u];i;i=e[i].nxt){
        int v=e[i].to;if(vis[v]||v>=s)continue;
        if(!e[i].w)dfs(v);
    }
}
void work(){
    n=read();m=read();
    for(int i=1;i<=m;i++){
        int u=read(),v=read();
        f[u][v]=1;
    }
    for(int i=1;i<=n;i++)f[i][i]=1;
    for(int k=1;k<=n;k++){
        for(int i=1;i<=n;i++)if(f[i][k])f[i]|=f[k];
    }
    for(int i=1;i<=n;i++)f[i][i]=0;
    s=2*n+1,t=2*n+2;
    init();
    printf("%d\n",ans=n-dinic());
    for(int i=head[t];i;i=e[i].nxt){
        int v=e[i].to;if(!e[i].w)dfs(v);
    }
    for(int i=1;i<=n;i++)putchar((vis[i+n]&&!vis[i])?'1':'0');puts("");
    for(int i=1;i<=n;i++)vis[i]=0;
    for(int i=1;i<=n;i++){
    	int nn=n;
        vis[i]=1,nn--;for(int j=1;j<=n;j++)if(f[j][i]||f[i][j])vis[j]=1,nn--;
        init();
        putchar(nn-dinic()==ans-1?'1':'0');
        vis[i]=0;for(int j=1;j<=n;j++)if(f[j][i]||f[i][j])vis[j]=0;
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