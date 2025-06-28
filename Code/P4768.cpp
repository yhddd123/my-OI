// Problem: P4768 [NOI2018] 归程
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P4768
// Memory Limit: 512 MB
// Time Limit: 4000 ms
// Written by yhm.
// Start codeing:2025-05-14 19:06:10
// 
// Powered by CP Editor (https://cpeditor.org)

#include<bits/stdc++.h>
// #define int long long
#define mod 998244353ll
#define pii pair<int,int>
#define fi first
#define se second
#define pb push_back
#define mkp make_pair
#define mems(a,x) memset((a),(x),sizeof(a))
using namespace std;
inline int read(){
	int x=0,fl=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')fl=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
	return x*fl;
}
const int maxn=400010;
const int inf=1e9;
bool mbe;

int n,m,idx,q,op,mx,ans;
int head[maxn],tot;
struct nd{
	int nxt,to,w;
}e[maxn<<1];
void add(int u,int v,int w){e[++tot]={head[u],v,w};head[u]=tot;}
tuple<int,int,int> edge[maxn];
int f[maxn],val[maxn];
int fd(int x){
	if(f[x]==x)return x;
	return f[x]=fd(f[x]);
}
vector<int> g[maxn];
int dis[maxn];
bool vis[maxn];
priority_queue<pii> qq;
int to[maxn][19];
void dfs(int u,int fa){
	to[u][0]=fa;
	for(int i=1;i<=18;i++)to[u][i]=to[to[u][i-1]][i-1];
	for(int v:g[u])dfs(v,u),dis[u]=min(dis[u],dis[v]);
}
void work(){
	n=read();m=read();idx=n;ans=0;
	for(int i=1;i<=n;i++)head[i]=0;tot=0;
	for(int i=1;i<=m;i++){
		int u=read(),v=read(),w=read();
		add(u,v,w),add(v,u,w);
		w=read();edge[i]={w,u,v};
	}
	sort(edge+1,edge+m+1),reverse(edge+1,edge+m+1);
	for(int i=1;i<=n;i++)f[i]=i,g[i].clear();
	for(int i=1;i<=m;i++){
		auto[w,u,v]=edge[i];
		u=fd(u),v=fd(v);
		if(u==v)continue;
		++idx;f[idx]=idx,val[idx]=w;
		f[u]=f[v]=idx;g[idx].clear(),g[idx].pb(u),g[idx].pb(v);
	}
	for(int i=1;i<=idx;i++)dis[i]=inf,vis[i]=0;
	dis[1]=0,qq.push({0,1});
	while(!qq.empty()){
		int u=qq.top().se;qq.pop();
		if(vis[u])continue;vis[u]=1;
		for(int i=head[u];i;i=e[i].nxt){
			int v=e[i].to;
			if(dis[v]>dis[u]+e[i].w){
				dis[v]=dis[u]+e[i].w;
				qq.push({-dis[v],v});
			}
		}
	}
	dfs(idx,0);
	q=read(),op=read(),mx=read();
	while(q--){
		int u=(read()+op*ans-1)%n+1,v=(read()+op*ans)%(mx+1);
		for(int i=18;~i;i--)if(val[to[u][i]]>v)u=to[u][i];
		printf("%d\n",ans=dis[u]);
	}
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