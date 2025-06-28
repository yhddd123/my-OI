// Problem: P12230 集合幂级数 exp
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P12230
// Memory Limit: 512 MB
// Time Limit: 2500 ms
// Written by yhm.
// Start codeing:2025-05-22 11:53:03
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

int n,f[1<<maxn],g[1<<maxn];
void fmt(int *a,int n,int w=1){
	for(int i=0;i<n;i++){
		for(int s=0;s<(1<<n);s++)if(s&(1<<i))(a[s]+=a[s^(1<<i)]*w)%=mod;
	}
}
int ff[maxn+1][1<<maxn],hh[1<<maxn],ni[maxn+1];
void xorexp(int *a,int *b,int n){//exp(a)=b
	ni[0]=ni[1]=1;for(int i=2;i<=n;i++)ni[i]=(mod-mod/i)*ni[mod%i]%mod;
	for(int i=0;i<=n;i++){
		for(int s=0;s<(1<<n);s++)ff[i][s]=0;
	}
	for(int s=0;s<(1<<n);s++)ff[__builtin_popcount(s)][s]=a[s];
	for(int i=0;i<=n;i++)fmt(ff[i],n,1);
	for(int s=0;s<(1<<n);s++){
		for(int i=0;i<=n;i++)hh[i]=0;
		for(int i=0;i<=n;i++){
			if(i<n)hh[i]=ff[i+1][s]*(i+1)%mod;
			for(int j=1;j<=i;j++)(hh[i]+=ff[j][s]*j%mod*hh[i-j]%mod*ni[i-j+1])%=mod;
		}
		for(int i=1;i<=n;i++)ff[i][s]=hh[i-1]*ni[i]%mod;
	}
	for(int i=0;i<=n;i++)fmt(ff[i],n,mod-1);
	b[0]=1;for(int s=1;s<(1<<n);s++)b[s]=ff[__builtin_popcount(s)][s];
}
void work(){
	n=read();
	for(int i=0;i<(1<<n);i++)f[i]=read();
	xorexp(f,g,n);
	for(int i=0;i<(1<<n);i++)printf("%lld ",g[i]);
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