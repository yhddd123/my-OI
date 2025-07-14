#include<bits/stdc++.h>
#define int long long
#define mod 1000000007
using namespace std;
const int maxn=4000010;
const int inf=1e9;
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch-48);ch=getchar();}
	return x*f;
}

int n,m,ans=inf;
int mx,a[maxn],sum[maxn];
int q[maxn],h=1,t=0;
int dp[maxn];
int X(int u){return a[u];}
int Y(int u){return dp[u]+sum[u];}
double slope(int u,int v){
	if(X(u)==X(v)){
		if(Y(u)<Y(v))return inf;
		return -inf;
	}
	return (double)((Y(u)-Y(v))/(X(u)-X(v)));
}

int T;
signed main(){
	//	freopen(".in","r",stdin);
	//	freopen(".out","w",stdout);
	
	n=read();m=read();
	for(int i=1;i<=n;i++){
		int u=read();
		mx=max(mx,u);
		a[u]++;sum[u]+=u;
	}
	for(int i=1;i<mx+m;i++)a[i]+=a[i-1],sum[i]+=sum[i-1];
	for(int i=0;i<m;i++)dp[i]=a[i]*i-sum[i];
	q[++t]=0;
	for(int i=m;i<m+mx;i++){
		while(h<t&&slope(q[h],q[h+1])<=i)h++;
		dp[i]=dp[q[h]]+(a[i]-a[q[h]])*i-(sum[i]-sum[q[h]]);
		while(h<t&&slope(q[t-1],q[t])>=slope(q[t-1],i-m+1))t--;
		q[++t]=i-m+1;
	}
	for(int i=mx;i<mx+m;i++)ans=min(ans,dp[i]);
	printf("%lld\n",ans);
}

//dp[i]=min(dp[j]+(a[i]-a[j])*i-(sum[i]-sum[j]))
//i*a[j]+(dp[i]+sum[i]-i*a[i])=(dp[j]+sum[j])

