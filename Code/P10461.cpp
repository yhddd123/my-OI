// Problem: P10461 多项式复合集合幂级数
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P10461
// Memory Limit: 512 MB
// Time Limit: 5000 ms
// Written by yhm.
// Start codeing:2026-01-19 16:43:02
// 
// Powered by CP Editor (https://cpeditor.org)

#include<bits/stdc++.h>
// #define int long long
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
const int maxn=20;
const int inf=1e9;
bool mbe;

int n,a[1<<maxn],b[maxn+1],c[1<<maxn];
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
void xormul1(int *a,int *c,int n){
	for(int i=0;i<=n;i++){
		for(int s=0;s<(1<<n);s++)ff[i][s]=0;
	}
	for(int s=0;s<(1<<n);s++)ff[__builtin_popcount(s)][s]=a[s];
	for(int i=0;i<=n;i++)fmt1(ff[i],1<<n);
	for(int s=0;s<(1<<n);s++){
		for(int i=0;i<=n;i++)tf[i]=ff[i][s];
		for(int i=0;i<=n;i++)tg[i]=gg[i][s];
		for(int i=0;i<=n;i++){
			th[i]=0;
			for(int j=0;j<=i;j++)inc(th[i],1ll*tf[j]*tg[i-j]%mod);
		}
		for(int i=0;i<=n;i++)ff[i][s]=th[i];
	}
	for(int i=0;i<=n;i++)fmt2(ff[i],1<<n);
	for(int s=0;s<(1<<n);s++)inc(c[s],ff[__builtin_popcount(s)][s]);
}
int hh[maxn+1][1<<maxn];
void comp(int *a,int *b,int *c,int n){
	for(int i=0;i<=n;i++){
		for(int j=1;j<=i;j++)b[i]=1ll*b[i]*j%mod;
	}
	for(int i=0;i<=n;i++)hh[i][0]=b[i];
	for(int i=1;i<=n;i++){
		for(int j=0;j<i;j++){
			for(int s=0;s<(1<<i-1);s++)gg[j][s]=0;
		}
		for(int s=0;s<(1<<i-1);s++)gg[__builtin_popcount(s)][s]=a[s+(1<<i-1)];
		for(int j=0;j<i;j++)fmt1(gg[j],1<<i-1);
		for(int j=1;j<=n-i+1;j++){
			xormul1(hh[j],hh[j-1]+(1<<i-1),i-1);
		}
	}
	for(int s=0;s<(1<<n);s++)c[s]=hh[0][s];
}
void work(){
	n=read();
	for(int s=0;s<(1<<n);s++)a[s]=read();
	for(int i=0;i<=n;i++)b[i]=read();
	comp(a,b,c,n);
	for(int s=0;s<(1<<n);s++)printf("%d ",c[s]);
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