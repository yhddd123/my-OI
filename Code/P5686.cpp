#include<bits/stdc++.h>
#define int long long
#define mod 1000000007
using namespace std;
const int maxn=500010;
const int inf=1e18;
inline int read(){
	int x=0,f=1;
	char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){x=(x<<3)+(x<<1)+(c^48),c=getchar();}
	return x*f;
}

int n,a[maxn],b[maxn],ans;
int suma[maxn],sumb[maxn];

signed main(){
	n=read();
	for(int i=1;i<=n;i++)a[i]=read();
	for(int i=1;i<=n;i++)b[i]=read();
	for(int i=1;i<=n;i++)a[i]=a[i-1]+a[i],a[i]%=mod;
	for(int i=1;i<=n;i++)b[i]=b[i-1]+b[i],b[i]%=mod;
	for(int i=1;i<=n;i++){
		ans+=a[i]*b[i]%mod*i%mod;
		if(ans>=mod)ans-=mod;
//		cout<<ans<<" ";
		ans+=a[i-1]*b[i-1]%mod*(n+1-i)%mod;
		if(ans>=mod)ans-=mod;
//		cout<<ans<<"\n";
	}
//	cout<<ans<<"\n";
	for(int i=1;i<=n;i++)suma[i]=suma[i-1]+a[i],suma[i]%=mod;
	for(int i=1;i<=n;i++)sumb[i]=sumb[i-1]+b[i],sumb[i]%=mod;
	for(int i=1;i<=n;i++){
		ans-=suma[i-1]*b[i]%mod;
		if(ans<0)ans+=mod;
//		cout<<ans<<" ";
		ans-=sumb[i-1]*a[i]%mod;
		if(ans<0)ans+=mod;
//		cout<<ans<<"\n";
	}
	printf("%lld\n",ans%mod);
}

