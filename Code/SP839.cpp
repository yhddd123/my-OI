// Problem: OPTM - Optimal Marks
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/SP839
// Memory Limit: 1 MB
// Time Limit: 1410 ms
// Written by yhm.
// Start codeing:2024-05-29 12:03:37
// 
// Powered by CP Editor (https://cpeditor.org)

#include<bits/stdc++.h>
#define int long long
#define mod 998244353ll
#define pii pair<int,int>
#define fi first
#define se second
#define mems(x,y) memset(x,y,sizeof(x))
using namespace std;
const int maxn=510;
const int inf=1e18;
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch-48);ch=getchar();}
	return x*f;
}
bool Mbe;

int n,m,a[maxn],b[maxn];
int head[maxn],tot;
struct nd{
	int nxt,to,w;
}e[maxn*30];
void add(int u,int v,int w){
	e[++tot]={head[u],v,w};head[u]=tot;
	e[++tot]={head[v],u,0};head[v]=tot;
}
int dis[maxn],rad[maxn];
bool vis[maxn];
queue<int> q;
int s,t,ans,res,idx;
bool bfs(){
	for(int i=1;i<=t;i++)rad[i]=head[i],dis[i]=inf,vis[i]=0;
	q.push(s);dis[s]=0;vis[s]=1;
	while(!q.empty()){
		int u=q.front();q.pop();vis[u]=0;
		for(int i=head[u];i;i=e[i].nxt){
			int v=e[i].to;
			if(e[i].w&&dis[v]>dis[u]+1){
				dis[v]=dis[u]+1;
				if(!vis[v])vis[v]=1,q.push(v);
			}
		}
	}
	return dis[t]!=inf;
}
int dfs(int u,int res){
	if(u==t)return res;
	int cnt=0;vis[u]=1;
	for(int i=rad[u];i;i=e[i].nxt){
		int v=e[i].to;rad[u]=i;
		if(!vis[v]&&e[i].w&&dis[v]==dis[u]+1){
			int out=dfs(v,min(e[i].w,res));
			cnt+=out,res-=out;
			e[i].w-=out,e[i^1].w+=out;
			if(!res)break;
		}
	}
	vis[u]=0;
	return cnt;
}
int hh[maxn],tt;
void work(){
	n=read();m=read();
	s=n+1,t=n+2;for(int i=1;i<=t;i++)head[i]=0;tot=1;
	for(int i=1;i<=m;i++){
		int u=read(),v=read();
		add(u,v,10000),add(v,u,10000);
	}
	for(int i=1;i<=n;i++)a[i]=b[i]=0;
	int k=read();while(k--){
		int u=read(),v=read();a[u]=v;b[u]=1;
	}
	for(int i=1;i<=t;i++)hh[i]=head[i];tt=tot;
	for(int c=0;c<31;c++){
		for(int i=1;i<=t;i++)head[i]=hh[i];tot=tt;
		for(int i=1;i<=n;i++){
			if(b[i]){
				if(a[i]&(1<<c))add(s,i,inf);
				else add(i,t,inf);
			}
			else add(i,t,1);
		}
		// for(int i=2;i<=tot;i+=2)cout<<e[i^1].to<<" "<<e[i].to<<" "<<e[i].w<<"\n";
		int flow=0;while(bfs())flow+=dfs(s,inf);
		ans+=(flow/10000ll)<<c,res+=(flow%10000ll)<<c;
		for(int i=2;i<=tot;i+=2)e[i].w+=e[i^1].w,e[i^1].w=0;
		for(int i=1;i<=n;i++)if(dis[i]<inf)a[i]|=(1<<c);
	}
	// printf("%lld\n%lld\n",ans,res);
	for(int i=1;i<=n;i++)printf("%lld\n",a[i]);
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
	
	T=read();
	while(T--)work();
}
