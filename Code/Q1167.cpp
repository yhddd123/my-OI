#include<bits/stdc++.h>
#define int long long
#define mod 1000000007
#define ls nd<<1
#define rs nd<<1|1
using namespace std;
const int maxn=300010;
const int inf=1e9;
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch-48);ch=getchar();}
	return x*f;
}

int n,q,a[maxn],c[maxn];
inline int ksm(int a,int b){
	int ans=1;
	while(b){
		if(b&1)ans=ans*a%mod;
		a=a*a%mod;
		b>>=1;
	}
	return ans;
}
int sum[maxn],inv[maxn],s;
int dep[maxn],f[maxn];

int T;
signed main(){
	//	freopen(".in","r",stdin);
	//	freopen(".out","w",stdout);
	
	n=read();q=read();
	for(int i=1;i<n;i++)a[i]=read();
	for(int i=1;i<=n;i++)c[i]=read();
	for(int i=1;i<n;i++)sum[i]=sum[i-1]+a[i],inv[i]=ksm(sum[i],mod-2);
	for(int i=1;i<=n;i++){
		dep[i]=(c[i]+s*inv[i-1])%mod;
		s+=(dep[i]+c[i])*a[i]%mod,s%=mod;
	}
	s=0;
	for(int i=1;i<=n;i++){
		f[i]=(dep[i]*a[i]%mod+s)*inv[i]%mod;
		s+=a[i]*f[i],s%=mod;
	}
	while(q--){
		int u=read(),v=read();
		if(u==v){
			printf("0\n");
			continue;
		}
		if(u>v)swap(u,v);
		printf("%lld\n",(dep[u]+dep[v]-2*f[u]%mod+mod)%mod);
	}
}
