// Problem: A - Chords and Checkered
// Contest: AtCoder - AtCoder Grand Contest 073
// URL: https://atcoder.jp/contests/agc073/tasks/agc073_a
// Memory Limit: 1024 MB
// Time Limit: 2000 ms
// Written by yhm.
// Start codeing:2025-09-28 20:34:45
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
const int maxn=750010;
const int inf=1e9;
bool mbe;

inline int ksm(int a,int b=mod-2){
    int ans=1;
    while(b){
        if(b&1)ans=ans*a%mod;
        a=a*a%mod;
        b>>=1;
    }
    return ans;
}
int fac[maxn],inv[maxn],pw[maxn];
int C(int m,int n){
    if(n<0|m<0||m<n)return 0;
    return fac[m]*inv[n]%mod*inv[m-n]%mod;}
void init(int n){
    fac[0]=1;for(int i=1;i<=n;i++)fac[i]=fac[i-1]*i%mod;
    inv[n]=ksm(fac[n]);for(int i=n-1;~i;i--)inv[i]=inv[i+1]*(i+1)%mod;
    pw[0]=1;for(int i=1;i<=n;i++)pw[i]=pw[i-1]*2%mod;
}
int l,k,n,a[maxn],ans;
int f[maxn];
int pl[maxn],pr[maxn];
void work(){
	l=read();k=read();n=read();init(n);
	for(int i=1;i<=n;i++)a[i]=read();
	for(int i=n+1;i<=3*n;i++)a[i]=a[i-n]+l;
	f[0]=1,f[1]=2,f[2]=5;
	for(int i=3;i<=n;i++)f[i]=4*(f[i-1]-f[i-2]+mod)%mod;
	for(int i=n+1,j=1;i<=2*n;i++){
		while(a[j]+k<=a[i])j++;
		pl[i]=j;
	}
	for(int i=n+1,j=n+1;i<=2*n;i++){
		while(a[j]<a[i]+k)j++;
		pr[i]=j;
	}
	for(int i=n+1;i<=2*n;i++){
		(ans+=f[i-pl[i]]*pw[n-(i-pl[i]+1)])%=mod;
	}
	printf("%lld\n",ans);	
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