// Problem: P9340 [JOIST 2023] 旅行 / Tourism
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P9340
// Memory Limit: 1024 MB
// Time Limit: 4000 ms
// Written by yhm.
// Start codeing:2026-02-02 08:22:49
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
vector<int> e[maxn];
int fa[maxn],dep[maxn],siz[maxn],son[maxn];
void dfs(int u){
    dep[u]=dep[fa[u]]+1,siz[u]=1,son[u]=0;
    for(int v:e[u])if(v!=fa[u]){
        fa[v]=u;dfs(v),siz[u]+=siz[v];
        if(siz[v]>=siz[son[u]])son[u]=v;
    }
}
int dfn[maxn],rnk[maxn],idx,tp[maxn],ed[maxn];
int st[17][maxn];
void dfs(int u,int lst){
    rnk[dfn[u]=++idx]=u;tp[u]=lst;ed[u]=u;st[0][idx]=fa[u];
    if(!son[u])return ;dfs(son[u],lst);ed[u]=ed[son[u]];
    for(int v:e[u])if(v!=fa[u]&&v!=son[u])dfs(v,v);
}
int mn[17][maxn],mx[17][maxn];
int mmax(int u,int v){return dfn[u]<dfn[v]?u:v;}
int lca(int u,int v){
	if(u==v)return u;
	u=dfn[u],v=dfn[v];
	if(u>v)swap(u,v);u++;
	int k=__lg(v-u+1);
	return mmax(st[k][u],st[k][v-(1<<k)+1]);
}
int quemn(int l,int r){
	int k=__lg(r-l+1);
	return min(mn[k][l],mn[k][r-(1<<k)+1]);
}
int quemx(int l,int r){
	int k=__lg(r-l+1);
	return max(mx[k][l],mx[k][r-(1<<k)+1]);
}
int calc(int l,int r){return lca(rnk[quemn(l,r)],rnk[quemx(l,r)]);}
#define lb(x) (x&(-x))
struct bit{
int tree[maxn];
void upd(int x,int w){
	while(x)tree[x]+=w,x-=lb(x);
}
int que(int x){
	int res=0;
	while(x<=m)res+=tree[x],x+=lb(x);
	return res;
}
}t;
struct node{
	int l,r,c;
	bool operator<(const node&tmp)const{return r<tmp.l;}
};
struct odt{
	set<node> s;
	void split(int p){
		auto it=s.lower_bound({p,p,0});
		if((*it).r>p){
			auto[l,r,c]=*it;
			s.erase(it);
			s.insert({l,p,c}),s.insert({p+1,r,c});
		}
	}
	void ins(int l,int r,int c){
		split(l-1),split(r);
		auto it=s.lower_bound({l,l,0});
		while((*it).r<=r){
			auto[l,r,c]=(*it);
			t.upd(c,-(r-l+1));
			it=s.erase(it);
		}
		s.insert({l,r,c});
		t.upd(c,r-l+1);
	}
	node que(int p){
		auto it=s.lower_bound({p,p,0});
		return (*it);
	}
}s[maxn];
vector<pii> que[maxn];
int ans[maxn];
void work(){
	n=read();m=read();q=read();
	for(int i=1;i<n;i++){
		int u=read(),v=read();
		e[u].pb(v),e[v].pb(u);
	}
	dfs(1),dfs(1,1);
	for(int j=1;j<=16;j++){
		for(int i=1;i+(1<<j)-1<=n;i++)st[j][i]=mmax(st[j-1][i],st[j-1][i+(1<<j-1)]);
	}
	for(int i=1;i<=m;i++)a[i]=read();
	for(int i=1;i<=m;i++)mn[0][i]=mx[0][i]=dfn[a[i]];
	for(int j=1;j<=16;j++){
		for(int i=1;i+(1<<j)-1<=m;i++){
			mn[j][i]=min(mn[j-1][i],mn[j-1][i+(1<<j-1)]);
			mx[j][i]=max(mx[j-1][i],mx[j-1][i+(1<<j-1)]);
		}
	}
	for(int i=1;i<=q;i++){
		int l=read(),r=read();
		que[r].pb({l,i});ans[i]-=dep[calc(l,r)]-1;
	}
	for(int i=1;i<=n;i++)if(tp[i]==i)s[i].s.insert({dfn[i]-1,dfn[ed[i]]+1,0});
	for(int i=1;i<=m;i++){
		int u=a[i];while(u){
			s[tp[u]].ins(dfn[tp[u]],dfn[u],i);
			u=fa[tp[u]];
		}
		for(auto[l,id]:que[i])ans[id]+=t.que(l);
	}
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