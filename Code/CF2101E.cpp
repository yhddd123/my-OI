// Problem: E. Kia Bakes a Cake
// Contest: Codeforces - Codeforces Round 1024 (Div. 1)
// URL: https://codeforces.com/problemset/problem/2101/E
// Memory Limit: 512 MB
// Time Limit: 6000 ms
// Written by yhm.
// Start codeing:2025-09-06 10:23:37
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
inline int read(){int x=0,f=1;char c=getchar();while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}while(c>='0'&&c<='9'){x=(x<<3)+(x<<1)+c-48;c=getchar();}return x*f;}
inline void write(int x){static char buf[20];static int len=-1;if(x<0)putchar('-'),x=-x;do buf[++len]=x%10,x/=10;while(x);while(len>=0)putchar(buf[len--]+48);}
const int maxn=70010;
bool mbe;

int n,lg,ans[maxn];
char s[maxn];
int id[maxn],m;
int f[maxn],g[maxn];
vector<int> e[maxn];
int siz[maxn],w[maxn],rt,sum;
bool vis[maxn];
void getrt(int u,int fa){
	siz[u]=1,w[u]=0;
	for(int v:e[u]){
		if(v==fa||vis[v])continue;
		getrt(v,u),siz[u]+=siz[v];
		w[u]=max(w[u],siz[v]);
	}
	w[u]=max(w[u],sum-siz[u]);
	if(w[u]<=sum/2)rt=u;
}
#define lb(x) (x&(-x))
int mx[maxn];
void upd(int x,int w){
	if(x<=0)return ;
	while(x)mx[x]=max(mx[x],w),x-=lb(x);
}
void clr(int x){
	if(x<=0)return ;
	while(x)mx[x]=-n,x-=lb(x);
}
int que(int x){
	int res=-n;while(x<=n)res=max(res,mx[x]),x+=lb(x);
	return res;
}
int d[maxn];
int dfn[maxn],rnk[maxn],idx;
void dfs(int u,int fa){
	siz[u]=1;rnk[dfn[u]=++idx]=u;
	for(int v:e[u]){
		if(v==fa||vis[v])continue;
		d[v]=d[u]+1;dfs(v,u);siz[u]+=siz[v];
	}
}
void sovle(int u){
	vis[u]=1;d[u]=0;idx=0;dfs(u,0);
	if(u<=m){
		for(int i=2;i<=siz[u];i++){
			int p=rnk[i];if(p>m)continue;
			if(d[p]<=g[p])f[u]=max(f[u],d[p]);
			if(d[p]<=g[u])f[p]=max(f[p],d[p]);
		}
	}
	for(int v:e[u])if(!vis[v]){
		for(int i=dfn[v];i<dfn[v]+siz[v];i++){
			int p=rnk[i];if(p>m)continue;
			f[p]=max(f[p],d[p]+que(d[p]));
		}
		for(int i=dfn[v];i<dfn[v]+siz[v];i++){
			int p=rnk[i];if(p>m)continue;
			upd(g[p]-d[p],d[p]);
		}
	}
	for(int i=2;i<=siz[u];i++){
		int p=rnk[i];if(p>m)continue;
		clr(g[p]-d[p]);
	}
	reverse(e[u].begin(),e[u].end());
	for(int v:e[u])if(!vis[v]){
		for(int i=dfn[v];i<dfn[v]+siz[v];i++){
			int p=rnk[i];if(p>m)continue;
			f[p]=max(f[p],d[p]+que(d[p]));
		}
		for(int i=dfn[v];i<dfn[v]+siz[v];i++){
			int p=rnk[i];if(p>m)continue;
			upd(g[p]-d[p],d[p]);
		}
	}
	for(int i=2;i<=siz[u];i++){
		int p=rnk[i];if(p>m)continue;
		clr(g[p]-d[p]);
	}
	for(int v:e[u])if(!vis[v]){
		sum=siz[v];getrt(v,u);sovle(rt);
	}
}
void work(){
	n=read();scanf("%s",s+1);lg=__lg(n)+1;
	m=0;for(int i=1;i<=n;i++)if(s[i]=='1')id[i]=++m;
	for(int i=1,mm=m;i<=n;i++)if(s[i]=='0')id[i]=++mm;
	for(int i=1;i<=n;i++)e[i].clear();
	for(int i=1;i<n;i++){
		int u=id[read()],v=id[read()];
		e[u].pb(v),e[v].pb(u);
	}
	for(int i=1;i<=n;i++)ans[i]=-1;
	for(int i=1;i<=m;i++)g[i]=n,ans[i]=1;
	for(int i=1;i<=n;i++)mx[i]=-n;
	for(int j=1;j<=lg;j++){
		for(int i=1;i<=n;i++)f[i]=vis[i]=0;
		sum=n;getrt(1,0);sovle(rt);
		// for(int i=1;i<=m;i++)cout<<f[i]<<" ";cout<<"\n";
		for(int i=1;i<=m;i++){
			if(f[i])ans[i]=j+1,f[i]/=2;
			g[i]=f[i];
		}
	}
	for(int i=1;i<=n;i++)write(ans[id[i]]),putchar(' ');puts("");
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