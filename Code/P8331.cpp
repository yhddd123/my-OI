// Problem: P8331 [ZJOI2022] 简单题
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P8331
// Memory Limit: 1 MB
// Time Limit: 6000 ms
// Written by yhm.
// Start codeing:2025-04-14 18:37:03
// 
// Powered by CP Editor (https://cpeditor.org)

#include<bits/stdc++.h>
#define int long long
#define mod 998244353ll
#define pii pair<int,int>
#define fi first
#define se second
#define pb push_back
#define mkp make_pair
#define mems(a,x) memset((a),(x),sizeof(a))
using namespace std;
static char buf[1000000],*p1=buf,*p2=buf;
#define getchar() p1==p2&&(p2=(p1=buf)+fread(buf,1,1000000,stdin),p1==p2)?EOF:*p1++
inline int read(){int x=0,f=1;char c=getchar();while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}while(c>='0'&&c<='9'){x=(x<<3)+(x<<1)+c-48;c=getchar();}return x*f;}
inline void write(int x){static char buf[20];static int len=-1;if(x<0)putchar('-'),x=-x;do buf[++len]=x%10,x/=10;while(x);while(len>=0)putchar(buf[len--]+48);}
#define put() putchar(' ')
#define endl puts("")
const int maxn=1000010;
const int inf=1e18;
bool mbe;

int n,m,q;
vector<pii> e[maxn];
vector<int> g[maxn];
int dfn[maxn],lw[maxn],idx;
int st[maxn],tp;
int scc[maxn],scct;
int dep[maxn];
void tar(int u){
	dfn[u]=lw[u]=++idx;st[++tp]=u;
	for(auto[v,w]:e[u]){
		if(!dfn[v]){
			dep[v]=dep[u]+1;tar(v);
			lw[u]=min(lw[u],lw[v]);
			if(lw[v]>=dfn[u]){
				++scct;
				g[scct].pb(st[tp]),g[st[tp]].pb(scct);
				while(st[tp--]!=v)g[scct].pb(st[tp]),g[st[tp]].pb(scct);
				g[scct].pb(u),g[u].pb(scct);
			}
		}
		else lw[u]=min(lw[u],dfn[v]);
	}
}
vector<tuple<int,int,int>> ee[maxn];
pii merge(pii u,pii v){return {u.fi*v.fi%mod,(u.fi*v.se+u.se*v.fi)%mod};}
int to[maxn][20];
pii val[maxn][20];
int a[maxn],b[maxn],num[maxn],sum[maxn];
vector<int> d[maxn],disa[maxn],disb[maxn],pos[maxn];
int rnk[maxn];
void dfsa(int id,int u,int fa){
	for(auto[v,w]:e[u])if(v!=fa){
		if(v==g[id][b[id]])continue;
		disa[id][rnk[v]]=disa[id][rnk[u]]+w;
		dfsa(id,v,u);
	}
}
void dfsb(int id,int u,int fa){
	for(auto[v,w]:e[u])if(v!=fa){
		if(v==g[id][a[id]])continue;
		disb[id][rnk[v]]=disb[id][rnk[u]]+w;
		dfsb(id,v,u);
	}
}
void dfsp(int id,int u,int fa,int fr){
	pos[id][rnk[u]]=fr;
	for(auto[v,w]:e[u])if(v!=fa){
		if(v==g[id][b[id]])continue;
		dfsp(id,v,u,fr);
	}
}
void init(int id){
	int sz=g[id].size();
	sort(g[id].begin(),g[id].end());
	d[id].resize(sz),disa[id].resize(sz),disb[id].resize(sz),pos[id].resize(sz);
	for(int i=0;i<sz;i++)rnk[g[id][i]]=i;
	for(auto[u,v,w]:ee[id])d[id][rnk[u]]++,d[id][rnk[v]]++;
	a[id]=b[id]=-1;
	for(int i=0;i<sz;i++)if(d[id][i]>2)(a[id]==-1?a[id]:b[id])=i;
	if(a[id]==-1)a[id]=0,b[id]=1;
	for(int u:g[id])e[u].clear();
	for(auto[u,v,w]:ee[id])e[u].pb({v,w}),e[v].pb({u,w}),sum[id]+=w;sum[id]%=mod;
	dfsa(id,g[id][a[id]],0),dfsb(id,g[id][b[id]],0);
	disa[id][b[id]]=disb[id][a[id]]=inf;
	pos[id][a[id]]=-1,pos[id][b[id]]=-1;
	for(auto [v,w]:e[g[id][a[id]]]){
		++num[id];
		if(v==g[id][b[id]])continue;
		dfsp(id,v,g[id][a[id]],num[id]);
	}
	// cout<<id<<" "<<num[id]<<" "<<sum[id]<<" init\n";
}
pii calc(int id,int u,int v){
	int p=lower_bound(g[id].begin(),g[id].end(),u)-g[id].begin();
	int q=lower_bound(g[id].begin(),g[id].end(),v)-g[id].begin();
	if(pos[id][p]!=-1&&pos[id][q]!=-1&&pos[id][p]!=pos[id][q]){
		return {2*(num[id]-1),(2*sum[id]+(disa[id][p]+disb[id][p]+disa[id][q]+disb[id][q])%mod*(num[id]+mod-3))%mod};
	}
	int va=0,vb=0;
	if(disa[id][p]<disa[id][q])va=disa[id][p],vb=disb[id][q];
	else va=disa[id][q],vb=disb[id][p];
	// cout<<id<<" "<<a[id]<<" "<<b[id]<<" "<<p<<" "<<q<<"\n"<<u<<" "<<v<<" "<<va<<" "<<vb<<" calc\n";
	return {num[id],(sum[id]+(va+vb)%mod*(num[id]-2))%mod};
}
void dfs(int u,int fa){
	dep[u]=dep[fa]+1;to[u][0]=fa;
	for(int i=1;i<20;i++)to[u][i]=to[to[u][i-1]][i-1];
	if(u<=n&&u>1)val[u][0]=calc(to[u][0],u,to[u][1]);
	// cout<<u<<" "<<to[u][1]<<" "<<val[u][0].fi<<" "<<val[u][0].se<<"\n";
	for(int i=1;i<20;i++)val[u][i]=merge(val[u][i-1],val[to[u][i]][i-1]);
	for(int v:g[u])if(v!=fa)dfs(v,u);
}
int lca(int u,int v){
	if(dep[u]<dep[v])swap(u,v);
	for(int i=19;~i;i--)if(dep[to[u][i]]>=dep[v])u=to[u][i];
	if(u==v)return u;
	for(int i=19;~i;i--)if(to[u][i]!=to[v][i])u=to[u][i],v=to[v][i];
	return to[u][0];
}
int que(int u,int v){
	int tp=lca(u,v);
	pii res={1,0};
	for(int i=19;i;i--)if(dep[to[u][i]]>=dep[tp])res=merge(res,val[u][i-1]),u=to[u][i];
	for(int i=19;i;i--)if(dep[to[v][i]]>=dep[tp])res=merge(res,val[v][i-1]),v=to[v][i];
	// cout<<u<<" "<<v<<" "<<res.fi<<" "<<res.se<<" "<<"que\n";
	if(u==v)return res.se;
	return merge(res,calc(to[u][0],u,v)).se;
}
void work(){
	n=read();m=read();q=read();	
	for(int i=1;i<=m;i++){
		int u=read(),v=read(),w=read();
		e[u].pb({v,w}),e[v].pb({u,w});
	}
	scct=n;tar(1);
	for(int i=n+1;i<=scct;i++){
		sort(g[i].begin(),g[i].end(),[&](int u,int v){return dep[u]<dep[v];});
		for(int j=1;j<g[i].size();j++)scc[g[i][j]]=i;
	}
	for(int u=1;u<=n;u++){
		for(auto[v,w]:e[u])if(dep[u]<dep[v]||(dep[u]==dep[v]&&u<v))ee[scc[v]].pb({u,v,w});
	}
	for(int i=n+1;i<=scct;i++)init(i);
	dfs(1,0);
	while(q--){
		int u=read(),v=read();
		write(que(u,v));puts("");
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