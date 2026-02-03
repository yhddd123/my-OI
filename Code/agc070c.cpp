// Problem: AT_agc070_c [AGC070C] No Streak
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/AT_agc070_c
// Memory Limit: 1024 MB
// Time Limit: 3000 ms
// Written by yhm.
// Start codeing:2026-02-03 22:07:35
// 
// Powered by CP Editor (https://cpeditor.org)

#include<bits/stdc++.h>
#define int long long
#define mod 1000000007
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
const int maxn=20000010;
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
int calc(int n,int m,int k){
	if((!n||!m))return !k;
	if(k&1){
		return 2*C(n-1,(k+1)/2-1)*C(m-1,(k+1)/2-1)%mod;
	}
	else{
		return (C(n-1,k/2)*C(m-1,k/2-1)+C(n-1,k/2-1)*C(m-1,k/2))%mod;
	}
}
int calc(int n,int m,int b,int k){
	if(k&1){
		k=(k+1)/2;
		return (2*C(n-1,k-1)*C(m-1,k-1)%mod+2*mod-C(n+b-2,k-1)*C(m-b,k-1)%mod-C(n+b-2,k-2)*C(m-b,k)%mod)%mod;
	}
	else{
		k=k/2;
		return (C(n-1,k)*C(m-1,k-1)+C(n-1,k-1)*C(m-1,k)+mod-2*C(n+b-2,k-1)*C(m-b,k)%mod)%mod;
	}
	// int res=calc(n,m,k);
	// for(int i=0;b+i<=m;i++)(res+=mod-calc(n+b-1,m-b-i,k-1))%=mod;
	// return res;
}
int n,a,b,ans;
void work(){
	n=read();a=read();b=read();init(n);
	for(int i=1;i<=a+b-1;i++)(ans+=calc(a,b,1,i)*C(n-a-b+i+1,a+b))%=mod;
	printf("%lld\n",ans);
}

bool med;
int T;
signed main(){
	// freopen(".in","r",stdin);
	// freopen(".out","w",stdout);
	
	cerr<<(&mbe-&med)/1024.0/1024.0<<"\n";
	
	T=1;
	while(T--)work();
}