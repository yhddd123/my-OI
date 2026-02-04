// Problem: P4727 [HNOI2009] 图的同构计数
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P4727
// Memory Limit: 125 MB
// Time Limit: 2000 ms
// Written by yhm.
// Start codeing:2026-02-04 09:43:40
// 
// Powered by CP Editor (https://cpeditor.org)

#include<bits/stdc++.h>
#define int long long
#define mod 997
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
const int maxn=200010;
const int inf=1e9;
bool mbe;

int n,m,ans;
inline int ksm(int a,int b=mod-2){
    int ans=1;
    while(b){
        if(b&1)ans=1ll*ans*a%mod;
        a=1ll*a*a%mod;
        b>>=1;
    }
    return ans;
}
int fac[maxn],inv[maxn],pw[maxn];
int C(int m,int n){
    if(n<0||m<0||m<n)return 0;
    return 1ll*fac[m]*inv[n]%mod*inv[m-n]%mod;}
void init(int n){
    fac[0]=1;for(int i=1;i<=n;i++)fac[i]=1ll*fac[i-1]*i%mod;
    inv[n]=ksm(fac[n]);for(int i=n-1;~i;i--)inv[i]=1ll*inv[i+1]*(i+1)%mod;
    pw[0]=1;for(int i=1;i<=n*n;i++)pw[i]=pw[i-1]*m%mod;
}
inline void inc(int &u,int v){((u+=v)>=mod)&&(u-=mod);}
int a[maxn],t[maxn];
void dfs(int d,int lst,int sum){
	if(sum==n){
		int mul=1;
		for(int i=1;i<=n;i++)t[i]=0;
		for(int i=1;i<d;i++)t[a[i]]++;
		for(int i=1;i<=n;i++)mul=mul*inv[t[i]]%mod;
		for(int i=1;i<d;i++)mul=mul*inv[a[i]]%mod*fac[a[i]-1]%mod;
		int num=0;for(int i=1;i<d;i++)num+=a[i]/2;
		for(int i=1;i<d;i++){
			for(int j=i+1;j<d;j++)num+=__gcd(a[i],a[j]);
		}
		mul=mul*pw[num]%mod;
		// for(int i=1;i<d;i++)cout<<a[i]<<" ";cout<<"\n";
		(ans+=mul)%=mod;
		return ;
	}
	for(int i=lst;i;i--)if(sum+i<=n){
		a[d]=i;dfs(d+1,i,sum+i);
	}
}
void work(){
	n=read();m=2;init(n);
	dfs(1,n,0);
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