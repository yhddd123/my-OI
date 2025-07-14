#include<bits/stdc++.h>
#define int long long
#define db double
#define mod 1000000007
#define pii pair<int,int>
#define mems(x,y) memset(x,y,sizeof x)
using namespace std;
const int maxn=210;
const int inf=1e18;
const db eps=1e-8;
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch-48);ch=getchar();}
	return x*f;
}

int n,ans=inf;
struct nd{
	int a,b;
}a[maxn];
int sum[maxn];
int dp[maxn][maxn*maxn];
void work(){
	n=read();
	for(int i=1;i<=n;i++)a[i]={read(),read()};
	sort(a+1,a+n+1,[&](const nd &u,const nd &v){
		return u.b>v.b;
	});
	for(int i=1;i<=n;i++)sum[i]=sum[i-1]+a[i].a;
	mems(dp,0x3f);
	dp[0][0]=0;
	for(int i=1;i<=n;i++){
		for(int j=0;j<=sum[i];j++){
			int k=sum[i]-j;
			if(j>=a[i].a)dp[i][j]=min(dp[i][j],max(dp[i-1][j-a[i].a],j+a[i].b));
			if(k>=a[i].a)dp[i][j]=min(dp[i][j],max(dp[i-1][j],k+a[i].b));
			if(i==n)ans=min(ans,dp[n][j]);
		}
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
