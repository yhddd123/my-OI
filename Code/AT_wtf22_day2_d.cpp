// Problem: AT_wtf22_day2_d Cat Jumps
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/AT_wtf22_day2_d
// Memory Limit: 1024 MB
// Time Limit: 2000 ms
// Written by yhm.
// Start codeing:2026-01-29 16:33:18
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

inline int ksm(int a,int b=mod-2){
    int ans=1;
    while(b){
        if(b&1)ans=1ll*ans*a%mod;
        a=1ll*a*a%mod;
        b>>=1;
    }
    return ans;
}
int fac[maxn],inv[maxn];
int C[maxn][maxn],S1[maxn][maxn],S2[maxn][maxn];
void init(int n){
    fac[0]=1;for(int i=1;i<=n;i++)fac[i]=1ll*fac[i-1]*i%mod;
    inv[n]=ksm(fac[n]);for(int i=n-1;~i;i--)inv[i]=1ll*inv[i+1]*(i+1)%mod;
    for(int i=0;i<=n;i++){
    	C[i][0]=1;for(int j=1;j<=i;j++)C[i][j]=(C[i-1][j]+C[i-1][j-1])%mod;
    }
    S1[0][0]=1;
    for(int i=1;i<=n;i++){
    	for(int j=1;j<=i;j++)S1[i][j]=(S1[i-1][j-1]+(i-1)*S1[i-1][j])%mod;
    }
    S2[0][0]=1;
    for(int i=1;i<=n;i++){
    	for(int j=1;j<=n;j++)S2[i][j]=(S2[i-1][j-1]+j*S2[i-1][j])%mod;
    }
}
inline void inc(int &u,int v){((u+=v)>=mod)&&(u-=mod);}
int n,a[maxn],t[maxn];
int ans[maxn],f[maxn],g[maxn],h[maxn],dp[maxn][maxn];
void work(){
	n=read();init(n);
	for(int i=1;i<=n;i++)a[i]=read(),t[a[i]]++;
	int sum=0;for(int i=1;i<=n;i++)sum+=a[i];
	dp[0][0]=1;for(int i=1;i<=n;i++){
		for(int j=0;j<i;j++){
			(dp[i][j+1]+=dp[i-1][j]*(a[i]+1))%=mod;
			(dp[i][j]+=dp[i-1][j]*(mod-j))%=mod;
			(dp[i][j]+=dp[i-1][j]*(sum+i))%=mod;
		}
	}
	for(int i=1;i<=n;i++){
		for(int j=i;j<=n;j++)(h[i]+=dp[n][j]*S1[j][i])%=mod;
	}
	for(int i=1;i<=n;i++){
		for(int j=i;j<=n;j++)(g[i]+=(((j-i)&1)?mod-1:1)*C[j][i]%mod*h[j])%=mod;
	}
	for(int i=1;i<=n;i++){
		for(int j=i;j<=n;j++)(f[i]+=g[j]*S2[j][i])%=mod;
		f[i]=f[i]*fac[i]%mod;
	}
	for(int i=1;i<=n;i++){
		for(int j=i;j<=n;j++)(ans[i]+=(((j-i)&1)?mod-1:1)*C[j-1][i-1]%mod*f[j])%=mod;
	}
	int mul=1;for(int i=1;i<=maxn-10;i++)mul=mul*inv[t[i]]%mod;
	for(int i=1;i<=n;i++)ans[i]=ans[i]*mul%mod;
	for(int i=1;i<=n;i++)printf("%lld\n",ans[i]);
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