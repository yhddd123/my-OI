// Problem: P12445 [COTS 2025] 数好图 / Promet
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P12445
// Memory Limit: 1024 MB
// Time Limit: 2000 ms
// Written by yhm.
// Start codeing:2025-06-12 09:13:04
// 
// Powered by CP Editor (https://cpeditor.org)

#include<bits/stdc++.h>
#define int long long
// #define mod 998244353ll
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
const int maxn=2010;
const int inf=1e9;
bool mbe;

int n,mod,ans[maxn];
int c[maxn][maxn],pw[maxn];
int dp[maxn][maxn],val[maxn],f[maxn][maxn],g[maxn][maxn];
void work(){
	n=read();mod=read();
	pw[0]=1;for(int i=1;i<=n;i++)pw[i]=pw[i-1]*2%mod;
	for(int i=0;i<=n;i++){
		c[i][0]=1;for(int j=1;j<=i;j++)c[i][j]=(c[i-1][j]+c[i-1][j-1])%mod;
	}
	dp[1][0]=1;for(int i=2;i<=n;i++){
		for(int j=0;j<i;j++){
			dp[i][j]=((dp[i-1][j]+(j?dp[i-1][j-1]:0))*(pw[i-1-j]-1))%mod;
			(val[i]+=((j&1)?mod-1:1)*dp[i][j])%=mod;
		}
	}
	// for(int i=2;i<=n;i++)cout<<val[i]<<" ";cout<<"\n";
	f[n][0]=1;
	for(int i=n-1;i>=2;i--){
		for(int j=0;j<=n-i;j++)f[i][j]=(f[i+1][j]+(j?f[i+1][j-1]:0)*pw[n-i])%mod;
	}
	g[1][1]=1;
	for(int i=2;i<=n;i++){
		for(int j=1;j<=i;j++)g[i][j]=(g[i-1][j-1]+g[i-1][j]*(pw[i-1]-1))%mod;
	}
	for(int i=2;i<=n;i++){
		for(int j=0;j<=n-i;j++)(ans[i]+=f[2][j]*g[n-j-1][i-1])%=mod;
		ans[i]=ans[i]*val[i]%mod;
	}
	ans[0]=ans[2];ans[1]=0;
	for(int i=0;i<=n;i++)printf("%lld ",ans[i]);
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