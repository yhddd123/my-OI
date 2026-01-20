// Problem: P13497 【MX-X14-T7】墓碑密码
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P13497
// Memory Limit: 512 MB
// Time Limit: 2000 ms
// Written by yhm.
// Start codeing:2026-01-20 16:18:41
// 
// Powered by CP Editor (https://cpeditor.org)

#include<bits/stdc++.h>
// #define int long long
#define mod 1000000007
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
const int maxn=50000200;
const int maxm=135;
const int maxk=28;
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
int fac[maxn],inv[maxn];
int C(int m,int n){
    if(n<0||m<0||m<n)return 0;
    return 1ll*fac[m]*inv[n]%mod*inv[m-n]%mod;}
void init(int n){
    fac[0]=1;for(int i=1;i<=n;i++)fac[i]=1ll*fac[i-1]*i%mod;
    inv[n]=ksm(fac[n]);for(int i=n-1;~i;i--)inv[i]=1ll*inv[i+1]*(i+1)%mod;
}
inline void inc(int &u,int v){((u+=v)>=mod)&&(u-=mod);}
int n,m,k=28,q;
int a[maxm],b[maxm];
int f[maxm],val[maxm];
#define ull unsigned long long
#define pii pair<ull,ull>
#define fi first
#define se second
pii ca,cb,aa[maxk],bb[maxk];
void work(){
	n=read();m=read();init(maxn-10);
	for(int i=0;i<n;i++)a[i]=read();
	for(int i=0;i<m;i++)b[i]=read();
	for(int i=0;i<k;i++){
		int s=(1<<i+1)-1;
		for(int j=0;j<n;j++)if(__builtin_parity(a[j]&s)){
			if(j<64)aa[i].fi|=1ull<<j;
			else aa[i].se|=1ull<<j-64;
		}
		for(int j=0;j<m;j++)if(__builtin_parity(b[j]&s)){
			if(j<64)bb[i].fi|=1ull<<j;
			else bb[i].se|=1ull<<j-64;
		}
	}
	inc(val[n],m);
	for(int s=1;s<(1<<k);s++){
		int kk=31-__builtin_clz(s^(s-1));
		ca.fi^=aa[kk].fi,ca.se^=aa[kk].se;
		cb.fi^=bb[kk].fi,cb.se^=bb[kk].se;
		int cnta=n-__builtin_popcountll(ca.fi)-__builtin_popcountll(ca.se),cntb=m-__builtin_popcountll(cb.fi)-__builtin_popcountll(cb.se);
		int w=2*cntb-m;(w<0)&&(w+=mod);
		inc(val[cnta],w);
	}
	// for(int i=0;i<=n;i++)cout<<val[i]<<" ";cout<<"\n";
	for(int t=0;t<=n;t++){
		for(int i=0;i<=n;i++){
			for(int j=0;j<=i&&j<=t;j++)inc(f[t],1ll*val[i]*C(i,j)%mod*C(n-i,t-j)%mod*(((t-j)&1)?mod-1:1)%mod);
		}
	}
	int ni=ksm(ksm(2,k));
	for(int i=0;i<=n;i++)f[i]=1ll*f[i]*ni%mod;
	// for(int i=0;i<=n;i++)cout<<f[i]<<" ";cout<<"\n";
	q=read();
	while(q--){
		int len=read(),ans=0;
		for(int i=0;i<=n&&i<=len;i++)inc(ans,1ll*f[i]*C((len-i)/2+n,n)%mod);
		printf("%lld\n",ans);
	}
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