#include<bits/stdc++.h>
#define int long long
#define mod 998244353ll
#define pii pair<int,int>
#define fi first
#define se second
#define pb push_back
#define mkp make_pair
#define mems(a,x) memset((a),(x),sizeof(a))
using namespace std;
inline int read(){
	int x=0,fl=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')fl=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
	return x*fl;
}
const int maxn=3010;
const int inf=1e18;
bool mbe;

int n,a[maxn];
int dp[maxn][maxn],f[maxn],s[maxn];
void work(){
	for(int i=1;i<=n;i++)a[i]=read();a[n+1]=inf;
	for(int i=1;i<n;i++)s[i]=s[i-1]+(a[i+1]-a[i])*(a[i+1]-a[i]);
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++)dp[i][j]=inf;
	}
	for(int j=2;j<=n;j++)dp[1][j]=(a[j]-a[1])*(a[j]-a[1]);
	for(int i=2;i<=n;i++){
		f[i]=inf;for(int j=i-1;j;j--)f[j]=min(f[j+1],dp[j][j+1]-s[j]);
		for(int j=i,p=i;j<=n;j++){
			while(p>1&&a[j]-a[i]>=a[i]-a[p-1])p--;
			dp[i][j]=min(dp[i][j],s[i-1]+f[p]+(a[j]-a[i])*(a[j]-a[i]));
		}
		for(int p=1,j=n+1;p<i;p++){
			while(j>=i&&a[j]-a[i]>a[i]-a[p])j--;
			dp[i][j]=min(dp[i][j],s[i-1]-s[p]+dp[p][p+1]+(a[i]-a[p])*(a[i]-a[p]));
		}
		for(int j=i;j<=n;j++)dp[i][j]=min(dp[i][j],dp[i-1][j]+(a[i]-a[i-1])*(a[i]-a[i-1]));
		for(int j=n-1;j>=i;j--)dp[i][j]=min(dp[i][j],dp[i][j+1]);
	}
	// for(int i=1;i<=n;i++){
		// for(int j=i;j<=n;j++)cout<<dp[i][j]<<" ";cout<<"\n";
	// }
	printf("%lld\n",dp[n][n]);
}

bool med;
int T;
signed main(){
	// freopen(".in","r",stdin);
	// freopen(".out","w",stdout);
	
	// cerr<<(&mbe-&med)/1024.0/1024.0<<"\n";
	
	while(~scanf("%lld",&n))work();
}