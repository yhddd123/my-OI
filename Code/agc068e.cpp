// Problem: AT_agc068_e [AGC068E] Sort and Match
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/AT_agc068_e
// Memory Limit: 1024 MB
// Time Limit: 2000 ms
// Written by yhm.
// Start codeing:2026-01-21 20:49:32
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
const int maxn=55;
const int inf=1e9;
bool mbe;

int n,m,a[maxn][maxn];
int f[maxn][maxn],dp[maxn],ans[maxn];
void work(){
	n=read();m=read();
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++)a[i][j]=read();
	}
	dp[0]=1;
	for(int i=n;i;i--){
		mems(f,0);
		for(int j=0;j<=m;j++)f[j][i]=dp[j];
		for(int j=0;j<m;j++){
			for(int u=i;u<=n;u++){
				for(int v=i;v<=n;v++)(f[j+1][v]+=f[j][u]*a[u][v])%=mod;
			}
		}
		for(int u=i;u<=n;u++)(ans[u]+=f[m-1][u]*a[u][i])%=mod;
		for(int j=0;j<=m;j++)dp[j]=f[j][i];
		// for(int j=0;j<=m;j++)cout<<dp[j]<<" ";cout<<"\n";
	}
	for(int i=1;i<=n;i++)printf("%lld ",ans[i]);
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