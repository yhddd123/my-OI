// Problem: CF914G Sum the Fibonacci
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/CF914G
// Memory Limit: 250 MB
// Time Limit: 4000 ms
// Written by yhm.
// Start codeing:2025-09-05 21:44:48
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
const int maxn=1<<17;
const int inf=1e9;
bool mbe;

int n,m=17;
int a[maxn],f[maxn],ans[maxn],ans1[maxn],ans2[maxn],ans3[maxn];
namespace fwt{
	void fwtand(int *a,int n,int fl=1){
		for(int l=2;l<=n;l<<=1){
			int k=l>>1;
			for(int i=0;i<n;i+=l){
				for(int j=i;j<i+k;j++)(a[j]+=a[j+k]*fl)%=mod;
			}
		}
	}
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
	int f[1<<17],g[1<<17];
	void muland(int *a,int *b,int *ans,int n){
		for(int i=0;i<n;i++)f[i]=a[i],g[i]=b[i];
		fwtand(f,n),fwtand(g,n);
		for(int i=0;i<n;i++)(f[i]*=g[i])%=mod;
		fwtand(f,n,mod-1);
		for(int i=0;i<n;i++)ans[i]=f[i],f[i]=g[i]=0;
	}
	void mulxor(int *a,int *b,int *ans,int n){
		for(int i=0;i<n;i++)f[i]=a[i],g[i]=b[i];
		fwtxor(f,n),fwtxor(g,n);
		for(int i=0;i<n;i++)(f[i]*=g[i])%=mod;
		fwtxor(f,n,(mod+1)/2);
		for(int i=0;i<n;i++)ans[i]=f[i],f[i]=g[i]=0;
	}
	int ff[18][1<<17],gg[18][1<<17],h[18];
	void mul(int *a,int *b,int *ans,int n){
		for(int i=0;i<=n;i++){
			for(int s=0;s<(1<<n);s++)ff[i][s]=gg[i][s]=0;
		}
		for(int s=0;s<(1<<n);s++)ff[__builtin_popcount(s)][s]=a[s],gg[__builtin_popcount(s)][s]=b[s];
		for(int i=0;i<=n;i++)fwtxor(ff[i],1<<n),fwtxor(gg[i],1<<n);
		for(int s=0;s<(1<<n);s++){
			for(int i=0;i<=n;i++){
				h[i]=0;for(int j=0;j<=i;j++)(h[i]+=ff[j][s]*gg[i-j][s])%=mod;
			}
			for(int i=0;i<=n;i++)ff[i][s]=h[i];
		}
		for(int i=0;i<=n;i++)fwtxor(ff[i],1<<n,(mod+1)/2);
		for(int s=0;s<(1<<n);s++)ans[s]=ff[__builtin_popcount(s)][s];
	}
}
void work(){
	n=read();
	for(int i=1;i<=n;i++)a[read()]++;
	f[0]=0,f[1]=1;for(int i=2;i<(1<<m);i++)f[i]=(f[i-1]+f[i-2])%mod;
	fwt::mul(a,a,ans1,m);
	for(int s=0;s<(1<<m);s++)ans1[s]=ans1[s]*f[s]%mod;
	for(int s=0;s<(1<<m);s++)ans2[s]=a[s]*f[s]%mod;
	fwt::mulxor(a,a,ans3,1<<m);
	for(int s=0;s<(1<<m);s++)ans3[s]=ans3[s]*f[s]%mod;
	fwt::fwtand(ans1,1<<m,1);
	fwt::fwtand(ans2,1<<m,1);
	fwt::fwtand(ans3,1<<m,1);
	for(int s=0;s<(1<<m);s++)ans[s]=ans1[s]*ans2[s]%mod*ans3[s]%mod;
	fwt::fwtand(ans,1<<m,mod-1);
	int res=0;for(int i=0;i<m;i++)(res+=ans[1<<i])%=mod;
	printf("%lld\n",res);
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