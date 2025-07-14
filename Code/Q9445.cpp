#include<bits/stdc++.h>
#define int long long
#define mod 998244353ll
#define pii pair<int,int>
#define fi first
#define se second
#define mems(x,y) memset(x,y,sizeof(x))
using namespace std;
const int maxn=110;
const int maxm=50010;
const int inf=1e9;
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch-48);ch=getchar();}
	return x*f;
}
bool Mbe;

int n,a[maxn];
int dp[maxn][maxm];
void work(){
	n=read();
	for(int i=1;i<n;i++)a[i]=read();
	mems(dp,0x3f);
	for(int i=0;i<=50000;i++)dp[1][i]=i;
	for(int i=2;i<=n;i++){
		for(int j=0;j<=50000;j++)if(dp[i-1][j]<=inf){
			if(j+a[i-1]<=50000)dp[i][j+a[i-1]]=min(dp[i][j+a[i-1]],dp[i-1][j]+a[i-1]);
			if(j-a[i-1]>=0)dp[i][j-a[i-1]]=min(dp[i][j-a[i-1]],dp[i-1][j]);
			// cout<<i-1<<" "<<j<<" "<<dp[i-1][j]<<"\n";
		}
		for(int j=50000-a[i-1],val=inf;~j;j--){
			val=min(val,dp[i-1][j+a[i-1]]);
			dp[i][j]=min(dp[i][j],val);
		}
		for(int j=a[i-1],val=inf;j<=50000;j++){
			val=min(val,dp[i-1][j-a[i-1]]-(j-a[i-1]));
			dp[i][j]=min(dp[i][j],val+j);
		}
	}
	int ans=inf;for(int j=0;j<=50000;j++)ans=min(ans,dp[n][j]);
	printf("%lld\n",ans);
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
	
	// cerr<<(&Mbe-&Med)/1048576.0<<" MB\n";
	
	T=1;
	while(T--)work();
}