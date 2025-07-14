#include<bits/stdc++.h>
#define int long long
#define mod 998244353
#define pii pair<int,int>
#define mems(x,y) memset(x,y,sizeof x)
using namespace std;
const int maxn=200010;
const int inf=1e18;
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch-48);ch=getchar();}
	return x*f;
}
bool Mbe;

int n,m,ans;
int a[maxn],b[maxn],c[maxn],d[maxn];
int num[maxn];
int head[maxn],tot=1;
struct edgend{
	int nxt,to,w,c;
}e[maxn<<1];
void add(int u,int v,int w,int c){
	e[++tot]={head[u],v,w,c};head[u]=tot;
	e[++tot]={head[v],u,0,-c};head[v]=tot;
}
int s,t,idx;
namespace dinic{
	int flow,cost;
	queue<int> q;
	int dis[maxn],rad[maxn];
	bool vis[maxn];
	bool bfs(){
		for(int i=1;i<=t;i++)dis[i]=inf,rad[i]=vis[s]=0;
		dis[s]=0;q.push(s);vis[s]=1;
		while(!q.empty()){
			int u=q.front();q.pop();vis[u]=0;
			rad[u]=head[u];
			for(int i=head[u];i;i=e[i].nxt){
				int v=e[i].to;
				if(dis[v]>dis[u]+e[i].c&&e[i].w){
					dis[v]=dis[u]+e[i].c;
					if(!vis[v])q.push(v),vis[v]=1;
				}
			}
		}
		return dis[t]<inf;
	}
	int dfs(int u,int res){
		if(u==t)return res;
		int cnt=0;vis[u]=1;
		for(int i=rad[u];i;i=e[i].nxt){
			int v=e[i].to;rad[u]=i;
			if(!vis[v]&&dis[v]==dis[u]+e[i].c&&e[i].w){
				int out=dfs(v,min(res,e[i].w));
				res-=out;cnt+=out;
				e[i].w-=out;e[i^1].w+=out;
				cost+=out*e[i].c;
				if(!res)break;
			}
		}
		vis[u]=0;
		return cnt;
	}
	void calc(){
		flow=0;
		while(bfs())flow+=dfs(s,inf);
		return ;
	}
}
void work(){
	n=read();m=read();s=n+m+1,t=n+m+2;
	for(int i=1;i<=n;i++)a[i]=read(),b[i]=read(),c[i]=read(),d[i]=read();
	for(int i=1;i<=m;i++){
		int u=read(),v=read();
		add(s,i+n,1,0);add(i+n,u,1,0);add(i+n,v,1,0);
		num[u]++,num[v]++;b[u]++;b[v]++;
	}
	for(int i=1;i<=n;i++)ans+=c[i]*a[i]*a[i]+d[i]*b[i]*b[i];
	for(int i=1;i<=n;i++){
		for(int j=1;j<=num[i];j++)add(i,t,1,c[i]+d[i]+2*c[i]*a[i]-2*d[i]*b[i]),a[i]++,b[i]--;
	}
	dinic::calc();
	printf("%lld\n",ans+dinic::cost);
}

// \
444

bool Med;
int T;
signed main(){
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
	
//	ios::sync_with_stdio(0);
//	cin.tie(0);cout.tie(0);
	
//	cerr<<(&Mbe-&Med)/1048576.0<<" MB\n";
	
	T=1;
	while(T--)work();
}
