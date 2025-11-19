// Problem: P9926 [NFLSPC #6] 所以 k 小生成树怎么做？
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P9926
// Memory Limit: 2048 MB
// Time Limit: 4000 ms
// Written by yhm.
// Start codeing:2025-11-19 08:38:45
// 
// Powered by CP Editor (https://cpeditor.org)

#include<bits/stdc++.h>
#define int long long
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
const int maxn=50010;
const int inf=1e9;
bool mbe;

int n,m,k;
struct edge{
	int u,v,w;
}g[maxn<<1];
int ff[maxn];
int fd(int x){
	if(ff[x]==x)return x;
	return ff[x]=fd(ff[x]);
}
struct dat{
	int add,del,fr,val;
	bool operator<(const dat &u)const{return val>u.val;}
};
struct node{
	int sum;
	vector<vector<int>> e;
	vector<int> vis;
	vector<int> fa,dep,eid;int idx;
	void dfs(int u){
		dep[u]=dep[fa[u]]+1;
		for(int v:e[u])if(v!=fa[u]){
			fa[v]=u;dfs(v);
		}
	}
	//非树边/树边
	//是否可被替换
	void init(){
		fa.resize(n),dep.resize(n),eid.resize(n);idx=0;
		dfs(0);
		for(int i=0;i<m;i++)if(vis[i]&1){
			auto[u,v,w]=g[i];
			if(fa[u]==v)swap(u,v);
			eid[v]=i;
		}
	}
	void add(int u,int v){
		e[u].pb(v),e[v].pb(u);
	}
	void del(int u,int v){
		e[u].erase(find(e[u].begin(),e[u].end(),v));
		e[v].erase(find(e[v].begin(),e[v].end(),u));
	}
	dat calc(){
		dat res={-1,-1,-1,inf};
		for(int i=0;i<n;i++)ff[i]=i;
		for(int i=0;i<m;i++)if(!vis[i]){
			auto[u,v,w]=g[i];
			u=fd(u),v=fd(v);
			while(u!=v){
				if(dep[u]<dep[v])swap(u,v);
				if(vis[eid[u]]==1)res=max(res,{i,eid[u],-1,w-g[eid[u]].w});
				u=ff[u]=fd(fa[u]);
			}
		}
		res.val+=sum;
		return res;
	}
}mst;
priority_queue<dat> q;
vector<node> st;int tp;
void work(){
	n=read();m=read();k=read();
	for(int i=1;i<=m;i++){
		int u=read(),v=read(),w=read();
		g[i-1]={u-1,v-1,w};
	}
	sort(g,g+m,[&](edge u,edge v){return u.w<v.w;});
	mst.e.resize(n);
	mst.vis.resize(m);
	for(int i=0;i<n;i++)ff[i]=i;
	for(int i=0;i<m;i++){
		auto[u,v,w]=g[i];
		if(fd(u)!=fd(v)){
			ff[fd(u)]=fd(v);
			mst.add(u,v);mst.vis[i]=1;
			mst.sum+=w;
		}
	}
	st.resize(k);
	q.push({-1,-1,-1,mst.sum});
	while(!q.empty()&&k){
		auto[ad,dl,fr,val]=q.top();q.pop();
		// cout<<ad<<" "<<dl<<" "<<fr<<" "<<val<<"\n";
		printf("%lld\n",val);k--;
		if(fr==-1)st[tp]=mst;
		else{
			st[tp]=st[fr];st[tp].sum=val;
			st[tp].del(g[dl].u,g[dl].v);
			st[tp].add(g[ad].u,g[ad].v);
			st[tp].vis[dl]=0,st[tp].vis[ad]=3;
			st[fr].vis[ad]=2;
			dat u=st[fr].calc();u.fr=fr;
			if(u.add!=-1)q.push(u);
		}
		st[tp].init();
		dat u=st[tp].calc();u.fr=tp;
		if(u.add!=-1)q.push(u);
		tp++;
	}
	while(k--)puts("-1");
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