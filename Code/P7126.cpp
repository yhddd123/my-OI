// Problem: P7126 [Ynoi2008] rdCcot
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P7126
// Memory Limit: 512 MB
// Time Limit: 2000 ms
// Written by yhm.
// Start codeing:2026-01-23 11:35:01
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

int n,q,c;
vector<int> e[maxn];
int dep[maxn],id[maxn],rnk[maxn];
int pl[maxn],pr[maxn];
int siz[maxn],w[maxn],sum,rt;
bool vis[maxn];
void getrt(int u,int fa){
	siz[u]=1,w[u]=0;
	for(int v:e[u])if(v!=fa&&!vis[v]){
		getrt(v,u);siz[u]+=siz[v];
		w[u]=max(w[u],siz[v]);
	}
	w[u]=max(w[u],sum-siz[u]);
	if(w[u]<=sum/2)rt=u;
}
vector<int> idd;
void dfs(int u,int fa){
	siz[u]=1;idd.pb(u);dep[u]=dep[fa]+1;
	for(int v:e[u])if(v!=fa&&!vis[v]){
		dfs(v,u),siz[u]+=siz[v];
	}
}
mt19937 rnd(1);
struct fhq{
	int w[maxn],ls[maxn],rs[maxn],rt;
	int mn[maxn],val[maxn];
	void up(int u){
		mn[u]=min({mn[ls[u]],mn[rs[u]],val[u]});
	}
	int merge(int u,int v){
		if(!u||!v)return u|v;
		if(w[u]<w[v]){
			rs[u]=merge(rs[u],v);
			up(u);
			return u;
		}
		else{
			ls[v]=merge(u,ls[v]);
			up(v);
			return v;
		}
	}
	pii split(int u,int k){
		if(!u)return {0,0};
		if(u>k){
			pii t=split(ls[u],k);
			ls[u]=t.se;
			up(u);
			return {t.fi,u};
		}
		else{
			pii t=split(rs[u],k);
			rs[u]=t.fi;
			up(u);
			return {u,t.se};
		}
	}
	int quer(int u,int w){
		if(!u)return 0;
		if(rs[u]&&mn[rs[u]]<=w)return quer(rs[u],w);
		if(val[u]<=w)return u;
		return quer(ls[u],w);
	}
	int quel(int u,int w){
		if(!u)return n+1;
		if(ls[u]&&mn[ls[u]]<=w)return quel(ls[u],w);
		if(val[u]<=w)return u;
		return quel(rs[u],w);
	}
	void newnode(int u,int v){
		w[u]=rnd();ls[u]=rs[u]=0;
		mn[u]=val[u]=v;
	}
}t;
void sovle(int u){
	vis[u]=1;
	idd.clear();dep[0]=-1;dfs(u,0);
	sort(idd.begin(),idd.end(),[&](int u,int v){return rnk[u]<rnk[v];});
	t.rt=0;
	// cout<<rt<<"\n";
	for(int u:idd)if(dep[u]<=c){
		auto[x,y]=t.split(t.rt,u);
		pl[u]=max(pl[u],t.quer(x,c-dep[u]));
		pr[u]=min(pr[u],t.quel(y,c-dep[u]));
		// cout<<u<<" "<<dep[u]<<" "<<pl[u]<<" "<<pr[u]<<"\n";
		t.newnode(u,dep[u]);
		t.rt=t.merge(x,t.merge(u,y));
	}
	for(int v:e[u])if(!vis[v]){
		sum=siz[v];getrt(v,u);
		sovle(rt);
	}
}
#define lb(x) (x&(-x))
int tree[maxn];
void upd(int x,int w){
	while(x<=n)tree[x]+=w,x+=lb(x);
}
void upd(int l,int r,int w){upd(l,w);upd(r+1,-w);}
int que(int x){
	int res=0;
	while(x)res+=tree[x],x-=lb(x);
	return res;
}
vector<tuple<int,int,int>> mdf[maxn];
vector<pii> ask[maxn];
int ans[maxn<<1];
void work(){
	n=read();q=read();c=read();
	for(int i=2;i<=n;i++){
		int u=read();
		e[u].pb(i),e[i].pb(u);
	}
	dfs(1,0);
	for(int i=1;i<=n;i++)id[i]=i;
	sort(id+1,id+n+1,[&](int u,int v){return dep[u]==dep[v]?u<v:dep[u]<dep[v];});
	for(int i=1;i<=n;i++)rnk[id[i]]=i;
	for(int i=1;i<=n;i++)pl[i]=0,pr[i]=n+1;
	t.mn[0]=n+1;
	sum=n;getrt(1,0);sovle(rt);
	// for(int i=1;i<=n;i++)cout<<pl[i]<<" "<<pr[i]<<"\n";
	for(int i=1;i<=n;i++)mdf[i].pb({pl[i]+1,i,1}),mdf[pr[i]].pb({pl[i]+1,i,-1});
	for(int i=1;i<=q;i++){
		int l=read(),r=read();
		ask[r].pb({l,i});
	}
	for(int i=1;i<=n;i++){
		for(auto[l,r,w]:mdf[i])upd(l,r,w);
		for(auto[l,id]:ask[i])ans[id]=que(l);
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