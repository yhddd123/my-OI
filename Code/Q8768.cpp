#include<bits/stdc++.h>
#define int long long
#define mod 998244353ll
#define pii pair<int,int>
#define fi first
#define se second
#define mems(x,y) memset(x,y,sizeof(x))
#define pb push_back
using namespace std;
const int maxn=5000010;
const int inf=1e18;
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch-48);ch=getchar();}
	return x*f;
}
bool Mbe;

int n,a[maxn],b[maxn],ans=inf;
int dp[2][maxn],cur;
void work(){
	n=read();
	for(int i=1;i<=n;i++)a[i]=read(),b[i]=read();
	for(int i=1;i<=n;i++){
		for(int j=0;j<=n*100000;j++)dp[i&1][j]=dp[cur][j]+b[i];
		for(int j=a[i];j<=n*100000;j++)dp[i&1][j]=min(dp[i&1][j],dp[cur][j-a[i]]);
		cur^=1;
	}
	for(int i=0;i<=n*100000;i++)ans=min(ans,max(i,dp[n&1][i]));
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
	
//	cerr<<(&Mbe-&Med)/1048576.0<<" MB\n";
	
	T=1;
	while(T--)work();
}
