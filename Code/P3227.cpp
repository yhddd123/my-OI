#include<bits/stdc++.h>
#define int long long
#define mod 998244353
#define pii pair<int,int>
#define mems(x,y) memset(x,y,sizeof x)
using namespace std;
const int maxn=70010;
const int inf=1e18;
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch-48);ch=getchar();}
	return x*f;
}
bool Mbe;

int n,m,h,d;
int head[maxn],tot=1;
struct edgend{
	int nxt,to,w;
}e[maxn*10];
void add(int u,int v,int w){
	e[++tot]={head[u],v,w};head[u]=tot;
	e[++tot]={head[v],u,0};head[v]=tot;
}
int s,t,idx;
namespace dinic{
	int flow;
	queue<int> q;
	int dis[maxn],rad[maxn];
	bool bfs(){
		for(int i=1;i<=t;i++)dis[i]=rad[i]=0;
		dis[s]=1;q.push(s);
		while(!q.empty()){
			int u=q.front();q.pop();rad[u]=head[u];
			for(int i=head[u];i;i=e[i].nxt){
				int v=e[i].to;
				if(!dis[v]&&e[i].w){
					dis[v]=dis[u]+1;
					q.push(v);
				}
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
				int out=dfs(v,min(res,e[i].w));
				res-=out;cnt+=out;
				e[i].w-=out;e[i^1].w+=out;
				if(!res)break;
			}
		}
		return cnt;
	}
	int calc(){
		while(bfs())flow+=dfs(s,inf);
		return flow;
	}
}
int id(int u,int v,int w){
	return n*m*(w-1)+m*(u-1)+v;
}
void work(){
	n=read();m=read();h=read();d=read();
	s=n*m*h+1,t=n*m*h+2;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			add(s,id(i,j,1),inf);
		}
	}
	for(int k=1;k<=h;k++){
		for(int i=1;i<=n;i++){
			for(int j=1;j<=m;j++){
				int w=read();
				if(k==h)add(id(i,j,k),t,w);
				else add(id(i,j,k),id(i,j,k+1),w);
				if(k>d){
					if(i>1)add(id(i,j,k),id(i-1,j,k-d),inf);
					if(i<n)add(id(i,j,k),id(i+1,j,k-d),inf);
					if(j>1)add(id(i,j,k),id(i,j-1,k-d),inf);
					if(j<m)add(id(i,j,k),id(i,j+1,k-d),inf);
				}
			}
		}
	}
//	for(int i=2;i<=tot;i+=2)cout<<e[i^1].to<<" "<<e[i].to<<" "<<e[i].w<<"\n";
	printf("%lld\n",dinic::calc());
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
