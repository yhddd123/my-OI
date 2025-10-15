// Problem: AT_arc068_d [ARC068F] Solitaire
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/AT_arc068_d
// Memory Limit: 256 MB
// Time Limit: 2000 ms
// Written by yhm.
// Start codeing:2025-10-15 09:44:31
// 
// Powered by CP Editor (https://cpeditor.org)

#include<bits/stdc++.h>
#define int long long
#define mod 1000000007ll
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
int fac[maxn<<1],inv[maxn<<1];
int C(int m,int n){
    if(n<0|m<0||m<n)return 0;
    return fac[m]*inv[n]%mod*inv[m-n]%mod;}
void init(int n){
    fac[0]=1;for(int i=1;i<=n;i++)fac[i]=fac[i-1]*i%mod;
    inv[n]=ksm(fac[n]);for(int i=n-1;~i;i--)inv[i]=inv[i+1]*(i+1)%mod;
}
int n,m;
// int f[maxn][maxn];
void work(){
	n=read();m=read();init(n+m);
	// f[1][1]=1;
	// for(int i=2;i<=n;i++){
		// for(int j=1;j<=i;j++)f[i][j]=(f[i-1][j]+f[i][j-1])%mod;
	// }
	// printf("%lld\n",f[n][m]*ksm(2,n-m-1)%mod);
	printf("%lld\n",(C(n+m-2,n-1)+mod-C(n+m-2,n))*(n==m?1:ksm(2,n-m-1))%mod);
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