// Problem: AT_abc306_h [ABC306Ex] Balance Scale
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/AT_abc306_h
// Memory Limit: 1024 MB
// Time Limit: 3000 ms
// Written by yhm.
// Start codeing:2026-01-28 19:22:04
// 
// Powered by CP Editor (https://cpeditor.org)

#include<bits/stdc++.h>
// #define int long long
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

inline int ksm(int a,int b=mod-2){
	int ans=1;
	while(b){
		if(b&1)ans=1ll*ans*a%mod;
		a=1ll*a*a%mod;
		b>>=1;
	}
	return ans;	
}
inline void inc(int &u,int v){((u+=v)>=mod)&&(u-=mod);}
int ff[maxn+1][1<<maxn],gg[maxn+1][1<<maxn];
void fmt1(int *a,int n){
	for(int l=2;l<=n;l<<=1){
		int k=l>>1;
		for(int i=0;i<n;i+=l){
			for(int j=i;j<i+k;j++)inc(a[j+k],a[j]);
		}
	}
}
void fmt2(int *a,int n){
	for(int l=2;l<=n;l<<=1){
		int k=l>>1;
		for(int i=0;i<n;i+=l){
			for(int j=i;j<i+k;j++)inc(a[j+k],mod-a[j]);
		}
	}
}
int tf[maxn+1],tg[maxn+1],th[maxn+1],ni[maxn+1];
void xorni(int *a,int *b,int n){//b=1/a
	for(int i=0;i<=n;i++){
		for(int s=0;s<(1<<n);s++)ff[i][s]=0;
	}
	for(int s=0;s<(1<<n);s++)ff[__builtin_popcount(s)][s]=a[s];
	for(int i=0;i<=n;i++)fmt1(ff[i],1<<n);
	for(int s=0;s<(1<<n);s++){
		tf[0]=mod+1-ff[0][s];for(int i=1;i<=n;i++)tf[i]=mod-ff[i][s];
		int nif=ksm(tf[0]);
		for(int i=0;i<=n;i++){
			th[i]=1;
			for(int j=1;j<=i;j++)inc(th[i],mod-1ll*tf[j]*th[i-j]%mod);
			th[i]=1ll*th[i]*nif%mod;
		}
		for(int i=0;i<=n;i++)ff[i][s]=th[i];
	}
	for(int i=0;i<=n;i++)fmt2(ff[i],1<<n);
	for(int s=0;s<(1<<n);s++)b[s]=ff[__builtin_popcount(s)][s];
}
int n,m;
int e[maxn][maxn],f[1<<maxn],g[1<<maxn];
int fa[maxn];
int fd(int x){
	if(x==fa[x])return x;
	return fa[x]=fd(fa[x]);
}
void work(){
	n=read();m=read();
	for(int i=1;i<=m;i++){
		int u=read()-1,v=read()-1;
		e[u][v]=e[v][u]=1;
	}
	f[0]=0;for(int s=1;s<(1<<n);s++){
		for(int i=0;i<n;i++)fa[i]=i;
		for(int i=0;i<n;i++)if(s&(1<<i)){
			for(int j=0;j<n;j++)if((s&(1<<j))&&e[i][j])fa[fd(i)]=fd(j);
		}
		int num=0;for(int i=0;i<n;i++)if((s&(1<<i))&&fa[i]==i)++num;
		f[s]=((num+1)&1)?mod-1:1;
		// cout<<s<<" "<<num<<" "<<f[s]<<"\n";
	}
	xorni(f,g,n);
	printf("%lld\n",g[(1<<n)-1]);
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