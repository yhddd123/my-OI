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

int n,d[maxn];
vector<int> e[maxn];
int f[maxn],g[maxn];
void dfs(int u,int fa){
	f[u]=g[u]=0;
	int g0=0,g1=0,sg=0;
	for(int v:e[u])if(v!=fa){
		dfs(v,u);
		f[u]+=f[v];sg+=g[v];
		g1=min(g0+f[v],g1+g[v]);
		g0+=g[v];
	}
	g[u]=min(g0,g1);
	if(d[u]>2)f[u]=inf;
	else if(d[u]==2)g[u]=sg;
	else g[u]=1;
	// cout<<u<<" "<<f[u]<<" "<<g[u]<<"\n";
}
void work(){
	n=read();
	for(int i=1;i<n;i++){
		int u=read()+1,v=read()+1;
		d[u]++,d[v]++;
		e[u].pb(v),e[v].pb(u);
	}
	int rt=0;for(int i=1;i<=n;i++)if(d[i]>2)rt=i;
	if(!rt){puts("1");return ;}
	dfs(rt,0);
	printf("%lld\n",g[rt]);
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