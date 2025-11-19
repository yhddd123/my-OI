// Problem: P4716 【模板】最小树形图
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P4716
// Memory Limit: 250 MB
// Time Limit: 1000 ms
// Written by yhm.
// Start codeing:2025-11-18 17:48:06
// 
// Powered by CP Editor (https://cpeditor.org)

#include<bits/stdc++.h>
// #define int long long
#define mod 998244353ll
#define pii pair<int,int>
#define fi first
#define se second
#define pb push_back
#define db long double
#define mems(a,x) memset((a),(x),sizeof(a))
using namespace std;
inline int read(){
	int x=0,fl=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')fl=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
	return x*fl;
}
const int maxn=200010;
const int inf=1e9;
bool mbe;

int n,m,rt;
struct bcj{
	int f[maxn];
	int fd(int x){
		if(f[x]==x)return x;
		return f[x]=fd(f[x]);
	}
	void merge(int u,int v){f[fd(u)]=fd(v);}
	void init(){
		for(int i=1;i<=n;i++)f[i]=i;
	}
}f1,f2;
priority_queue<pii,vector<pii>,greater<pii>> q[maxn];
int tag[maxn];
void merge(int u,int v){
	if(q[u].size()<q[v].size())swap(q[u],q[v]),swap(tag[u],tag[v]);
	while(q[v].size()){
		pii p=q[v].top();q[v].pop();
		q[u].push({p.fi+tag[v]-tag[u],p.se});
	}
}
int fa[maxn],val[maxn],ans;
vector<int> e[maxn];
bool vis[maxn];
void dfs(int u){
	vis[u]=1;
	for(int v:e[u])if(!vis[v])dfs(v);
}
void work(){
	n=read();m=read();rt=read();
	for(int i=1;i<=m;i++){
		int u=read(),v=read(),w=read();
		e[u].pb(v);
		if(v!=rt)q[v].push({w,u});
	}
	dfs(rt);
	for(int i=1;i<=n;i++)if(!vis[i]){puts("-1");return ;}
	f1.init(),f2.init();
	queue<int> qq;for(int i=1;i<=n;i++)if(i!=rt)qq.push(i);
	while(!qq.empty()){
		int u=qq.front();qq.pop();
		u=f1.fd(u);
		while(q[u].size()&&f1.fd(q[u].top().se)==u)q[u].pop();
		if(!q[u].size())break;
		auto[w,v]=q[u].top();w+=tag[u];v=f1.fd(v);
		// cout<<u<<" "<<v<<"\n";
		ans+=w;
		if(f2.fd(u)!=f2.fd(v)){
			fa[u]=v,val[u]=w;
			f2.merge(u,v);
		}
		else{
			qq.push(u);
			tag[u]-=w;
			while(v!=u){
				tag[v]-=val[v];merge(u,v);
				f1.merge(v,u);
				v=f1.fd(fa[v]);
			}
		}
	}
	printf("%d\n",ans);
}

bool med;
int T;
signed main(){
	// freopen(".in","r",stdin);
	// freopen(".out","w",stdout);
	
	// cerr<<(&mbe-&med)/1024.0/1024.0<<"\n";
	
	T=1;
	while(T--)work();
}