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
const int maxn=2010;
const int inf=1e9;
bool mbe;

int n;
vector<int> e[maxn];
int dep[maxn],id[maxn];
void dfs(int u,int fa){
	dep[u]=dep[fa]+1;
	for(int v:e[u])if(v!=fa)dfs(v,u);
}
bool vis[maxn],ban[maxn];
vector<pii> ans;
bool fl[maxn];
void mov(int u,int v){
	// cout<<u<<" "<<v<<"\n";
	ans.pb({u,v});
	swap(vis[u],vis[v]);
	// for(int p:e[v])if(vis[p]){
		// cout<<u<<" "<<v<<" "<<p<<"\n";
		// exit(0);
	// }
}
void down(int u,int fa){
	for(int v:e[u])if(v!=fa&&!ban[v]){
		down(v,u);
	}
	if(vis[u]){
		for(int v:e[u])if(v!=fa&&!ban[v]&&fl[v]){fl[v]=0;mov(u,v);break;}
	}
	fl[u]=!vis[u];
	for(int v:e[u])if(v!=fa)fl[u]&=!vis[v];
}
bool up(int u,int fa){
	if(!fl[u]){
		int num=0;for(int v:e[u])if(v!=fa)num+=vis[v];
		if(num>1)return 0;
		num=0;for(int v:e[u])if(v!=fa&&!ban[v])num+=vis[v];
		if(!num)return 0;
		for(int v:e[u])if(v!=fa&&!ban[v]&&vis[v])mov(v,u);
		return 1;
	}
	for(int v:e[u])if(v!=fa&&!ban[v]){
		if(up(v,u)){mov(v,u);return 1;}
	}
	return 0;
}
vector<pii> sovle(vector<int> &pid){
	for(int i=1;i<=n;i++)vis[i]=ban[i]=fl[i]=0;
	for(int i:pid)vis[i]=1;
	ans.clear();
	for(int i=n;i;i--){
		int u=id[i];ban[u]=1;
		if(vis[u])continue;
		down(u,0);
		up(u,0);
	}
	pid.clear();for(int i=1;i<=n;i++)if(vis[i])pid.pb(i);
	return ans;
}
void work(){
	n=read();
	for(int i=1;i<=n;i++)e[i].clear();
	for(int i=1;i<n;i++){
		int u=read(),v=read();
		e[u].pb(v),e[v].pb(u);
	}
	dfs(1,0);
	for(int i=1;i<=n;i++)id[i]=i;
	sort(id+1,id+n+1,[&](int u,int v){return dep[u]<dep[v];});
	int k=read();
	vector<int> id1(k),id2(k);
	for(int i=0;i<k;i++)id1[i]=read();
	for(int i=0;i<k;i++)id2[i]=read();
	vector<pii> ans1=sovle(id1),ans2=sovle(id2);
	// for(int i=1;i<=n;i++)cout<<id[i]<<" ";cout<<"\n";
	// for(int i:id1)cout<<i<<" ";cout<<"\n";
	// for(int i:id2)cout<<i<<" ";cout<<"\n";
	if(id1==id2){
		puts("YES");
		printf("%d\n",ans1.size()+ans2.size());
		for(auto[u,v]:ans1)printf("%d %d\n",u,v);
		reverse(ans2.begin(),ans2.end());
		for(auto[u,v]:ans2)printf("%d %d\n",v,u);
	}
	else puts("NO");
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