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
const int maxn=200010;
const int maxm=300010;
const int inf=1e9;
bool mbe;

int n,m,q,ans;
int head[maxn],tot;
struct nd{
	int nxt,to;
}e[maxn<<1];
void add(int u,int v){e[++tot]={head[u],v};head[u]=tot;}
int st[18][maxn],dfn[maxn],idx;
int to[maxn][18],dep[maxn];
void dfs(int u,int fa){
	st[0][dfn[u]=++idx]=fa;
	to[u][0]=fa,dep[u]=dep[fa]+1;
	for(int i=1;i<18;i++)to[u][i]=to[to[u][i-1]][i-1];
	for(int i=head[u];i;i=e[i].nxt){
		int v=e[i].to;if(v==fa)continue;
		dfs(v,u);
	}
}
int mmax(int u,int v){return dfn[u]<dfn[v]?u:v;}
int lca(int u,int v){
	if(u==v)return u;
	u=dfn[u],v=dfn[v];
	if(u>v)swap(u,v);u++;
	int k=__lg(v-u+1);
	return mmax(st[k][u],st[k][v-(1<<k)+1]);
}
int dis(int u,int v){return dep[u]+dep[v]-2*dep[lca(u,v)];}
int kth(int u,int k){
	for(int i=0;i<18;i++)if(k&(1<<i))u=to[u][i];
	return u;
}
int mov(int u,int v,int k){
	int tp=lca(u,v);
	if(dep[u]-dep[tp]>=k)return kth(u,k);
	return kth(v,dep[u]+dep[v]-2*dep[tp]-k);
}
pii a[maxm],pre[maxm],suf[maxm];
pii merge(pii u,pii v){
	if(u.fi==-1||v.fi==-1)return {-1,-1};
	if(u.se<v.se)swap(u,v);
	int d=dis(u.fi,v.fi);
	if(d>u.se+v.se)return {-1,-1};
	if(u.se>=d+v.se)return v;
	int p=mov(v.fi,u.fi,(d-u.se+v.se)/2);
	return {p,(u.se+v.se-d)/2};
}
int siz[maxn],w[maxn],sum,rt;
bool vis[maxn];
void getrt(int u,int fa){
	siz[u]=1,w[u]=0;
	for(int i=head[u];i;i=e[i].nxt){
		int v=e[i].to;if(v==fa||vis[v])continue;
		getrt(v,u);siz[u]+=siz[v],w[u]=max(w[u],siz[v]);
	}
	w[u]=max(w[u],sum-siz[u]);
	if(w[u]<=sum/2)rt=u;
}
int fa[maxn];
void sovle(int u){
	vis[u]=1;getrt(u,0);
	for(int i=head[u];i;i=e[i].nxt){
		int v=e[i].to;if(vis[v])continue;
		sum=siz[v];getrt(v,u);fa[rt]=u;sovle(rt);
	}
}
vector<int> f[maxn],g[maxn];
int calcf(int u,int d){return (d<0||!f[u].size())?0:(d>=f[u].size()?f[u].back():f[u][d]);}
int calcg(int u,int d){return (d<0||!g[u].size())?0:(d>=g[u].size()?g[u].back():g[u][d]);}
int calc(pii p){
	auto[x,d]=p;
	int u=x,ans=0;
	while(u){
		ans+=calcf(u,d-dis(u,x));
		if(fa[u])ans-=calcg(u,d-dis(fa[u],x));
		u=fa[u];
	}
	// cout<<x<<" "<<d<<" "<<ans<<" c\n";
	return ans;
}
void work(){
	n=read();
	for(int i=1;i<n;i++){
		int u=read(),v=read();
		add(u,n+i),add(n+i,u),add(v,n+i),add(n+i,v);
	}
	dfs(1,0);
	for(int j=1;j<18;j++){
		for(int i=1;i+(1<<j)-1<2*n;i++)st[j][i]=mmax(st[j-1][i],st[j-1][i+(1<<j-1)]);
	}
	sum=2*n;getrt(1,0);sovle(rt);
	for(int i=1;i<=n;i++){
		int u=i;
		while(u){
			int d=dis(u,i);
			if(d>=f[u].size())f[u].resize(d+1);
			f[u][d]++;
			if(fa[u]){
				d=dis(fa[u],i);
				if(d>=g[u].size())g[u].resize(d+1);
				g[u][d]++;
			}
			u=fa[u];
		}
	}
	for(int i=1;i<=2*n;i++){
		for(int j=1;j<f[i].size();j++)f[i][j]+=f[i][j-1];
		for(int j=1;j<g[i].size();j++)g[i][j]+=g[i][j-1];
	}
	q=read();
	while(q--){
		m=read();ans=0;
		for(int i=1;i<=m;i++)a[i]={read(),read()*2};
		pre[0]={1,2*n};for(int i=1;i<=m;i++)pre[i]=merge(pre[i-1],a[i]);
		suf[m+1]={1,2*n};for(int i=m;i;i--)suf[i]=merge(suf[i+1],a[i]);
		// for(int i=1;i<=m;i++)cout<<pre[i].fi<<" "<<pre[i].se<<"\n";
		for(int i=1;i<=m;i++){
			pii p=merge(pre[i-1],suf[i+1]);
			ans+=calc(p);
		}
		ans-=calc(pre[m])*(m-1);
		printf("%d\n",ans);
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