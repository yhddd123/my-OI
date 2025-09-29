// Problem: CF1656I Neighbour Ordering
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/CF1656I
// Memory Limit: 250 MB
// Time Limit: 5000 ms
// Written by yhm.
// Start codeing:2025-09-29 16:30:15
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
const int maxn=300010;
const int inf=1e9;
bool mbe;

int n,m;
vector<int> e[maxn];
int dfn[maxn],lw[maxn],idx;
int st[maxn],tp;
int dep[maxn];
vector<int> g[maxn<<1];int scc[maxn],scct;
void tar(int u){
	dfn[u]=lw[u]=++idx;st[++tp]=u;
	for(int v:e[u]){
		if(!dfn[v]){
			dep[v]=dep[u]+1;tar(v);
			lw[u]=min(lw[u],lw[v]);
			if(lw[v]==dfn[u]){
				g[++scct].pb(st[tp]),g[st[tp]].pb(scct);
				while(st[tp--]!=v)g[scct].pb(st[tp]),g[st[tp]].pb(scct);
				g[scct].pb(u),g[u].pb(scct);
			}
		}
		else lw[u]=min(lw[u],dfn[v]);
	}
}
vector<pii> edge[maxn<<1];
map<int,bool> mp[maxn];
int d[maxn];
void add(int u,int v){
	if(mp[u].find(v)==mp[u].end())mp[u][v]=1,d[u]++;
}
int pre[maxn],nxt[maxn];
vector<int> a[maxn<<1];
int rnk[maxn],val[maxn];
vector<int> ans[maxn<<1];
bool sovle(int id){
	for(int u:g[id])mp[u].clear(),d[u]=0;
	for(auto[u,v]:edge[id])add(u,v),add(v,u);
	queue<int> q;
	for(int u:g[id])if(d[u]<=2)q.push(u);
	vector<tuple<int,int,int>> tmp;
	int p1=0,p2=0;
	while(!q.empty()){
		int u=q.front();q.pop();
		if(!d[u])continue;
		if(d[u]==1){
			int v=(*mp[u].begin()).fi;
			mp[u].erase(v),mp[v].erase(u);d[u]--,d[v]--;
			p1=u,p2=v;
			if(d[v]<=2)q.push(v);
		}
		if(d[u]==2){
			int v1=(*mp[u].begin()).fi,v2=(*--mp[u].end()).fi;
			add(v1,v2),add(v2,v1);tmp.pb({u,v1,v2});
			mp[u].erase(v1),mp[u].erase(v2),mp[v1].erase(u),mp[v2].erase(u),d[u]-=2,d[v1]--,d[v2]--;
			if(d[v1]<=2)q.push(v1);
			if(d[v2]<=2)q.push(v2);
		}
	}
	for(int u:g[id])if(d[u])return 0;
	for(int u:g[id])pre[u]=nxt[u]=0;
	pre[p1]=p2,pre[p2]=p1,nxt[p1]=p2,nxt[p2]=p1;
	reverse(tmp.begin(),tmp.end());
	for(auto[u,v1,v2]:tmp){
		// cout<<u-1<<" "<<v1-1<<" "<<v2-1<<"\n";
		if(pre[v2]!=v1)swap(v1,v2);
		if(pre[v2]!=v1)return 0;
		pre[u]=v1,nxt[v1]=u,pre[v2]=u,nxt[u]=v2;
	}
	int u=*g[id].begin();
	a[id].clear();
	while(a[id].size()<g[id].size()){
		a[id].pb(u);
		u=nxt[u];
	}
	// for(int u:a[id])cout<<u<<" ";cout<<"\n";
	for(int i=0;i<a[id].size();i++)rnk[a[id][i]]=i;
	for(int u:g[id])ans[u+n].clear();
	for(auto[u,v]:edge[id])ans[u+n].pb(v),ans[v+n].pb(u);
	for(int u:g[id]){
		for(int v:ans[u+n])val[v]=(rnk[v]<rnk[u]?rnk[v]+g[id].size()-rnk[u]:rnk[v]-rnk[u]);
		sort(ans[u+n].begin(),ans[u+n].end(),[&](int x,int y){return val[x]<val[y];});
		// cout<<u<<"\n";for(int v:ans[u+n])cout<<v<<" "<<val[v]<<" "<<rnk[v]<<"\n";
	}
	for(int u:g[id]){
		for(int v:ans[u+n])ans[u].pb(v);
	}
	return 1;
}
void work(){
	n=read();m=read();
	for(int i=1;i<=n;i++)e[i].clear();
	for(int i=1;i<=m;i++){
		int u=read()+1,v=read()+1;
		e[u].pb(v),e[v].pb(u);
	}
	for(int i=1;i<=n;i++)dfn[i]=scc[i]=0;idx=0;
	for(int i=1;i<=scct;i++)g[i].clear();scct=n;
	for(int i=1;i<=n;i++)if(!dfn[i])tar(i);
	for(int i=n+1;i<=scct;i++)edge[i].clear();
	for(int i=n+1;i<=scct;i++){
		sort(g[i].begin(),g[i].end(),[&](int u,int v){return dep[u]<dep[v];});
		for(int j=1;j<g[i].size();j++)scc[g[i][j]]=i;
	}
	for(int u=1;u<=n;u++){
		for(int v:e[u])if(dep[u]<dep[v])edge[scc[v]].pb({u,v});
	}
	for(int i=1;i<=n;i++)ans[i].clear();
	for(int i=n+1;i<=scct;i++)if(!sovle(i)){puts("NO");return ;}
	puts("YES");
	for(int u=1;u<=n;u++){
		for(int v:ans[u])printf("%d ",v-1);puts("");
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