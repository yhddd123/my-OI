// Problem: AT_agc067_d [AGC067D] Unique Matching
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/AT_agc067_d
// Memory Limit: 1024 MB
// Time Limit: 2000 ms
// Written by yhm.
// Start codeing:2026-02-03 16:27:55
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
const int maxn=5010;
const int inf=1e9;
bool mbe;

int n,mod;
int f[maxn],g[maxn];
void work(){
	n=read();mod=read();
	f[0]=1,g[0]=-1;
	for(int i=1;i<=n;i++){
		(g[i]+=i*f[i-1])%=mod;
		for(int j=1;j<i;j++)(g[i]+=mod-g[j]*(i-j)%mod*(i-j)%mod*f[i-j-1]%mod)%=mod;
		for(int j=1;j<=i;j++)(f[i]+=g[j]*(i+1-j)%mod*f[i-j])%=mod;
		// cout<<f[i]<<" "<<g[i]<<"\n";
	}
	int fac=1;for(int i=1;i<=n;i++)fac=fac*i%mod;
	printf("%lld\n",f[n]*fac%mod);
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