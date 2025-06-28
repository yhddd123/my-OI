// Problem: AT_agc002_f [AGC002F] Leftmost Ball
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/AT_agc002_f
// Memory Limit: 256 MB
// Time Limit: 2000 ms
// Written by yhm.
// Start codeing:2025-03-11 18:13:29
// 
// Powered by CP Editor (https://cpeditor.org)

#include<bits/stdc++.h>
#define int long long
#define mod 1000000007ll
#define pii pair<int,int>
#define fi first
#define se second
#define pb push_back
#define mems(a,x) memset((a),(x),sizeof(a))
using namespace std;
inline int read(){
	int x=0,fl=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')fl=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
	return x*fl;
}
const int maxn=2010;
const int inf=2e9;
bool mbe;

int n,k;
int fac[maxn*maxn],inv[maxn*maxn];
inline int ksm(int a,int b=mod-2){
	int ans=1;
	while(b){
		if(b&1)ans=ans*a%mod;
		a=a*a%mod;
		b>>=1;
	}
	return ans;
}
int C(int m,int n){return fac[m]*inv[n]%mod*inv[m-n]%mod;}
int dp[maxn][maxn];
void work(){
	n=read();k=read();
	if(k==1){puts("1");return ;}
	fac[0]=1;for(int i=1;i<=n*k;i++)fac[i]=fac[i-1]*i%mod;
	inv[n*k]=ksm(fac[n*k]);for(int i=n*k-1;~i;i--)inv[i]=inv[i+1]*(i+1)%mod;
	dp[0][0]=1;
	for(int i=1;i<=n;i++){
		dp[i][0]=1;
		for(int j=1;j<=i;j++){
			dp[i][j]=(dp[i-1][j]+dp[i][j-1]*(n-j+1)%mod*C(n*k-i-(j-1)*(k-1)-1,k-2))%mod;
		}
	}
	printf("%lld\n",dp[n][n]);
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