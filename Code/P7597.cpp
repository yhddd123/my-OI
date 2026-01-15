// Problem: P7597 「EZEC-8」猜树 加强版
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P7597
// Memory Limit: 128 MB
// Time Limit: 1000 ms
// Written by yhm.
// Start codeing:2026-01-15 20:31:02
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
const int maxn=200010;
const int inf=1e9;
bool mbe;

int n;
mt19937 rnd(0);
namespace gra{
	int fa[maxn],dep[maxn];
	vector<int> e[maxn];
	int dfn[maxn],rnk[maxn],idx,siz[maxn];
	void dfs(int u){
		dep[u]=dep[fa[u]]+1;
		rnk[dfn[u]=++idx]=u,siz[u]=1;
		for(int v:e[u])dfs(v),siz[u]+=siz[v];
	}
	void init(){
		for(int i=2;i<=n;i++)fa[i]=rnd()%(i-1)+1,e[fa[i]].pb(i);
		dfs(1);
	}
	int ask1(int u,int v){return dfn[v]<dfn[u]+siz[u]?dep[v]-dep[u]:dep[v]-dep[u]+2;}
	vector<int> ask2(int u){
		vector<int> id;
		for(int i=dfn[u];i<dfn[u]+siz[u];i++)id.pb(rnk[i]);
		return id;
	}
}
int ask1(int u,int v){
	cout<<"? 1 "<<u<<" "<<v<<endl;
	// return gra::ask1(u,v);
	return read();
}
vector<int> ask2(int u){
	cout<<"? 2 "<<u<<endl;
	// return gra::ask2(u);
	int k=read();vector<int> id(k);
	for(int i=0;i<k;i++)id[i]=read();
	return id;
}
int ans[maxn];
int dep[maxn];
vector<int> id[maxn];
bool vis[maxn];
void dfs(int u){
	if(id[u].size()==1)return ;
	int p=id[u][rnd()%id[u].size()];
	while(p==u)p=id[u][rnd()%id[u].size()];
	vector<int> son;
	for(int v:id[u])if(dep[v]==dep[u]+1)ans[v]=u,son.pb(v);
	for(int &v:son){
		if(ask1(v,p)==dep[p]-dep[v]){
			swap(son[0],v);
			break;
		}
	}
	for(int v:son){
		if(v==son[0])continue;
		id[v]=ask2(v);
	}
	for(int v:id[u])vis[v]=1;vis[u]=0;
	for(int v:son)if(v!=son[0])for(int vv:id[v])vis[vv]=0;
	for(int v:id[u])if(vis[v]){
		id[son[0]].pb(v),vis[v]=0;
	}
	for(int v:son){
		dfs(v);
	}
}
void work(){
	n=read();
	// gra::init();
	// for(int i=2;i<=n;i++)cout<<gra::fa[i]<<" ";cout<<endl;
	for(int i=2;i<=n;i++)dep[i]=ask1(1,i);
	for(int i=1;i<=n;i++)id[1].pb(i);
	dfs(1);
	cout<<"! ";for(int i=2;i<=n;i++)cout<<ans[i]<<" ";cout<<endl;
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