#include<bits/stdc++.h>
// #define int long long
#define mod 998244353ll
#define pii pair<int,int>
#define fi first
#define se second
#define pb push_back
#define db long double
#define mems(a,x) memset((a),(x),sizeof(a))
using namespace std;
inline int read(){
	int x=0,fl=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')fl=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
	return x*fl;
}
const int maxn=5010;
const int inf=1e9;
bool mbe;

int n,a[maxn];
int dp[maxn][maxn];
int mx[maxn][maxn];
bool vis[maxn*maxn];
void work(){
	n=read();
	for(int i=1;i<=n;i++)a[i]=read()+a[i-1];
	// for(int i=2;i<=n;i++){
		// for(int j=2;j<=i;j++){
			// for(int k=j;k<i;k++)if(2*a[j-1]-a[k]>=0)vis[2*a[j-1]-a[k]]=1;
			// for(int k=j-1,w=0;k;k--){
				// dp[i][j]=max(dp[i][j],dp[j-1][k]+w);
				// w+=vis[a[k-1]];
			// }
			// for(int k=j;k<i;k++)if(2*a[j-1]-a[k]>=0)vis[2*a[j-1]-a[k]]=0;
			// // cout<<dp[i][j]<<" ";
		// }
		// // cout<<"\n";
	// }
	for(int j=2;j<=n;j++){
		dp[j][j]=mx[j-1][j-1];
		for(int i=j+1,k=j,w=0;i<=n;i++){
			if(2*a[j-1]-a[i-1]>=0)vis[2*a[j-1]-a[i-1]]=1;
			while(k>1&&a[i-1]-a[j-1]>=a[j-1]-a[k-2]){
				k--,w+=vis[a[k-1]];
			}
			if(k>1&&a[i-1]-a[j-1]==a[j-1]-a[k-1]){
				// cout<<i<<" "<<j<<" "<<k<<" "<<w<<"\n";
				dp[i][j]=max(dp[i][j],mx[j-1][k-1]+w);
			}
			dp[i][j]=max(dp[i][j],dp[i-1][j]);
			mx[i][j]=max(mx[i][j-1],dp[i][j]);
		}
		for(int i=j+1;i<=n;i++)if(2*a[j-1]-a[i-1]>=0)vis[2*a[j-1]-a[i-1]]=0;
	}
	// for(int i=1;i<=n;i++){
		// for(int j=1;j<=i;j++)cout<<dp[i][j]<<" ";cout<<"\n";
	// }
	int ans=0;for(int i=1;i<=n;i++)ans=max(ans,dp[n][i]);
	printf("%d\n",ans);
}

bool med;
int T;
signed main(){
	// freopen(".in","r",stdin);
	// freopen(".out","w",stdout);
	
	// cerr<<(&mbe-&med)/1024.0/1024.0<<"\n";
	
	T=1;
	while(T--)work();
}