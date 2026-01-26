// Problem: C - Double X
// Contest: AtCoder - AtCoder Regular Contest 213 (Div. 1)
// URL: https://atcoder.jp/contests/arc213/tasks/arc213_c
// Memory Limit: 1024 MB
// Time Limit: 4000 ms
// Written by yhm.
// Start codeing:2026-01-26 19:51:16
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
const int maxn=100010;
const int inf=4e9;
bool mbe;

int n,a[maxn],ans[maxn];
struct graph{
	bool fl;
	int fa[maxn];
	vector<int> e[maxn];
	int dfn[maxn],rnk[maxn],idx;
	int siz[maxn],son[maxn];
	bool in(int u,int v){return dfn[u]<=dfn[v]&&dfn[v]<dfn[u]+siz[u];}
	void dfs(int u,int fa){
		fa[u]=::fa;
		rnk[dfn[u]=++idx]=u;siz[u]=1;son[u]=0;
		if(fl){
			sort(e[u].begin(),e[u].end());
			if(fa)e[u].erase(lower_bound(e[u].begin(),e[u].end()),fa);
		}
		for(int v:e[u]){
			dfs(v,u),siz[u]+=siz[v];
			if(siz[v]>=siz[son[u]])son[u]=v;
		}
	}
	void init(bool _){
		fl=_;
		for(int i=1;i<=n;i++)e[i].clear();
		for(int i=1;i<n;i++){
			int u=read(),v=read();
			e[u].pb(v),e[v].pb(u);
		}
		idx=0;dfs(1,0);
	}
}g1,g2;
#define mid ((l+r)>>1)
#define ls lc[nd]
#define rs rc[nd]
int mn[maxn<<6],lc[maxn<<6],rc[maxn<<6],rt[maxn],idx;
void modif(int &nd,int l,int r,int p,int w){
	if(!nd)mn[nd=++idx]=inf;mn[nd]=min(mn[nd],w);
	if(l==r)return ;
	if(p<=mid)modif(ls,l,mid,p,w);
	else modif(rs,mid+1,r,p,w);
}
int query(int nd,int l,int r,int ql,int qr){
	if(!nd||l>r)return inf;
	if(l>=ql&&r<=qr)return mn[nd];
	if(qr<=mid)return query(ls,l,mid,ql,qr);
	if(ql>mid)return query(rs,mid+1,r,ql,qr);
	return min(query(ls,l,mid,ql,qr),query(rs,mid+1,r,ql,qr));
}
int merge(int u,int v,int l,int r){
	if(!u||!v)return u|v;
	if(l==r){
		mn[u]=min(mn[u],mn[v]);
		return u;
	}
	lc[u]=merge(lc[u],lc[v],l,mid),rc[u]=merge(rc[u],rc[v],mid+1,r);
	mn[u]=min(mn[lc[u]],mn[rc[u]]);return u;
}
void clr(){
	for(int i=1;i<=n;i++)rt[i]=0;
	while(idx)mn[idx]=inf,lc[idx]=rc[idx]=0,idx--;
}
int que(int rt,int l,int r){return query(rt,1,n,l,r);}
int v1[maxn],v2[maxn],v3[maxn],v4[maxn];
void dfs(int u,int fa){
	if(g1.son[u]){
		int v=g1.son[u];
		dfs(v,u);
		v1[v]=que(rt[v],g2.dfn[g2.son[u]],g2.dfn[g2.son[u]]+g2.siz[g2.son[u]]-1);
		v2[v]=min(que(rt[v],1,g2.dfn[g2.son[u]]-1),que(rt[v],g2.dfn[g2.son[u]]+g2.siz[g2.son[u]],n));
	}
	rt[u]=rt[g1.son[u]];
	modif(rt[u],1,n,g2.dfn[u],a[u]);
	for(int v:g1.e[u])if(v!=g1.son[u]){
		dfs(v,u);
		v1[v]=que(rt[v],g2.dfn[g2.son[u]],g2.dfn[g2.son[u]]+g2.siz[g2.son[u]]-1);
		v2[v]=min(que(rt[v],1,g2.dfn[g2.son[u]]-1),que(rt[v],g2.dfn[g2.son[u]]+g2.siz[g2.son[u]],n));
		rt[u]=merge(rt[u],rt[v],1,n);
	}
}
vector<int> ask[maxn];
vector<int> id[maxn];
mt19937 rnd(time(0));
int col[maxn];
int val[maxn][4];
void work(){
	n=read();
	for(int i=1;i<=n;i++)a[i]=read();
	g1.init(1),g2.init(0);
	clr();dfs(1,0);
	for(int i=1;i<=n;i++)ask[g1.dfn[i]-1].pb(i);
	clr();for(int i=1,rt=0;i<=n;i++){
		modif(rt,1,n,g2.dfn[u],a[u]);
		for(int u:ask[i]){
			v3[u]=que(rt,g2.dfn[g2.son[u]],g2.dfn[g2.son[u]]+g2.siz[g2.son[u]]-1);
			v4[u]=min(que(rt,1,g2.dfn[g2.son[u]]-1),que(rt,g2.dfn[g2.son[u]]+g2.siz[g2.son[u]],n));
		}
		ask[i].clear();
	}
	for(int i=1;i<=n;i++)ask[g1.dfn[i]+g1.siz[i]].pb(i);
	clr();for(int i=n,rt=0;i;i--){
		modif(rt,1,n,g2.dfn[u],a[u]);
		for(int u:ask[i]){
			v3[u]=min(v3[u],que(rt,g2.dfn[g2.son[u]],g2.dfn[g2.son[u]]+g2.siz[g2.son[u]]-1));
			v4[u]=min({v4[u],que(rt,1,g2.dfn[g2.son[u]]-1),que(rt,g2.dfn[g2.son[u]]+g2.siz[g2.son[u]],n)});
		}
		ask[i].clear();
	}
	for(int u=1;u<=n;u++){
		for(int v:g2.e[u])if(v!=g2.son[u]){
			for(int i=g2.dfn[v];i<g2.dfn[v]+g2.siz[v];i++)id[v].pb(rnk[i]);
		}
	}
	for(int i=1;i<=n;i++)ans[i]=inf;
	int T=200;
	while(T--){
		for(int u=1;u<=n;u++){
			for(int c=0;c<4;c++)val[g2.fa[u]][c]=inf;
			for(int c=0;c<4;c++)val[g2.son[u]][c]=inf;
			for(int v:g1.e[u]){
				int c=col[v]=rnd()&3;
				val[g2.son[u]][c]=min(val[g2.son[u]][c],v1[v]);
				val[g2.fa[u]][c]=min(val[g2.fa[u]][c],v2[v]);
			}
			if(u>1){
				int c=col[g1.fa[u]]=rnd()&3;
				val[g2.son[u]][c]=min(val[g2.son[u]][c],v3[u]);
				val[g2.fa[u]][c]=min(val[g2.fa[u]][c],v4[u]);
			}
			for(int v:e[u])if(v!=g2.son[u]){
				for(int c=0;c<4;c++)val[v][c]=inf;
				for(int p:id[v])g1.
			}
		}
	}
	for(int i=1;i<=n;i++)if(ans[i]==inf)ans[i]=-1;
	for(int u=1;u<=n;u++)printf("%lld ",ans[u]);puts("");
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