// Problem: P12992 [GCJ 2022 #1C] Intranets
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P12992
// Memory Limit: 1024 MB
// Time Limit: 20000 ms
// Written by yhm.
// Start codeing:2025-12-10 18:11:51
// 
// Powered by CP Editor (https://cpeditor.org)

#include<bits/stdc++.h>
#define int long long
#define mod 1000000007ll
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
const int maxn=1000010;
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
int fac[maxn],inv[maxn],ni[maxn],ipw[maxn];
int C(int m,int n){
    if(n<0|m<0||m<n)return 0;
    return fac[m]*inv[n]%mod*inv[m-n]%mod;}
void init(int n){
    fac[0]=1;for(int i=1;i<=n;i++)fac[i]=fac[i-1]*i%mod;
    inv[n]=ksm(fac[n]);for(int i=n-1;~i;i--)inv[i]=inv[i+1]*(i+1)%mod;
    ni[0]=ni[1]=1;for(int i=2;i<=n;i++)ni[i]=(mod-mod/i)*ni[mod%i]%mod;
    ipw[0]=1;for(int i=1;i<=n;i++)ipw[i]=ipw[i-1]*(mod+1)/2%mod;
}
int n,k,ans;
int pre[maxn];
void work(){
	n=read();k=read();ans=0;
	pre[0]=1;for(int i=1;i<=n/2;i++)pre[i]=pre[i-1]*ni[2*n-2*i-1]%mod;
	for(int i=k;i<=n/2;i++){
		(ans+=(((i-k)&1)?mod-1:1)*C(i,k)%mod*fac[n]%mod*inv[n-2*i]%mod*inv[i]%mod*ipw[i]%mod*pre[i])%=mod;
	}
	printf("%lld\n",ans);
}

bool med;
int T;
signed main(){
	// freopen(".in","r",stdin);
	// freopen(".out","w",stdout);
	
	// cerr<<(&mbe-&med)/1024.0/1024.0<<"\n";
	
	init(maxn-10);
	
	T=read();
	for(int t=1;t<=T;t++){
		printf("Case #%d: ",t);
		work();
	}
}