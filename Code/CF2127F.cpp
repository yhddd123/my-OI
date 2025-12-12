// Problem: CF2127F Hamed and AghaBalaSar
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/CF2127F
// Memory Limit: 500 MB
// Time Limit: 2000 ms
// Written by yhm.
// Start codeing:2025-12-12 09:52:01
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
const int maxn=400010;
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
int fac[maxn],inv[maxn];
int C(int m,int n){
	if(m==n)return 1;
    if(n<0|m<0||m<n)return 0;
    return fac[m]*inv[n]%mod*inv[m-n]%mod;}
void init(int n){
    fac[0]=1;for(int i=1;i<=n;i++)fac[i]=fac[i-1]*i%mod;
    inv[n]=ksm(fac[n]);for(int i=n-1;~i;i--)inv[i]=inv[i+1]*(i+1)%mod;
}
int n,m,ans;
int f1[maxn],f2[maxn];
int calc(int n,int m,int k){
	int res=0;
	for(int i=0;i<=n&&i*(k+1)<=m;i++)(res+=((i&1)?mod-1:1)*C(n,i)%mod*C(m-i*(k+1)+n-1,n-1))%=mod;
	return res;
}
int pre[maxn];
void work(){
	n=read();m=read();ans=0;
	for(int i=0;i<=m;i++)f1[i]=calc(n-1,m-i,i),f2[i]=calc(n-2,m-2*i,i);
	for(int i=0;i<=m;i++)(ans+=((n-1)*f2[i]+f1[i])%mod*i)%=mod;
	for(int i=0;i<=m;i++)(ans+=mod-f1[i]*(m-i)%mod*ksm(n-1)%mod)%=mod;
	for(int i=0;i<=m;i++)(ans+=mod-f2[i]*(m-2*i)%mod)%=mod;
	for(int i=0;i<=m;i++)(ans+=mod-f2[i]*i)%=mod;
	printf("%lld\n",ans);
}

bool med;
int T;
signed main(){
	// freopen(".in","r",stdin);
	// freopen(".out","w",stdout);
	
	// cerr<<(&mbe-&med)/1024.0/1024.0<<"\n";
	
	T=read();init(maxn-10);
	while(T--)work();
}