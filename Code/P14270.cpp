// Problem: P14270 ABC253Ex 加强版
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P14270
// Memory Limit: 512 MB
// Time Limit: 5000 ms
// Written by yhm.
// Start codeing:2026-01-20 07:59:30
// 
// Powered by CP Editor (https://cpeditor.org)

#include<bits/stdc++.h>
#define int long long
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

inline int ksm(int a,int b=mod-2){
    int ans=1;
    while(b){
        if(b&1)ans=1ll*ans*a%mod;
        a=1ll*a*a%mod;
        b>>=1;
    }
    return ans;
}
int fac[maxn+1],inv[maxn+1];
int C(int m,int n){
    if(n<0|m<0||m<n)return 0;
    return 1ll*fac[m]*inv[n]%mod*inv[m-n]%mod;}
void init(int n){
    fac[0]=1;for(int i=1;i<=n;i++)fac[i]=1ll*fac[i-1]*i%mod;
    inv[n]=ksm(fac[n]);for(int i=n-1;~i;i--)inv[i]=1ll*inv[i+1]*(i+1)%mod;
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
void xormul(int *a,int *b,int *c,int n){
	for(int i=0;i<=n;i++){
		for(int s=0;s<(1<<n);s++)ff[i][s]=gg[i][s]=0;
	}
	for(int s=0;s<(1<<n);s++)ff[__builtin_popcount(s)][s]=a[s];
	for(int s=0;s<(1<<n);s++)gg[__builtin_popcount(s)][s]=b[s];
	for(int i=0;i<=n;i++)fmt1(ff[i],1<<n);
	for(int i=0;i<=n;i++)fmt1(gg[i],1<<n);
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
	for(int s=0;s<(1<<n);s++)c[s]=ff[__builtin_popcount(s)][s];
}
void exp(int *a,int n){
	a[0]=1;
	for(int i=0;i<n;i++)xormul(a+(1<<i),a,a+(1<<i),i);
}
void xormul1(int *a,int *c,int n){
	for(int i=0;i<=n;i++){
		for(int s=0;s<(1<<n);s++)ff[i][s]=0;
	}
	for(int s=0;s<(1<<n);s++)ff[__builtin_popcount(s)][s]=a[s^((1<<n)-1)];
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
	for(int s=0;s<(1<<n);s++)inc(c[s^((1<<n)-1)],ff[__builtin_popcount(s)][s]);
}
int hh[maxn+1][1<<maxn];
void comptrans(int *a,int *c,int n){
	hh[0][(1<<n)-1]=1;
	for(int i=n;i;i--){
		for(int j=0;j<i;j++){
			for(int s=0;s<(1<<i-1);s++)gg[j][s]=0;
		}
		for(int s=0;s<(1<<i-1);s++)gg[__builtin_popcount(s)][s]=a[s+(1<<i-1)];
		for(int j=0;j<i;j++)fmt1(gg[j],1<<i-1);
		for(int j=n-i+1;j;j--){
			xormul1(hh[j-1]+(1<<i-1),hh[j],i-1);
		}
		// cout<<i<<"\n";
		// for(int j=0;j<=n-i+1;j++){
			// for(int s=0;s<(1<<n);s++)cout<<hh[j][s]<<" ";cout<<"\n";
		// }
	}
	for(int i=0;i<=n;i++)c[i]=hh[i][0];
	// for(int i=0;i<=n;i++)cout<<c[i]<<" ";cout<<"\n";
}
int n,m,e[maxn][maxn];
int f[1<<maxn],ans[maxn+1];
int tmpf[1<<maxn];
void work(){
	n=read();m=read();init(n);
	for(int i=1;i<=m;i++){
		int u=read()-1,v=read()-1;
		e[u][v]++,e[v][u]++;
	}
	for(int i=0;i<n;i++){
		for(int s=0;s<(1<<i);s++){
			int cnt=0;
			for(int j=0;j<i;j++)if(s&(1<<j))cnt+=e[i][j];
			f[s|(1<<i)]=f[s]*cnt%mod;
		}
		exp(f+(1<<i),i);
	}
	// for(int s=0;s<(1<<n);s++)cout<<f[s]<<" ";cout<<"\n";
	comptrans(f,ans,n);
	for(int i=1;i<n;i++)printf("%lld\n",fac[i]*ans[n-i]%mod);
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