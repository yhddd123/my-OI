// Problem: P6782 [Ynoi2008] rplexq
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P6782
// Memory Limit: 128 MB
// Time Limit: 1000 ms
// Written by yhm.
// Start codeing:2026-01-23 09:18:20
// 
// Powered by CP Editor (https://cpeditor.org)

#include<bits/stdc++.h>
#define ll long long
#define mod 998244353ll
#define pii pair<int,int>
#define fi first
#define se second
#define pb push_back
#define db long double
#define mems(a,x) memset((a),(x),sizeof(a))
using namespace std;
static char buf[1000000],*p1=buf,*p2=buf;
#define getchar() p1==p2&&(p2=(p1=buf)+fread(buf,1,1000000,stdin),p1==p2)?EOF:*p1++
inline int read(){int x=0,f=1;char c=getchar();while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}while(c>='0'&&c<='9'){x=(x<<3)+(x<<1)+c-48;c=getchar();}return x*f;}
const int maxn=200010;
const int inf=1e9;
bool mbe;

int n,q,rt;
vector<int> e[maxn];
ll ans[maxn];
const int B=200;
const int maxm=maxn/B+5;
int siz[maxn],fa[maxn];
bool vis[maxn];
void dfs(int u,int fa){
	siz[u]=1;::fa[u]=fa;
	for(int v:e[u])if(v!=fa)dfs(v,u),siz[u]+=siz[v];
	sort(e[u].begin(),e[u].end());
	if(fa)e[u].erase(lower_bound(e[u].begin(),e[u].end(),fa));
	sort(e[u].begin(),e[u].end(),[&](int u,int v){return siz[u]>siz[v];});
	for(int i=0;i<e[u].size()&&i<B;i++)vis[e[u][i]]=1;
}
struct DS{
	const int BB=450;
	int n,pl[maxm],pr[maxm],num,bel[maxn];
	int s1[maxm],s2[maxn];
	void init(int _n){
		n=_n;
		for(int l=1,r;l<=n;l=r+1){
			r=min(l+BB-1,n);pl[++num]=l,pr[num]=r;
			for(int i=l;i<=r;i++)bel[i]=num;
		}
	}
	void upd(int p,int w){
		for(int i=bel[p]+1;i<=num;i++)s1[i]+=w;
		for(int i=p;i<=pr[bel[p]];i++)s2[i]+=w;
	}
	inline int que(int p){return s1[bel[p]]+s2[p];}
	inline int que(int l,int r){return que(r)-que(l-1);}
}ds;
struct node{
	int l,r,id;
};
vector<node> ask[maxn];
int tmp1[maxn],tmp2[maxn];
inline ll C(int n){return 1ll*n*(n-1)/2;}
void dfs(int u){
	if(vis[u]){
		for(auto[l,r,id]:ask[fa[u]])tmp1[id]=ds.que(l,r);
	}
	for(auto[l,r,id]:ask[u])tmp2[id]=ds.que(l,r);
	ds.upd(u,1);
	for(int v:e[u])dfs(v);
	if(vis[u]){
		for(auto[l,r,id]:ask[fa[u]])tmp1[id]=ds.que(l,r)-tmp1[id],ans[id]-=C(tmp1[id]);
	}
	for(auto[l,r,id]:ask[u])tmp2[id]=ds.que(l,r)-tmp2[id],ans[id]+=C(tmp2[id]);
}
int st[maxn],tp;
void dfs1(int u){
	st[++tp]=u;
	for(int v:e[u])dfs1(v);
}
int t[maxn],col[maxn];
void work(){
	n=read();q=read();rt=read();
	for(int i=1;i<n;i++){
		int u=read(),v=read();
		e[u].pb(v),e[v].pb(u);
	}
	dfs(rt,0);
	for(int i=1;i<=q;i++){
		int l=read(),r=read(),u=read();
		ask[u].pb({l,r,i});
	}
	ds.init(n);
	dfs(rt);
	for(int u=1;u<=n;u++)if(e[u].size()>B){
		tp=0;for(int i=B;i<e[u].size();i++){
			int v=e[u][i],lst=tp;
			dfs1(v);
			for(int i=lst+1;i<=tp;i++)col[st[i]]=v;
		}
		sort(st+1,st+tp+1);
		int BB=max(1,(int)sqrt(tp));
		for(auto&[l,r,id]:ask[u]){
			l=lower_bound(st+1,st+tp+1,l)-st;
			r=upper_bound(st+1,st+tp+1,r)-st-1;
		}
		sort(ask[u].begin(),ask[u].end(),[&](node u,node v){
			if(u.l/BB==v.l/BB){
				return ((u.l/BB)&1)?u.r>v.r:u.r<v.r;
			}
			return u.l<v.l;
		});
		int pl=1,pr=0,res=0;
		auto add=[&](int c){res+=(t[c]++);};
		auto del=[&](int c){res-=(--t[c]);};
		for(auto[l,r,id]:ask[u]){
			while(pl>l)add(col[st[--pl]]);
			while(pr<r)add(col[st[++pr]]);
			while(pl<l)del(col[st[pl++]]);
			while(pr>r)del(col[st[pr--]]);
			ans[id]-=res;
		}
		for(int i=1;i<=tp;i++)t[col[st[i]]]=0;
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