// Problem: CF1866J Jackets and Packets
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/CF1866J
// Memory Limit: 500 MB
// Time Limit: 2000 ms
// Written by yhm.
// Start codeing:2025-11-05 15:03:49
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
const int maxn=410;
const int inf=1e18;
bool mbe;

int n,x,y;
int a[maxn],b[maxn],c[maxn];
int dp[maxn][maxn],f[maxn][maxn],g[maxn][maxn];
void work(){
	n=read();x=read();y=read();
	for(int i=1;i<=n;i++)c[i]=read();
	int nn=n;n=0;
	for(int i=1;i<=nn;i++){
		if(c[i]!=c[i-1])a[++n]=c[i],b[n]=1;
		else b[n]++;
	}
	memset(dp,0x3f,sizeof(dp));
	for(int i=1;i<=n+1;i++)dp[i][i-1]=0;
	for(int i=n;i;i--){
		f[i][i]=2*b[i]*y;g[i][i]=b[i]*y;
		for(int j=i+1;j<=n;j++)if(a[i]==a[j]){
			f[i][j]=g[i][j]=inf;
			for(int k=i;k<j;k++)if(a[i]==a[k]){
				f[i][j]=min(f[i][j],f[i][k]+dp[k+1][j-1]+2*b[j]*y);
				g[i][j]=min(g[i][j],g[i][k]+dp[k+1][j-1]+b[j]*y);
			}
			// cout<<i<<" "<<j<<" "<<f[i][j]<<" "<<g[i][j]<<"\n";
		}
		dp[i][i]=x;
		for(int j=i+1;j<=n;j++){
			for(int k=i;k<j;k++)dp[i][j]=min(dp[i][j],dp[i][k]+dp[k+1][j]);
			if(a[i]==a[j]){
				dp[i][j]=min(dp[i][j],f[i][j]-2*b[j]*y+x);
				dp[i][j]=min(dp[i][j],g[i][j]+x);
			}
			// cout<<i<<" "<<j<<" "<<dp[i][j]<<"\n";
		}
	}
	printf("%lld\n",dp[1][n]);
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