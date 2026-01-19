// Problem: P12232 集合幂级数求逆
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P12232
// Memory Limit: 512 MB
// Time Limit: 2500 ms
// Written by yhm.
// Start codeing:2025-05-22 11:42:01
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
const int maxn=20;
const int inf=1e9;
bool mbe;

int n,f[1<<maxn],g[1<<maxn];
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
int ff[maxn+1][1<<maxn],gg[maxn+1][1<<maxn];
int tf[maxn+1],tg[maxn+1],hh[maxn+1];
void xorni(int *a,int *b,int n){//b=1/a
	for(int i=0;i<=n;i++){
		for(int s=0;s<(1<<n);s++)ff[i][s]=0;
	}
	for(int s=0;s<(1<<n);s++)ff[__builtin_popcount(s)][s]=a[s];
	for(int i=0;i<=n;i++)fmt1(ff[i],1<<n);
	for(int s=0;s<(1<<n);s++){
		for(int i=0;i<=n;i++)tf[i]=ff[i][s];
		int nif=ksm(tf[0]);
		for(int i=0;i<=n;i++){
			hh[i]=1;
			for(int j=1;j<=i;j++)inc(hh[i],mod-1ll*tf[j]*hh[i-j]%mod);
			hh[i]=1ll*hh[i]*nif%mod;
		}
		for(int i=0;i<=n;i++)ff[i][s]=hh[i];
	}
	for(int i=0;i<=n;i++)fmt2(ff[i],1<<n);
	for(int s=0;s<(1<<n);s++)b[s]=ff[__builtin_popcount(s)][s];
}
void work(){
	n=read();
	for(int i=0;i<(1<<n);i++)f[i]=read();
	xorni(f,g,n);
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