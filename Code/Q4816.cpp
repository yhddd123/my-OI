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
const int maxn=100010;
const int maxm=35;
const int inf=1e9;
bool mbe;

int n,m,q;
vector<int> e[maxn];
int f[maxn][maxm],g[maxn][maxm];
int ans[maxn][maxm];
inline void inc(int &u,int v){((u+=v)>=mod)&&(u-=mod);}
inline int ksm(int a,int b=mod-2){
    int ans=1;
    while(b){
        if(b&1)ans=1ll*ans*a%mod;
        a=1ll*a*a%mod;
        b>>=1;
    }
    return ans;
}
void dfs(int u,int fa){
	for(int i=0;i<=m;i++)f[u][i]=1;
	for(int v:e[u])if(v!=fa){
		dfs(v,u);
		for(int i=m;i;i--)inc(g[v][i-1],g[v][i]),inc(g[v][i-1],f[v][i]);
		for(int i=1;i<=m;i++)inc(f[v][i],f[v][i-1]);
		for(int i=0;i<=m;i++)inc(g[u][i]=1ll*g[u][i]*f[v][i]%mod,1ll*f[u][i]*g[v][i]%mod);
		for(int i=0;i<=m;i++)f[u][i]=1ll*f[u][i]*f[v][i]%mod;
	}
}
int tfu[maxn][maxm],tfv[maxn][maxm],tgu[maxn][maxm],tgv[maxn][maxm];
int ni[maxm];
void dfs1(int u,int fa){
	for(int i=0;i<=m;i++)inc(ans[u][i]=f[u][i],g[u][i]);
	for(int v:e[u])if(v!=fa){
		for(int i=0;i<=m;i++)tfu[u][i]=f[u][i],tfv[u][i]=f[v][i],tgu[u][i]=g[u][i],tgv[u][i]=g[v][i];
		
		for(int i=0;i<=m;i++)ni[i]=ksm(f[v][i]);
		for(int i=0;i<=m;i++)f[u][i]=1ll*f[u][i]*ni[i]%mod;
		for(int i=0;i<=m;i++)inc(g[u][i],mod-1ll*f[u][i]*g[v][i]%mod),g[u][i]=1ll*g[u][i]*ni[i]%mod;
		for(int i=m;i;i--)inc(f[v][i],mod-f[v][i-1]);
		for(int i=1;i<=m;i++)inc(g[v][i-1],mod-g[v][i]),inc(g[v][i-1],mod-f[v][i]);
		
		swap(u,v);
		for(int i=m;i;i--)inc(g[v][i-1],g[v][i]),inc(g[v][i-1],f[v][i]);
		for(int i=1;i<=m;i++)inc(f[v][i],f[v][i-1]);
		for(int i=0;i<=m;i++)inc(g[u][i]=1ll*g[u][i]*f[v][i]%mod,1ll*f[u][i]*g[v][i]%mod);
		for(int i=0;i<=m;i++)f[u][i]=1ll*f[u][i]*f[v][i]%mod;
		swap(u,v);
		
		dfs1(v,u);
		for(int i=0;i<=m;i++)f[u][i]=tfu[u][i],f[v][i]=tfv[u][i],g[u][i]=tgu[u][i],g[v][i]=tgv[u][i];
	}
}
void work(){
	n=read();m=read();q=read();
	for(int i=1;i<n;i++){
		int u=read(),v=read();
		e[u].pb(v),e[v].pb(u);
	}
	dfs(1,0);
	dfs1(1,0);
	for(int i=1;i<=q;i++){
		int u=read(),v=read();
		printf("%lld\n",ans[u][v]);
	}
}

bool med;
int T;
signed main(){
	// freopen("maxset.in","r",stdin);
	// freopen("maxset.out","w",stdout);
	
	cerr<<(&mbe-&med)/1024.0/1024.0<<"\n";
	
	T=1;
	while(T--)work();
}