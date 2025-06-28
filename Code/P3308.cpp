// Problem: P3308 [SDOI2014] LIS
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P3308
// Memory Limit: 125 MB
// Time Limit: 1000 ms
// Written by yhm.
// Start codeing:2025-04-08 12:26:12
// 
// Powered by CP Editor (https://cpeditor.org)

#include<bits/stdc++.h>
#define ll long long
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
const int maxn=1410;
const int inf=1e9;
bool mbe;

int n;
int a[maxn],b[maxn],c[maxn];
int f[maxn];
int head[maxn],tot=1;
struct nd{
	int nxt,to,w;
}e[maxn*maxn/8];
void add(int u,int v,int w){
	e[++tot]={head[u],v,w};head[u]=tot;
	e[++tot]={head[v],u,0};head[v]=tot;
}
int s,t;
int rad[maxn],dis[maxn];
queue<int> q;
bool bfs(){
	for(int i=1;i<=t;i++)dis[i]=0,rad[i]=head[i];
	dis[s]=1,q.push(s);
	while(!q.empty()){
		int u=q.front();q.pop();
		for(int i=head[u];i;i=e[i].nxt){
			int v=e[i].to;
			if(e[i].w&&!dis[v]){
				dis[v]=dis[u]+1,q.push(v);
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
		if(e[i].w&&dis[v]==dis[u]+1){
			int out=dfs(v,min(e[i].w,res));
			e[i].w-=out,e[i^1].w+=out;
			res-=out,cnt+=out;
			if(!res)break;
		}
	}
	return cnt;
}
ll dinic(){
	ll flow=0;while(bfs())flow+=dfs(s,inf);
	return flow;
}
bool vis[maxn];
bool check(int u,int v){
	for(int i=1;i<=t;i++)vis[i]=0;
	vis[u]=1,q.push(u);
	while(!q.empty()){
		int u=q.front();q.pop();
		for(int i=head[u];i;i=e[i].nxt){
			int v=e[i].to;
			if(e[i].w&&!vis[v])vis[v]=1,q.push(v);
		}
	}
	return vis[v];
}
int id[maxn];
vector<int> ans;
void work(){
	n=read();ans.clear();
	for(int i=1;i<=n;i++)a[i]=read();
	for(int i=1;i<=n;i++)b[i]=read();
	for(int i=1;i<=n;i++)c[i]=read();
	s=2*n+1,t=2*n+2;
	for(int i=1;i<=t;i++)head[i]=0;tot=1;
	for(int i=1;i<=n;i++)add(i,i+n,b[i]);
	for(int i=1;i<=n;i++){
		f[i]=1;for(int j=1;j<i;j++)if(a[j]<a[i])f[i]=max(f[i],f[j]+1);
		for(int j=1;j<i;j++)if(a[j]<a[i]&&f[i]==f[j]+1)add(j+n,i,inf);
	}
	int mx=0;for(int i=1;i<=n;i++)mx=max(mx,f[i]);
	for(int i=1;i<=n;i++){
		if(f[i]==1)add(s,i,inf);
		if(f[i]==mx)add(i+n,t,inf);
	}
	printf("%lld ",dinic());
	for(int i=1;i<=n;i++)id[i]=i;
	sort(id+1,id+n+1,[&](int u,int v){return c[u]<c[v];});
	for(int i=1;i<=n;i++){
		if(!check(id[i],id[i]+n)){
			ans.pb(id[i]);
			for(int j=2;j<=tot;j+=2)e[j].w+=e[j^1].w,e[j^1].w=0;
			e[id[i]*2].w=0;
			dinic();
		}
	}
	printf("%d\n",ans.size());
	sort(ans.begin(),ans.end());
	for(int u:ans)printf("%d ",u);puts("");
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