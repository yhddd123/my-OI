// Problem: P1813 拯救小 tim
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P1813
// Memory Limit: 125 MB
// Time Limit: 1000 ms
// Written by yhm.
// Start codeing:2024-09-09 14:25:25
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
using namespace std;
const int maxn=1010;
const int inf=1e18;
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch-48);ch=getchar();}
	return x*f;
}
bool Mbe;

int n,m,s,t;
struct edge{
	int s,t,b,e,c;
}g[maxn<<1];
vector<int> e[maxn],e1[maxn];
int dis[maxn];bool vis[maxn];
priority_queue<pii> qq;
int dis1[maxn][maxn<<2],dis2[maxn][maxn<<2];
void work(){
	n=read();m=read();s=read(),t=read();
	for(int i=1;i<=m;i++)g[i]={read(),read(),read(),read(),read()};
	for(int i=1;i<=m;i++)e[g[i].s].pb(i),e1[g[i].t].pb(i);
	for(int i=1;i<=m;i++){
		for(int j=1;j<=n;j++)dis[j]=inf,vis[j]=0;
		dis[g[i].s]=g[i].b;qq.push({-dis[g[i].s],g[i].s});
		while(!qq.empty()){
			int u=qq.top().se;qq.pop();
			if(vis[u])continue;vis[u]=1;
			for(int j:e[u])if(dis[u]<=g[j].e-g[j].c){
				int v=g[j].t;
				if(dis[v]>max(g[j].b,dis[u])+g[j].c){
					dis[v]=max(g[j].b,dis[u])+g[j].c;
					qq.push({-dis[v],v});
				}
			}
		}
		for(int j=1;j<=n;j++)dis1[j][i]=dis[j];
	}
	
	for(int i=1;i<=m;i++){
		for(int j=1;j<=n;j++)dis[j]=0,vis[j]=0;
		dis[g[i].s]=g[i].b;qq.push({dis[g[i].s],g[i].s});
		while(!qq.empty()){
			int u=qq.top().se;qq.pop();
			// if(i==8)cout<<u<<" "<<dis[u]<<"\n";
			if(vis[u])continue;vis[u]=1;
			for(int j:e1[u])if(dis[u]>=g[j].b+g[j].c){
				int v=g[j].s;
				if(dis[v]<min(g[j].e,dis[u])-g[j].c){
					dis[v]=min(g[j].e,dis[u])-g[j].c;
					qq.push({dis[v],v});
				}
			}
		}
		for(int j=1;j<=n;j++)dis2[j][i]=dis[j];
	}
	
	int ans=inf;
	for(int i=1;i<=m;i++)if(dis1[t][i]<=inf/n&&dis2[s][i]){
		ans=min(ans,dis1[t][i]-dis2[s][i]);
		// cout<<i<<" "<<dis1[t][i]<<" "<<dis2[s][i]<<"\n";
	}
	if(ans>inf/n)puts("Impossible");
	else printf("%lld\n",ans);
}

// \
444

bool Med;
int T;
signed main(){
//	freopen("path.in","r",stdin);
//	freopen("path.out","w",stdout);
	
//	ios::sync_with_stdio(0);
//	cin.tie(0);cout.tie(0);
	
//	cerr<<(&Mbe-&Med)/1048576.0<<" MB\n";
	
	T=1;
	while(T--)work();
}
