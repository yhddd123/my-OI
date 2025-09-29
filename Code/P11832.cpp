// Problem: P11832 [省选联考 2025] 图排列
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P11832
// Memory Limit: 512 MB
// Time Limit: 2500 ms
// Written by yhm.
// Start codeing:2025-09-29 14:53:36
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
const int maxn=100010;
const int inf=1e9;
bool mbe;

int n,m;
vector<int> e[maxn];
int f[maxn];
int fd(int x){
	if(f[x]==x)return x;
	return f[x]=fd(f[x]);
}
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
void sovle(int id){
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
	for(int u:g[id])pre[u]=nxt[u]=0;
	pre[p1]=p2,pre[p2]=p1,nxt[p1]=p2,nxt[p2]=p1;
	reverse(tmp.begin(),tmp.end());
	for(auto[u,v1,v2]:tmp){
		if(pre[v2]!=v1)swap(v1,v2);
		pre[u]=v1,nxt[v1]=u,pre[v2]=u,nxt[u]=v2;
	}
	int u=*g[id].begin();
	a[id].clear();
	while(a[id].size()<g[id].size()){
		a[id].pb(u);
		u=nxt[u];
	}
}
list<int> id[maxn<<1];
void dfs(int u,int fa){
	if(u<=n){
		vector<int> son;
		for(int v:g[u]){
			if(v==fa)continue;
			dfs(v,u);son.pb(v);
		}
		id[u].clear();id[u].pb(u);son.pb(u);
		sort(son.begin(),son.end(),[&](int u,int v){return (*id[u].begin())<(*id[v].begin());});
		list<int> tmp;
		for(int v:son)tmp.splice(tmp.end(),id[v]);
		swap(id[u],tmp);
	}
	else{
		for(int v:a[u]){
			if(v==fa)continue;
			dfs(v,u);
		}
		rotate(a[u].begin(),find(a[u].begin(),a[u].end(),fa),a[u].end());
		if((*id[a[u][1]].begin())>(*id[a[u].back()].begin()))reverse(a[u].begin()+1,a[u].end());
		id[u].clear();
		for(int i=1;i<a[u].size();i++)id[u].splice(id[u].end(),id[a[u][i]]);
	}
}
priority_queue<int,vector<int>,greater<int>> q;
vector<int> ans;
void dfs(int u){
	for(int p:a[u]){
		while(q.size()&&p>q.top()){
			int v=q.top();q.pop();
			dfs(v);
		}
		ans.pb(p);
	}
}
void work(){
	n=read();m=read();
	for(int i=1;i<=n;i++)f[i]=i;
	for(int i=1;i<=n;i++)e[i].clear();
	for(int i=1;i<=m;i++){
		int u=read(),v=read();
		e[u].pb(v),e[v].pb(u);
		u=fd(u),v=fd(v);
		if(u==v)continue;
		if(u>v)swap(u,v);f[v]=u;
	}
	for(int i=1;i<=n;i++)dfn[i]=scc[i]=0;idx=0;
	for(int i=1;i<=scct;i++)g[i].clear();scct=n;tp=0;
	for(int i=1;i<=n;i++)if(!dfn[i])tar(i);
	for(int i=n+1;i<=scct;i++)edge[i].clear();
	for(int i=n+1;i<=scct;i++){
		sort(g[i].begin(),g[i].end(),[&](int u,int v){return dep[u]<dep[v];});
		for(int j=1;j<g[i].size();j++)scc[g[i][j]]=i;
	}
	for(int u=1;u<=n;u++){
		for(int v:e[u])if(dep[u]<dep[v])edge[scc[v]].pb({u,v});
	}
	for(int i=n+1;i<=scct;i++)sovle(i);
	for(int i=1;i<=n;i++)if(f[i]==i){
		dfs(i,0);q.push(i);
		a[i].clear();for(int u:id[i])a[i].pb(u);
	}
	ans.clear();
	while(!q.empty()){
		int u=q.top();q.pop();
		dfs(u);
	}
	for(int u:ans)printf("%d ",u);puts("");
}

bool med;
int T;
signed main(){
	// freopen(".in","r",stdin);
	// freopen(".out","w",stdout);
	
	// cerr<<(&mbe-&med)/1024.0/1024.0<<"\n";
	
	read();T=read();
	while(T--)work();
}