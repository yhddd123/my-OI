// Problem: B. 交通管制
// Contest: UOJ - UOJ Round #30
// URL: https://uoj.ac/contest/97/problem/962
// Memory Limit: 1024 MB
// Time Limit: 4000 ms
// Written by yhm.
// Start codeing:2025-05-26 21:43:32
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
const int maxn=16;
const int inf=1e9;
bool mbe;

int n,m,k;
int ff[maxn+1][1<<maxn],gg[maxn+1][1<<maxn],hh[maxn+1],ni[maxn+1];
void fmt(int *a,int n,int w=1){
	for(int i=0;i<n;i++){
		for(int s=0;s<(1<<n);s++)if(s&(1<<i))(a[s]+=a[s^(1<<i)]*w)%=mod;
	}
}
void xormul(int *a,int *b,int *c,int n){
	for(int i=0;i<=n;i++){
		for(int s=0;s<(1<<n);s++)ff[i][s]=gg[i][s]=0;
	}
	for(int s=0;s<(1<<n);s++)ff[__builtin_popcount(s)][s]=a[s];
	for(int s=0;s<(1<<n);s++)gg[__builtin_popcount(s)][s]=b[s];
	for(int i=0;i<=n;i++)fmt(ff[i],n,1),fmt(gg[i],n,1);
	for(int s=0;s<(1<<n);s++){
		for(int i=0;i<=n;i++){
			hh[i]=0;
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
		for(int i=0;i<n;i++){
			hh[i]=ff[i+1][s]*(i+1)%mod;
			for(int j=1;j<=i;j++)(hh[i]+=ff[j][s]*j%mod*hh[i-j]%mod*ni[i-j+1])%=mod;
		}
		for(int i=1;i<=n;i++)ff[i][s]=hh[i-1]*ni[i]%mod;
	}
	for(int i=1;i<=n;i++)fmt(ff[i],n,mod-1);
	b[0]=1;for(int s=1;s<(1<<n);s++)b[s]=ff[__builtin_popcount(s)][s];
}
int e[1<<maxn],sum[1<<maxn],to[2][1<<maxn],pw[maxn*maxn];
int f[1<<maxn],g[1<<maxn];
int tmpg[1<<maxn],tmph[1<<maxn];
void comb(int *dp,int c){
	for(int i=n-1;i;i--){
		for(int s=0;s<(1<<i);s++){
			for(int t=0;t<(1<<n-i-1);t++){
				tmpg[s|(t<<i)]=dp[s|(1<<i)|(t<<i+1)];
				int num=__builtin_popcount(s&e[i]);
				tmph[s|(t<<i)]=c*dp[s|(t<<i+1)]%mod*num%mod;
			}
		}
		xorexp(tmph,tmph,n-1);
		xormul(tmpg,tmph,tmpg,n-1);
		for(int s=0;s<(1<<i);s++){
			for(int t=0;t<(1<<n-i-1);t++){
				dp[s|(1<<i)|(t<<i+1)]=tmpg[s|(t<<i)];
			}
		}
	}
}
void split(int *dp,int c){
	for(int i=1;i<n;i++){
		for(int s=0;s<(1<<i);s++){
			for(int t=0;t<(1<<n-i-1);t++){
				tmpg[s|(t<<i)]=dp[s|(1<<i)|(t<<i+1)];
				int num=__builtin_popcount(s&e[i]);
				tmph[s|(t<<i)]=mod-c*dp[s|(t<<i+1)]%mod*num%mod;
			}
		}
		xorexp(tmph,tmph,n-1);
		xormul(tmpg,tmph,tmpg,n-1);
		for(int s=0;s<(1<<i);s++){
			for(int t=0;t<(1<<n-i-1);t++){
				dp[s|(1<<i)|(t<<i+1)]=tmpg[s|(t<<i)];
			}
		}
	}
}
void work(){
	n=read();m=read();k=read();
	for(int i=1;i<=m;i++){
		int u=read()-1,v=read()-1;
		e[u]|=1<<v,e[v]|=1<<u;
	}
	while(k--){
		int u=read()-1,v=read()-1,op=read()-1;
		to[op][1<<u]|=1<<v,to[op][1<<v]|=1<<u;
	}
	for(int i=0;i<n;i++)to[0][1<<i]|=to[1][1<<i];
	ni[0]=ni[1]=1;for(int i=2;i<=n;i++)ni[i]=(mod-mod/i)*ni[mod%i]%mod;
	for(int s=1;s<(1<<n);s++){
		int u=__lg(s&(-s));
		sum[s]=sum[s^(1<<u)]+__builtin_popcount(s&e[u]);
		to[0][s]=to[0][s^(1<<u)]|to[0][1<<u];
		to[1][s]=to[1][s^(1<<u)]|to[1][1<<u];
	}
	for(int u=0;u<n;u++){
		for(int s=0;s<(1<<u);s++)tmpg[s]=f[s]*__builtin_popcount(s&e[u])%mod;
		xorexp(tmpg,tmpg,u+1);
		for(int s=0;s<(1<<u);s++)f[s|(1<<u)]=tmpg[s];
	}
	for(int s=0;s<(1<<n);s++)if(to[1][s]&s)f[s]=0;
	comb(f,mod-1);
	pw[0]=1;for(int i=1;i<=m;i++)pw[i]=pw[i-1]*2%mod;
	for(int s=0;s<(1<<n);s++)g[s]=pw[sum[s]];
	xorln(g,g,n);
	split(g,1);
	// for(int s=0;s<(1<<n);s++)cout<<g[s]<<" ";cout<<"\n";
	for(int s=0;s<(1<<n);s++)if(__builtin_popcount(s)>=2)(f[s]+=g[s])%=mod;
	comb(f,1);
	for(int s=0;s<(1<<n);s++)if((to[0][s]&s)!=to[0][s])f[s]=0;
	xorexp(f,f,n);
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