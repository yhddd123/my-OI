// Problem: P5311 [Ynoi2011] 成都七中
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P5311
// Memory Limit: 250 MB
// Time Limit: 1000 ms
// Written by yhm.
// Start codeing:2026-02-02 16:01:30
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
const int inf=1e9;
bool mbe;

int n,m,q,a[maxn];
int ff[maxn];
int fd(int x){
	if(ff[x]==x)return x;
	return ff[x]=fd(ff[x]);
}
vector<int> e[maxn];
int up1[maxn][17],up2[maxn][17];
int fa[maxn],dep[maxn],siz[maxn],son[maxn];
void dfs(int u){
    dep[u]=dep[fa[u]]+1,siz[u]=1,son[u]=0;
    up1[u][0]=fa[u];for(int i=1;i<=16;i++)up1[u][i]=up1[up1[u][i-1]][i-1];
    for(int v:e[u])if(v!=fa[u]){
        fa[v]=u;dfs(v),siz[u]+=siz[v];
        if(siz[v]>=siz[son[u]])son[u]=v;
    }
}
int dfn[maxn],rnk[maxn],idx,tp[maxn],st[17][maxn];
void dfs(int u,int lst){
    rnk[dfn[u]=++idx]=u;tp[u]=lst;st[0][idx]=fa[u];
    if(!son[u])return ;dfs(son[u],lst);
    for(int v:e[u])if(v!=fa[u]&&v!=son[u])dfs(v,v);
}
int mmax(int u,int v){return dfn[u]<dfn[v]?u:v;}
int lca(int u,int v){
	if(u==v)return u;
	u=dfn[u],v=dfn[v];
	if(u>v)swap(u,v);u++;
	int k=__lg(v-u+1);
	return mmax(st[k][u],st[k][v-(1<<k)+1]);
}
#define lb(x) (x&(-x))
struct bit{
	int tree[maxn];
	void upd(int x,int w){
		while(x<=n)tree[x]+=w,x+=lb(x);
	}
	void upd(int l,int r,int w){
		upd(l,w),upd(r+1,-w);
	}
	int que(int x){
		int res=0;
		while(x)res+=tree[x],x-=lb(x);
		return res;
	}
}t;
void upd(int u,int v,int w,int o=0){
	while(tp[u]!=tp[v]){
		t.upd(dfn[tp[u]],dfn[u],w);
		u=fa[tp[u]];
	}
	if(dfn[v]+o<=dfn[u])t.upd(dfn[v]+o,dfn[u],w);
}
int in[maxn],out[maxn],tim,pos[maxn];
void dfs1(int u,int fa){
	siz[u]=1,son[u]=0;in[u]=++tim,pos[tim]=u;
	up2[u][0]=fa;for(int i=1;i<=16;i++)up2[u][i]=up2[up2[u][i-1]][i-1];
	for(int v:e[u]){
		dfs1(v,u);siz[u]+=siz[v];
		if(siz[v]>siz[son[u]])son[u]=v;
	}
	out[u]=tim;
}
set<pii> s[maxn];
void upd(int u,int w){
	int c=a[u];
	if(w==-1)s[c].erase({dfn[u],u});
	if(!s[c].size())upd(u,1,w);
	else{
		auto it=s[c].lower_bound({dfn[u],u});
		if(it==s[c].end()||it==s[c].begin()){
			int p=lca((*s[c].begin()).se,(*--s[c].end()).se);
			int nw=lca(u,p);
			if(nw==p){
				int p1=lca((*s[c].begin()).se,u),p2=lca((*--s[c].end()).se,u);
				if(dep[p1]>dep[p2])swap(p1,p2);
				upd(u,p2,w,1);
			}
			else if(u==nw){}
			else upd(u,nw,w,1);
		}
		else{
			int p1=(*it).se;it--;int p2=(*it).se;
			p1=lca(p1,u),p2=lca(p2,u);
			if(dep[p1]>dep[p2])swap(p1,p2);
			upd(u,p2,w,1);
		}
	}
	if(w==1)s[c].insert({dfn[u],u});
}
vector<pii> que[maxn];int ans[maxn];
void dfs2(int u,bool fl=0){
	for(int v:e[u]){
		if(v!=son[u])dfs2(v,0);
	}
	if(son[u])dfs2(son[u],1);
	for(int v:e[u])if(v!=son[u]){
		for(int j=in[v];j<=out[v];j++){
			int p=pos[j];
			upd(p,1);
		}
	}
	upd(u,1);
	// cout<<u<<"\n";
	// for(int i=1;i<=n;i++)cout<<t.que(rnk[i])<<" ";cout<<"\n";
	for(auto[y,id]:que[u])ans[id]=t.que(dfn[y]);
	if(!fl){
		for(int j=in[u];j<=out[u];j++){
			int p=pos[j];
			upd(p,-1);
		}
	}
}
void work(){
	n=read();q=read();
	for(int i=1;i<=n;i++)a[i]=read();
	vector<pii> edge;
	for(int i=1;i<n;i++){
		int u=read(),v=read();
		edge.pb({u,v});
	}
	for(int i=1;i<=n;i++)ff[i]=i;
	sort(edge.begin(),edge.end(),[&](pii u,pii v){return min(u.fi,u.se)>min(v.fi,v.se);});
	for(auto[u,v]:edge){
		u=fd(u),v=fd(v);
		if(u>v)swap(u,v);
		ff[v]=u;e[u].pb(v);
		// cout<<u<<" "<<v<<" e\n";
	}
	dfs(1),dfs(1,1);
	for(int j=1;j<=16;j++){
		for(int i=1;i+(1<<j)-1<=n;i++)st[j][i]=mmax(st[j-1][i],st[j-1][i+(1<<j-1)]);
	}
	for(int i=1;i<=n;i++)e[i].clear();
	sort(edge.begin(),edge.end(),[&](pii u,pii v){return max(u.fi,u.se)<max(v.fi,v.se);});
	for(int i=1;i<=n;i++)ff[i]=i;
	for(auto[u,v]:edge){
		u=fd(u),v=fd(v);
		if(u>v)swap(u,v);
		ff[u]=v;e[v].pb(u);
		// cout<<v<<" "<<u<<" g\n";
	}
	dfs1(n,0);
	for(int i=1;i<=q;i++){
		int l=read(),r=read(),x=read();
		int x1=x;for(int j=16;~j;j--)if(up1[x1][j]&&up1[x1][j]>=l)x1=up1[x1][j];
		int x2=x;for(int j=16;~j;j--)if(up2[x2][j]&&up2[x2][j]<=r)x2=up2[x2][j];
		// cout<<x1<<" "<<x2<<"\n";
		que[x2].pb({x1,i});
	}
	dfs2(n,1);
	for(int i=1;i<=q;i++)printf("%lld\n",ans[i]);
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