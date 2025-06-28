// Problem: P6846 [CEOI 2019] Amusement Park
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P6846
// Memory Limit: 1 MB
// Time Limit: 3000 ms
// Written by yhm.
// Start codeing:2025-05-22 11:17:56
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
const int maxn=18;
const int inf=1e9;
bool mbe;

int n,m;
int e[1<<maxn],f[1<<maxn],g[1<<maxn];
void fmt(int *a,int n,int w){
	for(int i=0;i<n;i++){
		if(w==1){
			for(int s=0;s<(1<<n);s++)if(s&(1<<i))(a[s]+=a[s^(1<<i)])%=mod;
		}
		else{
			for(int s=0;s<(1<<n);s++)if(s&(1<<i))(a[s]+=mod-a[s^(1<<i)])%=mod;
		}
	}
}
inline int ksm(int a,int b=mod-2){
	int ans=1;
	while(b){
		if(b&1)ans=ans*a%mod;
		a=a*a%mod;
		b>>=1;
	}
	return ans;	
}
int ff[maxn+1][1<<maxn],hh[maxn+1];
void xorni(int *a,int *b,int n){//g=1/(1-f)
	for(int i=0;i<=n;i++){
		for(int s=0;s<(1<<n);s++)ff[i][s]=0;
	}
	for(int s=0;s<(1<<n);s++)ff[__builtin_popcount(s)][s]=a[s];
	for(int i=0;i<=n;i++)fmt(ff[i],n,1);
	for(int s=0;s<(1<<n);s++){
		ff[0][s]=mod+1-ff[0][s];for(int i=1;i<=n;i++)ff[i][s]=mod-ff[i][s];
		int nif=ksm(ff[0][s]);
		for(int i=0;i<=n;i++){
			hh[i]=1;
			for(int j=1;j<=i;j++)(hh[i]+=mod-ff[j][s]*hh[i-j]%mod)%=mod;
			hh[i]=hh[i]*nif%mod;
		}
		for(int i=0;i<=n;i++)ff[i][s]=hh[i];
	}
	for(int i=0;i<=n;i++)fmt(ff[i],n,-1);
	for(int s=0;s<(1<<n);s++)b[s]=ff[__builtin_popcount(s)][s];
}
void work(){
	n=read();m=read();
	for(int i=1;i<=m;i++){
		int u=read()-1,v=read()-1;
		e[(1<<u)|(1<<v)]++;
	}
	fmt(e,n,1);
	f[0]=0;for(int s=1;s<(1<<n);s++){
		if(e[s])f[s]=0;
		else f[s]=((__builtin_popcount(s)+1)&1)?-1:1;
	}
	xorni(f,g,n);
	printf("%lld\n",g[(1<<n)-1]*m%mod*(mod+1)/2%mod);
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