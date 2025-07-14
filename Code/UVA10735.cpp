#include<bits/stdc++.h>
#define int long long
#define mod 998244353
#define pii pair<int,int>
#define mems(x,y) memset(x,y,sizeof x)
using namespace std;
const int maxn=110;
const int inf=1e18;
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch-48);ch=getchar();}
	return x*f;
}
bool Mbe;

int n,m;
int head[maxn],tot=1;
struct edgend{
	int nxt,to,w;
}e[maxn*20];
void add(int u,int v,int w){
	e[++tot]={head[u],v,w};head[u]=tot;
	e[++tot]={head[v],u,0};head[v]=tot;
}
int d[maxn];
int s,t,idx;
namespace dinic{
	int flow;
	queue<int> q;
	int dis[maxn],rad[maxn];
	bool bfs(){
		for(int i=1;i<=t;i++)dis[i]=rad[i]=0;
		dis[s]=1;q.push(s);
		while(!q.empty()){
			int u=q.front();q.pop();
			rad[u]=head[u];
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
		flow=0;
		while(bfs())flow+=dfs(s,inf);
		return flow;
	}
}
vector<int> g[maxn];
int st[maxn*5],tp;
void dfs(int u){
	while(g[u].size()){
		int v=g[u].back();
		g[u].pop_back();
		dfs(v);
	}
	st[++tp]=u;
}
char op[2];
void work(){
	n=read();m=read();s=n+1,t=n+2;
	mems(head,0);tot=1;mems(d,0);
	for(int i=1;i<=n;i++)g[i].clear();
	for(int i=1;i<=m;i++){
		int u=read(),v=read();
		scanf("%s",op+1);
		d[u]++,d[v]--;
		if(op[1]=='U')add(u,v,1);
		else g[u].push_back(v);
	}
	int num=0;
	for(int i=1;i<=n;i++){
		if(abs(d[i])&1){puts("No euler circuit exist\n");return ;}
		d[i]/=2;
		if(d[i]>0)add(s,i,d[i]),num+=d[i];
		else add(i,t,-d[i]);
	}
	if(num!=dinic::calc()){puts("No euler circuit exist\n");return ;}
	for(int i=2;i<=tot;i+=2){
		int u=e[i^1].to,v=e[i].to;
		if(u==s||v==t)continue;
		if(e[i^1].w)g[v].push_back(u);
		else g[u].push_back(v);
	}
	for(int i=1;i<=n;i++){
		m-=g[i].size();
//		for(int j:g[i])cout<<i<<" "<<j<<"\n";
	}
	assert(!m);
	tp=0;dfs(1);
	reverse(st+1,st+tp+1);
	for(int i=1;i<=tp;i++)printf("%lld ",st[i]);
	puts("\n");
}

bool Med;
int T;
signed main(){
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
	
//	ios::sync_with_stdio(0);
//	cin.tie(0);cout.tie(0);
	
//	cerr<<(&Mbe-&Med)/1048576.0<<" MB\n";
	
	T=read();
	while(T--){
		work();
	}
}
