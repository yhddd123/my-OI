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

int n,m,ans;
int dp[maxn][maxn],f[maxn];
bool ban[maxn][maxn];
bool ok1[maxn][maxn];
int mx[maxn][maxn];
int val[maxn][maxn];
void work(){
	n=read();m=read();
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++)ban[i][j]=0;
	}
	for(int i=1;i<=m;i++)ban[read()][read()]=1;
	for(int i=1;i<=n;i++){
		bool fl=1;
		for(int j=i;j<=n;j++){
			fl&=!ban[j][j-i+1];
			ok1[i][j]=fl;
		}
	}
	for(int j=1;j<=n;j++)mx[n][j]=ban[n][j]?0:j;mx[n][n+1]=0;
	for(int i=n-1;i;i--){
		mx[i][n+1]=0;
		for(int j=1;j<=n;j++)mx[i][j]=ban[i][j]?0:max(j,mx[i+1][j+1]);
	}
	for(int i=0;i<=n;i++){
		for(int j=1;j<=n+1;j++)dp[i][j]=0;
	}
	dp[0][n+1]=1,f[0]=1;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++)val[i][j]=0;
	}
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++)(val[i][j]+=val[i-1][j])%=mod;
		for(int j=1;j<=i;j++)if(!ban[i][j]){
			dp[i][j]=0;
			if(ok1[i-j+1][i])(dp[i][j]+=f[i-j])%=mod;
		}
		dp[i][n+1]=0;
		for(int j=1;j<i;j++)if(!ban[i][j]){
			if(ok1[i-j+1][i]){
				(dp[i][n+1]+=val[i][j])%=mod;
				// for(int k=1;k<i-j+1;k++)if(mx[k][j+1]>=i-k+1){
					// (dp[i][n+1]+=f[k-1]+mod-dp[k-1][j])%=mod;
				// }
			}
		}
		// for(int j=1;j<=n+1;j++)cout<<dp[i][j]<<" ";cout<<"\n";
		f[i]=0;for(int j=1;j<=n+1;j++)(f[i]+=dp[i][j])%=mod;
		for(int j=1;j<=n;j++){
			int l=i+j,r=min(n,mx[i][j+1]+i-1),v=(f[i-1]+mod-dp[i-1][j])%mod;
			if(l>r)continue;
			(val[l][j]+=v)%=mod,(val[r+1][j]+=mod-v)%=mod;
		}
	}
	printf("%d\n",f[n]);
}

bool med;
int T;
signed main(){
	// freopen(".in","r",stdin);
	// freopen(".out","w",stdout);
	
	// cerr<<(&mbe-&med)/1024.0/1024.0<<"\n";
	
	T=read();
	while(T--)work();
}