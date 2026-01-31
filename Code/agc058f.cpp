// Problem: AT_agc058_f [AGC058F] Authentic Tree DP
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/AT_agc058_f
// Memory Limit: 1024 MB
// Time Limit: 2000 ms
// Written by yhm.
// Start codeing:2026-01-30 08:49:39
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
const int maxn=5010;
const int inf=1e9;
bool mbe;

int n,ans;
vector<int> e[maxn];
int f[maxn][maxn],siz[maxn],g[maxn],ni[maxn];
void dfs(int u,int fa){
	f[u][1]=1;siz[u]=1;
	for(int v:e[u])if(v!=fa){
		dfs(v,u);
		for(int j=1;j<=siz[u];j++){
			for(int k=1;k<=siz[v];k++){
				(g[j]+=ni[k]*ni[k]%mod*f[u][j]%mod*f[v][k])%=mod;
				(g[j+k]+=mod-ni[k]*ni[k]%mod*f[u][j]%mod*f[v][k]%mod)%=mod;
			}
		}
		siz[u]+=siz[v];
		for(int j=1;j<=siz[u];j++)f[u][j]=g[j],g[j]=0;
	}
}
void work(){
	n=read();
	for(int i=1;i<n;i++){
		int u=read(),v=read();
		e[u].pb(v),e[v].pb(u);
	}
	ni[0]=ni[1]=1;for(int i=2;i<=n;i++)ni[i]=(mod-mod/i)*ni[mod%i]%mod;
	dfs(1,0);
	for(int i=1;i<=n;i++)(ans+=f[1][i]*ni[i])%=mod;
	printf("%lld\n",ans);
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