// Problem: P4717 【模板】快速莫比乌斯/沃尔什变换 (FMT/FWT)
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P4717
// Memory Limit: 250 MB
// Time Limit: 1000 ms
// Written by yhm.
// Start codeing:2024-05-12 09:13:47
// 
// Powered by CP Editor (https://cpeditor.org)

#include<bits/stdc++.h>
#define int long long
#define mod 998244353ll
#define pii pair<int,int>
#define fi first
#define se second
#define mems(x,y) memset(x,y,sizeof(x))
using namespace std;
const int inf=1e18;
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch-48);ch=getchar();}
	return x*f;
}
bool Mbe;

int n,a[1<<17],b[1<<17],ans[1<<17];
namespace fwt{
	void fwtor(int *a,int n,int fl=1){
		for(int l=2;l<=n;l<<=1){
			int k=l>>1;
			for(int i=0;i<n;i+=l){
				for(int j=i;j<i+k;j++)(a[j+k]+=a[j]*fl)%=mod;
			}
		}
	}
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
	void mulor(int *a,int *b,int *ans,int n){
		for(int i=0;i<n;i++)f[i]=a[i],g[i]=b[i];
		fwtor(f,n),fwtor(g,n);
		for(int i=0;i<n;i++)(f[i]*=g[i])%=mod;
		fwtor(f,n,mod-1);
		for(int i=0;i<n;i++)ans[i]=f[i],f[i]=g[i]=0;
	}
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
}
using fwt::mulor;
using fwt::muland;
using fwt::mulxor;

void work(){
	n=1<<read();
	for(int i=0;i<n;i++)a[i]=read();
	for(int i=0;i<n;i++)b[i]=read();
	mulor(a,b,ans,n);
	for(int i=0;i<n;i++)printf("%lld ",ans[i]);printf("\n");
	muland(a,b,ans,n);
	for(int i=0;i<n;i++)printf("%lld ",ans[i]);printf("\n");
	mulxor(a,b,ans,n);
	for(int i=0;i<n;i++)printf("%lld ",ans[i]);printf("\n");
}

// \
444

bool Med;
int T;
signed main(){
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
	
//	ios::sync_with_stdio(0);
//	cin.tie(0);cout.tie(0);
	
//	cerr<<(&Mbe-&Med)/1048576.0<<" MB\n";
	
	T=1;
	while(T--)work();
}