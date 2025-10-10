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
static char buf[1000000],*p1=buf,*p2=buf;
#define getchar() p1==p2&&(p2=(p1=buf)+fread(buf,1,1000000,stdin),p1==p2)?EOF:*p1++
inline int read(){int x=0,f=1;char c=getchar();while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}while(c>='0'&&c<='9'){x=(x<<3)+(x<<1)+c-48;c=getchar();}return x*f;}
inline void write(int x){static char buf[20];static int len=-1;if(x<0)putchar('-'),x=-x;do buf[++len]=x%10,x/=10;while(x);while(len>=0)putchar(buf[len--]+48);}
const int maxn=500010;
const int inf=1e9;
bool mbe;

int n;
struct graph{
	vector<int> e[maxn];
	void add(int u,int v){
		e[u].pb(v),e[v].pb(u);
	}
	int siz[maxn],dfn[maxn],rnk[maxn],idx,fa[maxn];
	void dfs(int u){
		siz[u]=1;
		for(int v:e[u])if(v!=fa[u])fa[v]=u,dfs(v),siz[u]+=siz[v];
	}
	void dfs1(int u){
		rnk[dfn[u]=++idx]=u;
		for(int v:e[u])if(v!=fa[u])dfs1(v);
	}
	vector<tuple<int,int,int>> a[maxn];
	void init(){
		dfs(1);
		for(int i=1;i<=n;i++)sort(e[i].begin(),e[i].end(),[&](int u,int v){return siz[u]<siz[v];});
		dfs1(1);
		// for(int i=1;i<=n;i++)cout<<dfn[i]<<" ";cout<<"\n";
		for(int u=1;u<=n;u++){
			a[u].pb({n,dfn[u],dfn[u]});
			for(int v:e[u])if(v!=fa[u])a[u].pb({n-siz[v],dfn[v],dfn[v]+siz[v]-1});
			if(dfn[u]!=1)a[u].pb({siz[u],1,dfn[u]-1});
			if(dfn[u]+siz[u]!=n+1)a[u].pb({siz[u],dfn[u]+siz[u],n});
			// cout<<u<<"\n";
			// for(auto[v,l,r]:a[u])cout<<v<<" "<<l<<" "<<r<<"\n";
		}
	}
}t1,t2;
int ans[maxn];
#define mid ((l+r)>>1)
#define ls nd<<1
#define rs nd<<1|1
int tree[maxn<<2];
void updata(int nd,int l,int r,int ql,int qr,int w){
	if(l>=ql&&r<=qr){tree[nd]+=w;return ;}
	if(ql<=mid)updata(ls,l,mid,ql,qr,w);
	if(qr>mid)updata(rs,mid+1,r,ql,qr,w);
}
int query(int nd,int l,int r,int p){
	if(l==r)return tree[nd];
	if(p<=mid)return query(ls,l,mid,p)+tree[nd];
	else return query(rs,mid+1,r,p)+tree[nd];
}
vector<tuple<int,int,int>> upd[maxn];
void work(){
	n=read();
	for(int i=1;i<n;i++)t1.add(read(),read());
	for(int i=1;i<n;i++)t2.add(read(),read());
	t1.init(),t2.init();
	for(int u=1;u<=n;u++){
		for(int i=0;i<t1.a[u].size();i++){
			auto[v1,l1,r1]=t1.a[u][i];
			for(int j=t2.e[u].size();j<t2.a[u].size();j++){
				auto[v2,l2,r2]=t2.a[u][j];
				if(v1>v2){
					upd[l1].pb({1,l2,r2}),upd[r1+1].pb({-1,l2,r2});
				}
			}
		}
		for(int i=0;i<t2.e[u].size();i++){
			auto[v2,l2,r2]=t2.a[u][i];
			for(int j=t1.e[u].size();j<t1.a[u].size();j++){
				auto[v1,l1,r1]=t1.a[u][j];
				if(v1>v2){
					upd[l1].pb({1,l2,r2}),upd[r1+1].pb({-1,l2,r2});
				}
			}
		}
		for(int i=0,j=0;i<t1.e[u].size();i++){
			auto[v1,l1,r1]=t1.a[u][i];
			while(j<t2.e[u].size()&&v1<=(get<0>(t2.a[u][j])))j++;
			if(j<t2.e[u].size()){
				auto[v2,l2,r2]=t2.a[u][j];
				r2=get<2>(t2.a[u][t2.e[u].size()-1]);
				upd[l1].pb({1,l2,r2}),upd[r1+1].pb({-1,l2,r2});
			}
		}
		// for(auto[v1,l1,r1]:t1.a[u]){
			// for(auto[v2,l2,r2]:t2.a[u])if(v1>v2){
				// upd[l1].pb({1,l2,r2}),upd[r1+1].pb({-1,l2,r2});
			// }
		// }
	}
	for(int i=1;i<=n;i++){
		for(auto[v,l,r]:upd[i])updata(1,1,n,l,r,v);
		ans[t1.rnk[i]]=query(1,1,n,t2.dfn[t1.rnk[i]]);
	}
	for(int i=1;i<=n;i++)write(ans[i]),putchar(' ');
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