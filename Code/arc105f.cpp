// Problem: AT_arc105_f [ARC105F] Lights Out on Connected Graph
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/AT_arc105_f
// Memory Limit: 1 MB
// Time Limit: 3000 ms
// Written by yhm.
// Start codeing:2025-05-19 18:37:49
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
const int maxn=17;
const int inf=1e9;
bool mbe;

int n,m;
int f[1<<maxn],g[1<<maxn],val[1<<maxn],cnt[1<<maxn];
int pw[maxn*maxn],npw[maxn*maxn];
void fwt(int *a,int n,int w){
	for(int l=2;l<=n;l<<=1){
		int k=l>>1;
		for(int i=0;i<n;i+=l){
			for(int j=i;j<i+k;j++)(a[j+k]+=a[j]*w)%=mod;
		}
	}
}
int ff[maxn+1][1<<maxn],gg[maxn+1][1<<maxn],hh[maxn+1][1<<maxn],ni[maxn+1];
void xormul(int *a,int *b,int *c,int n){
	for(int i=0;i<=n;i++){
		for(int s=0;s<(1<<n);s++)ff[i][s]=gg[i][s]=hh[i][s]=0;
	}
	for(int s=0;s<(1<<n);s++)ff[__builtin_popcount(s)][s]=a[s];
	for(int s=0;s<(1<<n);s++)gg[__builtin_popcount(s)][s]=b[s];
	for(int i=0;i<=n;i++)fwt(ff[i],1<<n,1);
	for(int i=0;i<=n;i++)fwt(gg[i],1<<n,1);
	for(int s=0;s<(1<<n);s++){
		for(int i=0;i<=n;i++){
			for(int j=0;j<=i;j++)(hh[i][s]+=ff[j][s]*gg[i-j][s])%=mod;
		}
	}
	for(int i=0;i<=n;i++)fwt(hh[i],1<<n,mod-1);
	for(int s=0;s<(1<<n);s++)c[s]=hh[__builtin_popcount(s)][s];
}
void xorln(int *a,int *b,int n){
	for(int i=0;i<=n;i++){
		for(int s=0;s<(1<<n);s++)ff[i][s]=gg[i][s]=0;
	}
	for(int s=0;s<(1<<n);s++)ff[__builtin_popcount(s)][s]=a[s];
	for(int i=0;i<=n;i++)fwt(ff[i],1<<n,1);
	for(int s=0;s<(1<<n);s++){
		for(int i=0;i<n;i++){
			gg[i][s]=ff[i+1][s]*(i+1)%mod;
			for(int j=1;j<=i;j++)(gg[i][s]+=mod-ff[j][s]*gg[i-j][s]%mod)%=mod;
		}
		for(int i=1;i<=n;i++)ff[i][s]=gg[i-1][s]*ni[i]%mod;
	}
	for(int i=0;i<=n;i++)fwt(ff[i],1<<n,mod-1);
	for(int s=0;s<(1<<n);s++)b[s]=ff[__builtin_popcount(s)][s];
}
void work(){
	n=read();m=read();
	for(int i=1;i<=m;i++){
		int u=read()-1,v=read()-1;
		cnt[(1<<u)|(1<<v)]++;
	}
	for(int i=0;i<n;i++){
		for(int s=0;s<(1<<n);s++)if(s&(1<<i))cnt[s]+=cnt[s^(1<<i)];
	}
	pw[0]=1;for(int i=1;i<n*n;i++)pw[i]=pw[i-1]*2%mod;
	npw[0]=1;for(int i=1;i<n*n;i++)npw[i]=npw[i-1]*(mod+1)/2%mod;
	for(int s=0;s<(1<<n);s++)val[s]=npw[cnt[s]];
	xormul(val,val,g,n);
	g[0]=0;for(int s=1;s<(1<<n);s++)g[s]=g[s]*pw[cnt[s]]%mod;
	// for(int s=0;s<(1<<n);s++)cout<<g[s]<<" ";cout<<"\n";
	ni[0]=ni[1]=1;for(int i=2;i<=n;i++)ni[i]=(mod-mod/i)*ni[mod%i]%mod;
	xorln(g,f,n);
	printf("%lld\n",f[(1<<n)-1]*((mod+1)/2)%mod);
}

bool med;
int T;
signed main(){
	// freopen("A.in","r",stdin);
	// freopen(".out","w",stdout);
	
	// cerr<<(&mbe-&med)/1024.0/1024.0<<"\n";
	
	T=1;
	while(T--)work();
}