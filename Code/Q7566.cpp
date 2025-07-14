#include<bits/stdc++.h>
#define int long long
#define db double
#define mod 1000000007
using namespace std;
const int maxn=25;
const int inf=1e9;
const db eps=1e-9;
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch-48);ch=getchar();}
	return x*f;
}

int n,m,l,a[maxn],d[maxn];
int sum[1<<maxn],dp[1<<maxn],ans;
void sovle(){
	n=read();
	for(int i=1;i<=n;i++)a[i]=read();
	for(int i=1;i<=n;i++)if(a[i]-a[i-1])d[l++]=a[i]-a[i-1];
	n=l;m=(1<<n)-1;ans=n;
	for(int i=1;i<=m;i++){
		int j=log2(i&(-i));
		sum[i]=sum[i^(1<<j)]+d[j];
		if(sum[i])continue;
		for(int k=i&(i-1);k;k=(k-1)&i){
			dp[i]=max(dp[i],dp[k]);
		}
		dp[i]++;ans=min(ans,n-dp[i]);
	}
	printf("%lld\n",ans);
}

int T;
signed main(){
	//	freopen(".in","r",stdin);
	//	freopen(".out","w",stdout);
	
	T=1;
	while(T--)sovle();
}
