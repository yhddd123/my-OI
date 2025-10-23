// Problem: CF1608F MEX counting
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/CF1608F
// Memory Limit: 250 MB
// Time Limit: 4000 ms
// Written by yhm.
// Start codeing:2025-10-22 15:37:29
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
const int maxn=2010;
const int inf=1e9;
bool mbe;

inline int ksm(int a,int b=mod-2){
    int ans=1;
    while(b){
        if(b&1)ans=ans*a%mod;
        a=a*a%mod;
        b>>=1;
    }
    return ans;
}
int fac[maxn],inv[maxn];
int C(int m,int n){
    if(n<0|m<0||m<n)return 0;
    return fac[m]*inv[n]%mod*inv[m-n]%mod;}
void init(int n){
    fac[0]=1;for(int i=1;i<=n;i++)fac[i]=fac[i-1]*i%mod;
    inv[n]=ksm(fac[n]);for(int i=n-1;~i;i--)inv[i]=inv[i+1]*(i+1)%mod;
}
int n,k,a[maxn],ans;
int f[2][maxn][maxn],cur;
int sum[maxn][maxn];
void work(){
	n=read();k=read();init(n);
	for(int i=1;i<=n;i++)a[i]=read();
	f[0][0][0]=1;
	for(int i=1;i<=n;i++){
		int l1=max(0ll,a[i-1]-k),r1=min(n,a[i-1]+k);
		int l2=max(0ll,a[i]-k),r2=min(n,a[i]+k);
		for(int j=0;j<i;j++){
			for(int k=l1;k<=r1;k++)if(f[cur][j][k]){
				if(l2<=k&&k<=r2){
					(f[i&1][j][k]+=f[cur][j][k]*k)%=mod;
					(f[i&1][j][k]+=f[cur][j][k]*j)%=mod;
					(f[i&1][j+1][k]+=f[cur][j][k])%=mod;
				}
				(sum[j+k+1][j]+=f[cur][j][k]*fac[j])%=mod;
				f[cur][j][k]=0;
			}
		}
		for(int j=l1+1;j<=i+r1&&j<=n;j++){
			int pl=max(0ll,j-r1-1),pr=j-l1-1;
			for(int k=pr-1;k>=pl;k--)(sum[j][k]+=sum[j][k+1])%=mod;
		}
		for(int j=0;j<=i;j++){
			for(int k=l2;k<=r2;k++)if(j+k<=n){
				int pl=max(0ll,j+k-r1-1),pr=j+k-l1-1;
				if(j<=pr)(f[i&1][j][k]+=sum[j+k][max(j,pl)]*inv[j])%=mod;
			}
		}
		for(int j=l1+1;j<=i+r1&&j<=n;j++){
			int pl=max(0ll,j-r1-1),pr=j-l1-1;
			for(int k=pl;k<=pr;k++)sum[j][k]=0;
		}
		cur^=1;
	}
	int l=max(0ll,a[n]-k),r=min(n,a[n]+k);
	for(int j=0;j<=n;j++){
		for(int k=l;k<=r;k++)if(f[n&1][j][k]){
			// cout<<j<<" "<<k<<" "<<f[n&1][j][k]<<"\n";
			(ans+=f[n&1][j][k]*fac[n-k]%mod*inv[n-k-j])%=mod;
		}
	}
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