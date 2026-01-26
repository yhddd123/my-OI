// Problem: P12059 [THUPC 2025 决赛] I'm Here
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P12059
// Memory Limit: 768 MB
// Time Limit: 2500 ms
// Written by yhm.
// Start codeing:2026-01-26 08:07:54
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
const int maxn=85;
const int inf=1e9;
bool mbe;

int n;
vector<int> e[maxn];
int siz[maxn];
int C[maxn][maxn];
int f[maxn][maxn],g[maxn][maxn][maxn];
int tmp[maxn];
void work(){
	n=read();
	for(int i=1;i<n;i++){
		int u=read(),v=read();
		if(u>v)swap(u,v);
		e[u].pb(v);
	}
	for(int i=0;i<=n;i++){
		C[i][0]=1;for(int j=1;j<=i;j++)C[i][j]=(C[i-1][j]+C[i-1][j-1])%mod;
	}
	for(int u=n;u;u--){
		f[u][0]=1;
		for(int v:e[u]){
			for(int i=0;i<=siz[u];i++){
				for(int j=0;j<=siz[v];j++)(tmp[i+j]+=C[i+j][i]*f[u][i]%mod*(f[v][j]+(j?f[v][j-1]:0)))%=mod;
			}
			siz[u]+=siz[v];
			for(int i=0;i<=siz[u];i++)f[u][i]=tmp[i],tmp[i]=0;
		}
		siz[u]++;
	}
	// for(int u=1;u<=n;u++){
		// for(int i=0;i<=siz[u];i++)cout<<val[u][i]<<" ";cout<<"\n";
	// }
	g[n+1][0][0]=1;
	for(int u=n;u;u--){
		for(int i=0;i<=n-u;i++){
			for(int j=i;j<=n;j++)if(g[u+1][i][j]){
				if(u>1)(g[u][i][j]+=g[u+1][i][j])%=mod;
				for(int k=j+1;k<=n-u+1;k++)(g[u][i+1][k]+=g[u+1][i][j])%=mod;
			}
		}
		if(u>1){
			for(int i=0;i<=n-(u+siz[u]-1);i++){
				for(int j=i;j<=n;j++)if(g[u+siz[u]][i][j]){
					for(int p=0;p<siz[u];p++)(g[u][i+p+1][j]+=g[u+siz[u]][i][j]*f[u][p]%mod*C[j-i][p+1])%=mod;
				}
			}
		}
	}
	for(int i=1;i<=n;i++)printf("%d ",g[1][i][i]);
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