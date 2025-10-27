#include<bits/stdc++.h>
// #define int long long
#define ull unsigned long long
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

int n,q;
int head[maxn],tot;
struct nd{
	int nxt,to;ull w;
}e[maxn<<1];
void add(int u,int v,ull w){
	e[++tot]={head[u],v,w};head[u]=tot;}
vector<pii> g[maxn];
mt19937_64 rnd(time(0));
int dep[maxn],dfn[maxn],idx,st[17][maxn];
ull a[maxn];
void dfs(int u,int fa){
	st[0][dfn[u]=++idx]=fa;dep[u]=dep[fa]+1;
	for(int i=head[u];i;i=e[i].nxt){
		int v=e[i].to;if(v==fa)continue;
		a[v]=a[u]^e[i].w;dfs(v,u);
	}
}
inline int mmax(int u,int v){return dfn[u]<dfn[v]?u:v;}
int lca(int u,int v){
	if(u==v)return u;
	u=dfn[u],v=dfn[v];if(u>v)swap(u,v);u++;
	int k=__lg(v-u+1);
	return mmax(st[k][u],st[k][v-(1<<k)+1]);
}
inline int dis(int u,int v){
	if(!u||!v)return 0;
	return dep[u]+dep[v]-2*dep[lca(u,v)];}
struct ds{
	struct node{
		int u,v,d;
		node(int _u=0,int _v=0){u=_u,v=_v,d=dis(u,v);}
		bool operator<(const node&tmp)const{return d<tmp.d;}
	};
	void merge(node &u,int p){u=max({u,node(u.u,p),node(u.v,p),node(p,p)});}
	unordered_map<ull,node> mp;
	node mx;
	void ins(int p){
		if(mp.find(a[p])==mp.end())mp[a[p]]=node(p,p);
		else merge(mp[a[p]],p);
		mx=max(mx,mp[a[p]]);
		// cout<<p<<" "<<mp[a[p]].u<<" "<<mp[a[p]].v<<" "<<mp[a[p]].d<<"\n";
	}
	void clr(){
		mp.clear(),mx=node(0,0);
	}
}f;
int stk[maxn],tp;
void dfs(int u,int fa,int ed){
	stk[++tp]=u;
	if(stk[tp]==ed)return ;
	for(int i=head[u];i;i=e[i].nxt){
		int v=e[i].to;if(v==fa)continue;
		dfs(v,u,ed);
		if(stk[tp]==ed)return ;
	}
	tp--;
}
int ans[maxn];
bool bk[maxn];
vector<int> id[maxn];int s;
void dfs1(int u,int fa){
	id[s].pb(u);
	for(int i=head[u];i;i=e[i].nxt){
		int v=e[i].to;if(v==fa)continue;
		dfs1(v,u);
	}
}
void work(){
	n=read();q=read();
	for(int i=1;i<n;i++){
		int u=read(),v=read(),w=read();
		g[w].pb({u,v});
	}
	for(int i=1;i<=n;i++)if(g[i].size()){
		ull s=0;
		for(int j=0;j+1<g[i].size();j++){
			ull w=rnd();s^=w;
			add(g[i][j].fi,g[i][j].se,w),add(g[i][j].se,g[i][j].fi,w);
		}
		add(g[i].back().fi,g[i].back().se,s),add(g[i].back().se,g[i].back().fi,s);
	}
	dfs(1,0);
	for(int j=1;j<=16;j++){
		for(int i=1;i+(1<<j)-1<=n;i++)st[j][i]=mmax(st[j-1][i],st[j-1][i+(1<<j-1)]);
	}
	for(int i=1;i<=n;i++)f.ins(i);
	auto[u,v,d]=f.mx;
	dfs(u,0,v);
	// for(int i=1;i<=n;i++)cout<<a[i]<<" ";cout<<"\n";
	// cout<<u<<" "<<v<<" "<<d<<"\n";
	for(int i=1;i<=tp;i++)bk[stk[i]]=1;
	for(int i=1;i<=n;i++)if(!bk[i])ans[i]=d;
	f.clr();
	for(int ii=1;ii<=tp;ii++){
		int u=stk[ii];
		for(int i=head[u];i;i=e[i].nxt){
			int v=e[i].to;if(bk[v])continue;
			s=v;dfs1(v,u);
		}
	}
	for(int ii=1;ii<=tp;ii++){
		int u=stk[ii];
		for(int i=head[u];i;i=e[i].nxt){
			int v=e[i].to;if(bk[v])continue;
			for(int p:id[v])f.ins(p);
			ans[u]=max(ans[u],f.mx.d);f.clr();
		}
	}
	for(int ii=1;ii<tp;ii++){
		int u=stk[ii];f.ins(u);
		for(int i=head[u];i;i=e[i].nxt){
			int v=e[i].to;if(bk[v])continue;
			for(int p:id[v])f.ins(p);
		}
		ans[stk[ii+1]]=max(ans[stk[ii+1]],f.mx.d);
	}
	f.clr();
	for(int ii=tp;ii>1;ii--){
		int u=stk[ii];f.ins(u);
		for(int i=head[u];i;i=e[i].nxt){
			int v=e[i].to;if(bk[v])continue;
			for(int p:id[v])f.ins(p);
		}
		ans[stk[ii-1]]=max(ans[stk[ii-1]],f.mx.d);
	}
	while(q--){
		int u=read();
		printf("%d\n",ans[u]);
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