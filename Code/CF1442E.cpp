// Problem: CF1442E Black, White and Grey Tree
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/CF1442E
// Memory Limit: 500 MB
// Time Limit: 2000 ms
// Written by yhm.
// Start codeing:2025-10-24 17:02:12
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
const int maxn=200010;
const int inf=1e9;
bool mbe;

int n,a[maxn],ans;
vector<int> e[maxn];
int f[maxn][2];
void dfs(int u,int fa){
	int g0=0,g1=0;
	f[u][0]=f[u][1]=inf;
	if(a[u]==1||a[u]==0)f[u][0]=g0=0;
	if(a[u]==2||a[u]==0)f[u][1]=g1=0;
	for(int v:e[u])if(v!=fa){
		dfs(v,u);
		g0=max(g0,f[u][0]+min(f[v][0],f[v][1]+1));
		g1=max(g1,f[u][1]+min(f[v][1],f[v][0]+1));
		f[u][0]=max(f[u][0],min(f[v][0],f[v][1]+1));
		f[u][1]=max(f[u][1],min(f[v][1],f[v][0]+1));
	}
	ans=max(ans,min(g0,g1));
}
void work(){
	n=read();ans=0;
	for(int i=1;i<=n;i++)a[i]=read();
	for(int i=1;i<=n;i++)e[i].clear();
	for(int i=1;i<n;i++){
		int u=read(),v=read();
		e[u].pb(v),e[v].pb(u);
	}
	dfs(1,0);
	printf("%lld\n",(ans+1)/2+1);
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