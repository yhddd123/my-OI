// Problem: AT_abc367_g [ABC367G] Sum of (XOR^K or 0)
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/AT_abc367_g
// Memory Limit: 1024 MB
// Time Limit: 3000 ms
// Written by yhm.
// Start codeing:2026-01-20 15:39:04
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
const int maxn=200010;
const int maxm=100;
const int maxk=20;
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
inline void inc(int &u,int v){((u+=v)>=mod)&&(u-=mod);}
int n,m,k=20,b,ans;
int a[1<<maxk],t[1<<maxk];
void fwtxor(int *a,int n,int fl=1){
	for(int l=2;l<=n;l<<=1){
		int k=l>>1;
		for(int i=0;i<n;i+=l){
			for(int j=i;j<i+k;j++){
				int u=a[j],v=a[j+k];
				a[j]=(u+v)*fl%mod,a[j+k]=(u+mod-v)*fl%mod;
			}
		}
	}
}
int ff[maxn][maxm],gg[maxn][maxm];
int f[maxn];
void work(){
	n=read();m=read();b=read();
	for(int i=1;i<=n;i++)t[read()]++;
	fwtxor(t,1<<k);
	ff[0][0]=1;
	for(int i=1;i<=n;i++){
		for(int j=0;j<m;j++){
			inc(ff[i][j],ff[i-1][j]);
			inc(ff[i][(j+1)%m],ff[i-1][j]);
		}
	}
	gg[0][0]=1;
	for(int i=1;i<=n;i++){
		for(int j=0;j<m;j++){
			inc(gg[i][j],gg[i-1][j]);
			inc(gg[i][(j+1)%m],mod-gg[i-1][j]);
		}
	}
	for(int i=0;i<=n;i++){
		for(int j=0;j<m;j++)(f[i]+=ff[i][j]*gg[n-i][(m-j)%m])%=mod;
	}
	for(int s=0;s<(1<<k);s++){
		if(t[s]>n)t[s]-=mod;
		a[s]=f[(n+t[s])/2];
	}
	fwtxor(a,1<<k,(mod+1)/2);
	for(int s=1;s<(1<<k);s++)(ans+=a[s]*ksm(s,b))%=mod;
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