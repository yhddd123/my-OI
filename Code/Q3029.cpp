#include<bits/stdc++.h>
#define int long long
#define mod 998244353ll
#define pii pair<int,int>
#define fi first
#define se second
#define mems(x,y) memset(x,y,sizeof(x))
using namespace std;
const int maxn=1500010;
const int inf=1e18;
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch-48);ch=getchar();}
	return x*f;
}
bool Mbe;

int n,m,k,p;
pii a[maxn];int h[maxn];
struct edge{
	int u,v,w;
}E[maxn];
namespace krus{
	int f[maxn],idx,tim[maxn];
	int fd(int x){
		if(f[x]==x)return x;
		return f[x]=fd(f[x]);
	}
	int to[21][maxn],dep[maxn];
	void kru(){
		sort(E+1,E+m+1,[&](edge u,edge v){
			return u.w>v.w;
		});
		for(int i=1;i<=2*n;i++)f[i]=i;idx=n;
		for(int i=1;i<=m;i++){
			int u=fd(E[i].u),v=fd(E[i].v);
			if(u==v)continue;
			else f[u]=f[v]=++idx,to[0][u]=to[0][v]=idx,tim[idx]=E[i].w,to[0][idx]=0;
		}
		for(int j=1;j<=20;j++){
			for(int i=1;i<=idx;i++)to[j][i]=to[j-1][to[j-1][i]];
		}
		for(int i=idx;i;i--)dep[i]=dep[to[0][i]]+1;
	}
	int lca(int u,int v){
		if(dep[u]<dep[v])swap(u,v);
		for(int i=20;~i;i--)if(dep[to[i][u]]>=dep[v])u=to[i][u];
		if(u==v)return u;
		for(int i=20;~i;i--)if(to[i][u]!=to[i][v])u=to[i][u],v=to[i][v];
		return to[0][u];
	}
	int que(int u,int v){
		int tp=lca(u,v);
		return tim[tp]==inf?-1:tim[tp];
	}
}
int head[maxn],tot;
struct nd{
	int nxt,to,w;
}e[maxn];
void add(int u,int v,int w){e[++tot]={head[u],v,w};head[u]=tot;}
vector<pii> g[maxn];
int d[maxn];set<pii> q;
set<pii> sl[maxn],sr[maxn];
bool chk(int u,int v,int l){
	return (h[u]-h[v])*(h[u]-h[v])+(a[u].fi-a[v].fi)*(a[u].fi-a[v].fi)+(a[u].se-a[v].se)*(a[u].se-a[v].se)<=l*l;
}
int get(int u,int v,int l){
	int len=l*l-(a[u].fi-a[v].fi)*(a[u].fi-a[v].fi)-(a[u].se-a[v].se)*(a[u].se-a[v].se);
	if(len<0)return -inf;
	int ss=sqrtl(len);
	while(ss*ss>len)ss--;
	while((ss+1)*(ss+1)<=len)ss++;
	return ss;
}
void work(){
	for(int i=1;i<=n;i++)head[i]=0;tot=0;
	for(int i=1;i<=n;i++)g[i].clear(),h[i]=d[i]=0,sl[i].clear(),sr[i].clear();
	n=read();
	for(int i=1;i<=n;i++)a[i]={read(),read()};
	m=read();
	for(int i=1;i<=m;i++){
		int u=read(),v=read(),l=read();
		g[u].push_back({v,l}),g[v].push_back({u,l});
		d[u]++,d[v]++;
	}
	for(int i=1;i<=n;i++)q.insert({d[i],i});
	for(int i=1;i<=n;i++){
		int u=(*q.begin()).se;q.erase(q.begin());
		for(auto[v,w]:g[u])if(q.find({d[v],v})!=q.end()){
			add(u,v,w);
			int lim=get(u,v,w);
			// cout<<u<<" "<<v<<" "<<w<<" "<<lim<<"\n";
			if(lim==-inf)E[tot]={u,v,0};
			else E[tot]={u,v,inf},sl[v].insert({-lim,tot}),sr[v].insert({lim,tot});
			q.erase({d[v],v});d[v]--;q.insert({d[v],v});
		}
	}
	k=read();
	for(int t=1;t<=k;t++){
		int u=read(),l=read();
		h[u]+=l;
		while(sl[u].size()&&h[u]<(*--sl[u].end()).fi){
			if(E[(*--sl[u].end()).se].w>k)E[(*--sl[u].end()).se].w=t;
			sl[u].erase(--sl[u].end());
		}
		while(sr[u].size()&&h[u]>(*sr[u].begin()).fi){
			if(E[(*sr[u].begin()).se].w>k)E[(*sr[u].begin()).se].w=t;
			sr[u].erase(sr[u].begin());
		}
		for(int i=head[u];i;i=e[i].nxt){
			int v=e[i].to;if(E[i].w<=k)continue;
			if(!chk(u,v,e[i].w)){
				E[i].w=t;
				int lim=get(u,v,e[i].w);
				sl[v].erase({-lim+h[u]-l,i}),sr[v].erase({lim+h[u]-l,i});
			}
			else{
				int lim=get(u,v,e[i].w);
				sl[v].erase({-lim+h[u]-l,i}),sl[v].insert({-lim+h[u],i});
				sr[v].erase({lim+h[u]-l,i}),sr[v].insert({lim+h[u],i});
			}
		}
	}
	// for(int i=1;i<=m;i++)cout<<E[i].u<<" "<<E[i].v<<" "<<E[i].w<<"\n";
	p=read();krus::kru();
	while(p--){
		int u=read(),v=read();
		printf("%lld\n",krus::que(u,v));
	}
}

// \
444

bool Med;
int T;
signed main(){
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
	
//	ios::sync_with_stdio(0);
//	cin.tie(0);cout.tie(0);
	
	// cerr<<(&Mbe-&Med)/1048576.0<<" MB\n";
	
	T=read();
	while(T--)work();
}
