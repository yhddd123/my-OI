// Problem: P3440 [POI2006] SZK-Schools
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P3440
// Memory Limit: 125 MB
// Time Limit: 1000 ms
// Written by yhm.
// Start codeing:2024-10-18 10:17:53
// 
// Powered by CP Editor (https://cpeditor.org)

#include<bits/stdc++.h>
#define int long long
#define mod 998244353ll
#define pii pair<int,int>
#define fi first
#define se second
#define mems(x,y) memset(x,y,sizeof(x))
#define pb push_back
#define db double
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

int n;
int s,t,flow,ans;
struct nd{
	int nxt,to,w,c;
}e[maxn<<1];
int head[maxn],tot=1;
void add(int u,int v,int w,int c){
	e[++tot]={head[u],v,w,c};head[u]=tot;
	e[++tot]={head[v],u,0,-c};head[v]=tot;
}
queue<int> q;
int dis[maxn],rad[maxn];
bool vis[maxn];
bool bfs(){
	for(int i=1;i<=t;i++)dis[i]=inf,vis[i]=0,rad[i]=head[i];
	q.push(s);dis[s]=0;vis[s]=1;
	while(!q.empty()){
		int u=q.front();q.pop();vis[u]=0;
		for(int i=head[u];i;i=e[i].nxt){
			int v=e[i].to;
			if(e[i].w&&dis[v]>dis[u]+e[i].c){
				dis[v]=dis[u]+e[i].c;
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
		if(e[i].w&&dis[v]==dis[u]+e[i].c&&!vis[v]){
			int out=dfs(v,min(e[i].w,res));
			res-=out;cnt+=out;
			e[i].w-=out;e[i^1].w+=out;
			ans+=out*e[i].c;
			if(!res)break;
		}
	}
	vis[u]=0;
	return cnt;
}
void work(){
	n=read();s=2*n+1,t=2*n+2;
	for(int i=1;i<=n;i++){
		add(s,i,1,0),add(i+n,t,1,0);
		int id=read(),l=read(),r=read(),k=read();
		for(int j=l;j<=r;j++)add(i,j+n,1,k*abs(id-j));
	}
	while(bfs())flow+=dfs(s,inf);
	if(flow!=n)puts("NIE");
	else printf("%lld\n",ans);
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
