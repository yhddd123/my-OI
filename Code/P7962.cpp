#include<bits/stdc++.h>
#define int long long
#define db double
#define mod 1000000007
using namespace std;
const int maxn=10010;
const int inf=1e15;
const db eps=1e-9;
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch-48);ch=getchar();}
	return x*f;
}

int n,a[maxn],sum[maxn];
int dp[2][maxn*55],cur,ans=inf;
void work(){
	n=read();
	for(int i=1;i<=n;i++)a[i]=read();
	for(int i=1;i<n;i++)a[i]=a[i+1]-a[i];
	sort(a+1,a+n);
	for(int i=1;i<n;i++)sum[i]=sum[i-1]+a[i];
	for(int i=1;i<=a[n]*n;i++)dp[0][i]=inf;
	for(int i=1;i<n;i++){
		if(!a[i])continue;
		for(int j=0;j<=a[n]*n;j++)dp[cur^1][j]=inf;
		for(int j=0;j<=a[n]*n;j++){
			if(dp[cur][j]>=inf)continue;
			dp[cur^1][j+sum[i]]=min(dp[cur^1][j+sum[i]],dp[cur][j]+sum[i]*sum[i]);
			dp[cur^1][j+a[i]*i]=min(dp[cur^1][j+a[i]*i],dp[cur][j]+2*a[i]*j+a[i]*a[i]*i);
		}
		cur^=1;
	}
	for(int i=0;i<=a[n]*n;i++){
		if(dp[cur][i]>=inf)continue;
		ans=min(ans,n*dp[cur][i]-i*i);
	}
	printf("%lld\n",ans);
}

int T;
signed main(){
	//	freopen(".in","r",stdin);
	//	freopen(".out","w",stdout);
	
	T=1;
	while(T--)work();
}
