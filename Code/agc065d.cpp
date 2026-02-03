// Problem: AT_agc065_d [AGC065D] Not Intersect
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/AT_agc065_d
// Memory Limit: 1024 MB
// Time Limit: 3000 ms
// Written by yhm.
// Start codeing:2026-02-03 17:06:41
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
int fac[maxn],inv[maxn],ni[maxn];
int C(int m,int n){
    if(n<0||m<0||m<n)return 0;
    return 1ll*fac[m]*inv[n]%mod*inv[m-n]%mod;}
void init(int n){
    fac[0]=1;for(int i=1;i<=n;i++)fac[i]=1ll*fac[i-1]*i%mod;
    inv[n]=ksm(fac[n]);for(int i=n-1;~i;i--)inv[i]=1ll*inv[i+1]*(i+1)%mod;
    ni[0]=ni[1]=1;for(int i=2;i<=n;i++)ni[i]=(mod-mod/i)*ni[mod%i]%mod;
}
inline void inc(int &u,int v){((u+=v)>=mod)&&(u-=mod);}
int n,m,ans;
void work(){
	n=read();m=read();
	if(m>2*n-3){puts("0");return ;}
	if(n<=2){puts(m?"0":"1");return ;}
	init(maxn-10);
	for(int i=0;i<=m&&i<=n;i++)if(m-i+1<=n-2)(ans+=C(n,i)*C(n-3,m-i)%mod*C(n+m-i,m-i+1)%mod*ni[n-1+m-i+1])%=mod;
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