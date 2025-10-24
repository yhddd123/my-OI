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
const int maxn=600010;
const int inf=1e9;
bool mbe;

int n,m;
set<int> s[maxn];
vector<pii> ans;
vector<int> e[maxn],g[maxn];
int scct;
int dfn[maxn],idx,lw[maxn];
int st[maxn],tp;
void tar(int u){
	dfn[u]=lw[u]=++idx;st[++tp]=u;
	for(int v:e[u]){
		if(!dfn[v]){
			tar(v);
			lw[u]=min(lw[u],lw[v]);
			if(lw[v]>=dfn[u]){
				g[++scct].push_back(st[tp]);
				g[st[tp]].push_back(scct);
				while(st[tp--]!=v){
					g[scct].push_back(st[tp]);
					g[st[tp]].push_back(scct);
				}
				g[scct].push_back(u);
				g[u].push_back(scct);
			}
		}
		else lw[u]=min(lw[u],dfn[v]);
	}
}
void dfs(int u,int fa){
	for(int v:g[u])if(v!=fa)dfs(v,u);
	// cout<<u<<" "<<fa<<endl;
	if(u>n){
		vector<int> tmp(g[u].size());
		int p=0;for(int i=0;i<g[u].size();i++)if(g[u][i]==fa)p=i;
		for(int i=p;i<g[u].size();i++)tmp[i-p]=g[u][i];
		for(int i=0;i<p;i++)tmp[i+g[u].size()-p]=g[u][i];
		swap(g[u],tmp);
		for(int i=1;i<g[u].size();i++){
			int v=g[u][i];
			if(i&1)ans.pb({1,v});
			else ans.pb({1,v+n});
		}
		ans.pb({1,g[u][1]+n});
		if(g[u].size()&1)ans.pb({1,g[u].back()});
		else ans.pb({1,g[u].back()+n});
	}
}
void work(){
	n=read();m=read();
	for(int i=1;i<=m;i++){
		int u=read(),v=read();
		s[u].insert(v),s[v].insert(u);
	}
	set<int> ss;
	for(int i=1;i<=n;i++)if(s[i].size()&1)ss.insert(i);
	while(ss.size()){
		int u=*ss.begin();ss.erase(*ss.begin());ans.pb({1,u});
		for(int v:s[u]){
			s[v].erase(u);
			if(ss.find(v)==ss.end())ss.insert(v);
			else ss.erase(v);
		}
		s[u].clear();
	}
	int rt=0;for(int i=1;i<=n;i++)if(s[i].size()&&!rt)rt=i;
	if(rt){
		ans.pb({2,0});
		for(int i=1;i<=n;i++)if(!s[i].size())ans.pb({1,i});
		for(int u=1;u<=n;u++){
			for(int v:s[u])e[u].pb(v);
		}
		
		// for(int i=1;i<=n;i++)if(s[i].size()){
			// for(int j:s[i])s[i+n].insert(j+n);
			// s[i].insert(i+n);s[i+n].insert(i);
		// }
		// int p=ans.size();
		
		scct=n;
		for(int i=1;i<=n;i++)if(e[i].size()&&!dfn[i]){
			tar(i);
			dfs(i,0);
			ans.pb({1,i});
		}
		
		// for(int i=p;i<ans.size();i++){
			// int u=ans[i].se;
			// for(int v:s[u])s[v].erase(u);
			// s[u].clear();
		// }
		// for(int i=1;i<=2*n;i++)if(s[i].size()){
			// for(int j:s[i])cout<<i<<" "<<j<<" err\n";
		// }
	}
	printf("0 %d\n",ans.size());
	for(auto[o,u]:ans){
		if(o==2)puts("2");
		else printf("1 %d\n",u);
	}
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