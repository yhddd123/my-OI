// Problem: #6730. 边双连通生成子图计数
// Contest: LibreOJ
// URL: https://loj.ac/p/6730
// Memory Limit: 1024 MB
// Time Limit: 10000 ms
// Written by yhm.
// Start codeing:2025-05-25 22:18:15
// 
// Powered by CP Editor (https://cpeditor.org)

#include<bits/stdc++.h>
#define int long long
#define mod 998244353ll
#define pii pair<int,int>
#define fi first
#define se second
#define pb push_back
#define mkp make_pair
#define mems(a,x) memset((a),(x),sizeof(a))
using namespace std;
inline int read(){
	int x=0,fl=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')fl=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
	return x*fl;
}
const int maxn=20;
const int inf=1e9;
bool mbe;

int n,m;
int e[1<<maxn],pw[maxn*maxn];
void fmt(int *a,int n,int w=1){
	for(int i=0;i<n;i++){
		for(int s=0;s<(1<<n);s++)if(s&(1<<i))(a[s]+=a[s^(1<<i)]*w)%=mod;
	}
}
int ff[maxn+1][1<<maxn],gg[maxn+1][1<<maxn],hh[maxn+1],ni[maxn];
void xormul(int *a,int *b,int *c,int n){
	for(int i=0;i<=n;i++){
		for(int s=0;s<(1<<n);s++)ff[i][s]=gg[i][s]=0;
	}
	for(int s=0;s<(1<<n);s++)ff[__builtin_popcount(s)][s]=a[s];
	for(int s=0;s<(1<<n);s++)gg[__builtin_popcount(s)][s]=b[s];
	for(int i=0;i<=n;i++)fmt(ff[i],n,1),fmt(gg[i],n,1);
	for(int s=0;s<(1<<n);s++){
		for(int i=0;i<=n;i++)hh[i]=0;
		for(int i=0;i<=n;i++){
			for(int j=0;j<=i;j++)(hh[i]+=ff[j][s]*gg[i-j][s])%=mod;
		}
		for(int i=0;i<=n;i++)ff[i][s]=hh[i];
	}
	for(int i=0;i<=n;i++)fmt(ff[i],n,mod-1);
	for(int s=0;s<(1<<n);s++)c[s]=ff[__builtin_popcount(s)][s];
}
void xorln(int *a,int *b,int n){
	for(int i=0;i<=n;i++){
		for(int s=0;s<(1<<n);s++)ff[i][s]=0;
	}
	for(int s=0;s<(1<<n);s++)ff[__builtin_popcount(s)][s]=a[s];
	for(int i=0;i<=n;i++)fmt(ff[i],n,1);
	for(int s=0;s<(1<<n);s++){
		for(int i=0;i<=n;i++)hh[i]=0;
		for(int i=0;i<n;i++){
			hh[i]=ff[i+1][s]*(i+1)%mod;
			for(int j=1;j<=i;j++)(hh[i]+=mod-ff[j][s]*hh[i-j]%mod)%=mod;
		}
		for(int i=1;i<=n;i++)ff[i][s]=hh[i-1]*ni[i]%mod;
	}
	for(int i=1;i<=n;i++)fmt(ff[i],n,mod-1);
	b[0]=0;for(int s=1;s<(1<<n);s++)b[s]=ff[__builtin_popcount(s)][s];
}
void xorexp(int *a,int *b,int n){
	for(int i=0;i<=n;i++){
		for(int s=0;s<(1<<n);s++)ff[i][s]=0;
	}
	for(int s=0;s<(1<<n);s++)ff[__builtin_popcount(s)][s]=a[s];
	for(int i=0;i<=n;i++)fmt(ff[i],n,1);
	for(int s=0;s<(1<<n);s++){
		for(int i=0;i<=n;i++)hh[i]=0;
		for(int i=0;i<n;i++){
			hh[i]=ff[i+1][s]*(i+1)%mod;
			for(int j=1;j<=i;j++)(hh[i]+=ff[j][s]*j%mod*hh[i-j]%mod*ni[i-j+1])%=mod;
		}
		for(int i=1;i<=n;i++)ff[i][s]=hh[i-1]*ni[i]%mod;
	}
	for(int i=1;i<=n;i++)fmt(ff[i],n,mod-1);
	b[0]=1;for(int s=1;s<(1<<n);s++)b[s]=ff[__builtin_popcount(s)][s];
}
int f[1<<maxn],g[1<<maxn],h[1<<maxn];
void work(){
	n=read();m=read();
	for(int i=1;i<=m;i++){
		int u=read()-1,v=read()-1;
		e[(1<<u)|(1<<v)]++;
	}
	pw[0]=1;for(int i=1;i<=m;i++)pw[i]=pw[i-1]*2%mod;
	ni[0]=ni[1]=1;for(int i=2;i<=n;i++)ni[i]=(mod-mod/i)*ni[mod%i]%mod;
	fmt(e,n,1);
	for(int s=0;s<(1<<n);s++)f[s]=pw[e[s]];
	fmt(e,n,mod-1);
	xorln(f,f,n);
	// for(int s=0;s<(1<<n);s++)cout<<f[s]<<" ";cout<<"\n";
	for(int i=1;i<n;i++){
		for(int s=0;s<(1<<n);s++)g[s]=h[s]=0;
		for(int s=0;s<(1<<i);s++){
			for(int t=0;t<(1<<n-i-1);t++){
				g[s|(t<<i)]=f[s|(1<<i)|(t<<i+1)];
				int num=0;for(int j=0;j<i;j++)if((s&(1<<j))&&e[(1<<i)|(1<<j)])++num;
				h[s|(t<<i)]=mod-f[s|(t<<i+1)]*num%mod;
			}
		}
		xorexp(h,h,n-1);
		// for(int s=0;s<(1<<n-1);s++)cout<<h[s]<<" ";cout<<"\n";
		// for(int s=0;s<(1<<n-1);s++)cout<<g[s]<<" ";cout<<"\n";
		xormul(g,h,g,n-1);
		for(int s=0;s<(1<<i);s++){
			for(int t=0;t<(1<<n-i-1);t++)f[s|(1<<i)|(t<<i+1)]=g[s|(t<<i)];
		}
		// for(int s=0;s<(1<<n);s++)cout<<f[s]<<" ";cout<<"\n";
	}
	printf("%lld\n",f[(1<<n)-1]);
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