#include<bits/stdc++.h>
#define int long long
#define db double
#define mod 998244353
using namespace std;
const int maxn=200010;
const int inf=1e18;
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch-48);ch=getchar();}
	return x*f;
}

int n,a,b,l[maxn],r[maxn];
inline int ksm(int a,int b=mod-2){
	int ans=1;
	while(b){
		if(b&1)ans=ans*a%mod;
		a=a*a%mod;
		b>>=1;
	}
	return ans;
}
int dp[maxn],sum[maxn],val[maxn];
int mul=1,cnt;

int T;
signed main(){
	//	freopen(".in","r",stdin);
	//	freopen(".out","w",stdout);
	
	n=read();a=read();b=read();
	for(int i=1;i<=n;i++)l[i]=read(),r[i]=read();
	dp[0]=sum[0]=1;
	for(int i=1;i<=n;i++){
		dp[i]=max(min(b,r[i])-l[i]+1,0ll)*sum[i-1]%mod;
		val[i]=max(r[i]-max(b+1,l[i])+1,0ll);
		if(i<=a-1||cnt)sum[i]=dp[i]+sum[i-1]*val[i]%mod,sum[i]%=mod;
		else sum[i]=dp[i]+(sum[i-1]-dp[i-a]*mul%mod+mod)*val[i],sum[i]%=mod;
		if(!val[i])++cnt;
		else mul=mul*val[i]%mod;
		if(i>=a){
			if(!val[i-a+1])--cnt;
			else mul=mul*ksm(val[i-a+1])%mod;
		}
	}
	printf("%lld\n",sum[n]);
}
