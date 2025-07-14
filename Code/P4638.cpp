// Problem: P4638 [SHOI2011] 银行家
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P4638
// Memory Limit: 125 MB
// Time Limit: 5000 ms
// Written by yhm.
// Start codeing:2024-08-07 20:37:13
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

int n,m;
int head[maxn],tot=1;
struct nd{
	int nxt,to,w;
}e[maxn];
void add(int u,int v,int w){
	// cout<<u<<" "<<v<<" "<<w<<"\n";
	e[++tot]={head[u],v,w};head[u]=tot;
	e[++tot]={head[v],u,0};head[v]=tot;
}
int s,t,flow;
int dis[maxn],rad[maxn];
queue<int> q;
bool bfs(){
	for(int i=1;i<=t;i++)dis[i]=0,rad[i]=head[i];
	dis[s]=1,q.push(s);
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
	int cnt=0;
	for(int i=rad[u];i;i=e[i].nxt){
		int v=e[i].to;rad[u]=i;
		if(e[i].w&&dis[v]==dis[u]+1){
			int out=dfs(v,min(e[i].w,res));
			res-=out,cnt+=out;
			e[i].w-=out,e[i^1].w+=out;
			if(!res)break;
		}
	}
	return cnt;
}
int vis[maxn];
void work(){
	m=read();n=read();s=n+m+1,t=n+m+2;
	for(int i=1;i<=m;i++){
		int num=read();
		add(s,i,num);
	}
	for(int i=1;i<=n;i++){
		int k=read();
		while(k--){
			int u=read();
			if(!vis[u]){
				vis[u]=i;
				add(u,i+m,inf);
			}
			else{
				add(vis[u]+m,i+m,inf);
				vis[u]=i;
			}
		}
		int num=read();
		add(i+m,t,num);
	}
	while(bfs())flow+=dfs(s,inf);
	printf("%lld\n",flow);
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
