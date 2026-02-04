// Problem: AT_agc038_e [AGC038E] Gachapon
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/AT_agc038_e
// Memory Limit: 1024 MB
// Time Limit: 3000 ms
// Written by yhm.
// Start codeing:2026-02-04 14:59:27
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
int n,a[maxn],b[maxn],sa,sb,ans;
int f[maxn][maxn][maxn];
int C[maxn][maxn],pw[maxn][maxn];
inline void inc(int &u,int v){((u+=v)>=mod)&&(u-=mod);}
void work(){
	n=read();
	for(int i=1;i<=n;i++){
		a[i]=read(),sa+=a[i];
		b[i]=read(),sb+=b[i];
	}
	for(int i=0;i<=maxn-10;i++){
		C[i][0]=1;for(int j=1;j<=i;j++)inc(C[i][j]=C[i-1][j],C[i-1][j-1]);
	}
	for(int i=0;i<=maxn-10;i++){
		pw[i][0]=1;for(int j=1;j<=maxn-10;j++)pw[i][j]=pw[i][j-1]*i%mod;
	}
	f[0][0][0]=mod-1;
	for(int i=1,s0=0,s1=0;i<=n;s0+=a[i],s1+=b[i],i++){
		for(int j=0;j<=s0;j++){
			for(int k=0;k<=s1;k++)if(f[i-1][j][k]){
				inc(f[i][j][k],f[i-1][j][k]);
				for(int l=0;l<b[i];l++){
					inc(f[i][j+a[i]][k+l],mod-f[i-1][j][k]*C[k+l][l]%mod*pw[a[i]][l]%mod);
				}
			}
		}
	}
	for(int j=0;j<=sa;j++){
		for(int k=0;k<=sb;k++)if(f[n][j][k]){
			(ans+=sa*f[n][j][k]%mod*ksm(pw[j][k+1]))%=mod;
			// cout<<j<<" "<<k<<" "<<f[n][j][k]<<"\n";
		}
	}
	printf("%lld\n",ans);
}

bool med;
int T;
signed main(){
	// freopen(".in","r",stdin);
	// freopen(".out","w",stdout);
	
	cerr<<(&mbe-&med)/1024.0/1024.0<<"\n";
	
	T=1;
	while(T--)work();
}