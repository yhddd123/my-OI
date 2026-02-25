// Problem: AT_agc065_f [AGC065F] Always Perfect
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/AT_agc065_f
// Memory Limit: 1024 MB
// Time Limit: 2000 ms
// Written by yhm.
// Start codeing:2026-02-25 21:22:47
// 
// Powered by CP Editor (https://cpeditor.org)

#include<bits/stdc++.h>
// #define int long long
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
const int maxn=510;
const int inf=1e9;
bool mbe;

int n,mod,ans;
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
int fac[maxn],inv[maxn],pw2[maxn*maxn],pw[maxn][maxn];
int C(int m,int n){
    if(n<0||m<0||m<n)return 0;
    return 1ll*fac[m]*inv[n]%mod*inv[m-n]%mod;}
void init(int n){
    fac[0]=1;for(int i=1;i<=n;i++)fac[i]=1ll*fac[i-1]*i%mod;
    inv[n]=ksm(fac[n]);for(int i=n-1;~i;i--)inv[i]=1ll*inv[i+1]*(i+1)%mod;
    pw2[0]=1;for(int i=1;i<=n*n;i++)inc(pw2[i]=pw2[i-1],pw2[i-1]);
    for(int i=0;i<=n;i++){
    	pw[i][0]=1;for(int j=1;j<=n;j++)pw[i][j]=1ll*pw[i][j-1]*i%mod;
    }
}
int f[maxn],g[maxn],h[maxn][maxn];
int dp[maxn][maxn];
void work(){
	n=read();mod=read();init(maxn-10);
	for(int i=1;i<=n;i++){
		g[i]=pw2[i*(i-1)/2];
		for(int j=1;j<i;j++)inc(g[i],mod-1ll*C(i-1,j-1)*g[j]%mod*pw2[(i-j)*(i-j-1)/2]%mod);
	}
	h[0][0]=1;
	for(int i=2;i<=n;i++){
		f[i]=g[i];for(int j=2;j<i;j++)inc(f[i],mod-1ll*h[i-1][j]*pw[i][j-1]%mod*fac[i-1]%mod*inv[j]%mod);
		h[i-1][1]=1ll*f[i]*inv[i-1]%mod;
		for(int j=1;j<=i;j++){
			for(int k=1;k<i;k++)inc(h[i][j],1ll*h[i-k][j-1]%mod*f[k+1]%mod*inv[k]%mod);
		}
	}
	// for(int i=1;i<=n;i++)cout<<g[i]<<" ";cout<<"\n";
	// for(int i=1;i<=n;i++)cout<<f[i]<<" ";cout<<"\n";
	dp[0][0]=1;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=i;j++){
			for(int k=2;k<=i;k+=2){
				int coef=k==2?1:1ll*fac[k-1]*(mod+1)/2%mod;
				inc(dp[i][j],1ll*C(i-1,k-1)*dp[i-k][j-1]%mod*coef%mod*k%mod);
			}
		}
	}
	inc(ans,n==2?1:1ll*fac[n-1]*(mod+1)/2%mod);
	for(int x=2;x<=n/2;x++){
		for(int y=1;y<x;y++){
			// cout<<x<<" "<<y<<" "<<dp[n][x]<<" "<<h[x-1][y]<<"\n";
			inc(ans,1ll*dp[n][x]*h[x-1][y]%mod*pw[n][y-1]%mod*fac[x-1]%mod*inv[y]%mod);
		}
	}
	printf("%lld\n",ans);
}

bool med;
signed main(){
	// freopen(".in","r",stdin);
	// freopen(".out","w",stdout);
	
	cerr<<(&mbe-&med)/1024.0/1024.0<<"\n";
	
	int T=1;
	while(T--)work();
}