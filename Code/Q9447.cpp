#include<bits/stdc++.h>
#define int long long
#define mod 998244353ll
#define pii pair<int,int>
#define fi first
#define se second
#define mems(x,y) memset(x,y,sizeof(x))
using namespace std;
const int maxn=5010;
const int inf=1e18;
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch-48);ch=getchar();}
	return x*f;
}
bool Mbe;

int n,m,a[maxn],b[maxn];
int dp[maxn][maxn];
void work(){
	n=read();m=read();
	for(int i=1;i<=n;i++)a[i]=read();
	for(int i=1;i<=m;i++)b[i]=read();
	sort(a+1,a+n+1),sort(b+1,b+m+1);
	mems(dp,0x3f),dp[1][1]=0;
	for(int i=1;i<=n+1;i++){
		for(int j=1;j<=m+1;j++){
			dp[i+1][j+1]=min(dp[i+1][j+1],dp[i][j]+abs(a[i]-b[j]));
			dp[i+1][j]=min(dp[i+1][j],dp[i][j]);
			// cout<<dp[i][j]<<" ";
		}
		// cout<<"\n";
	}
	printf("%lld\n",dp[n+1][m+1]);
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