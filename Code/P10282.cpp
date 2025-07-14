// Problem: P10282 [USACO24OPEN] Smaller Averages G
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P10282
// Memory Limit: 256 MB
// Time Limit: 2000 ms
// Written by yhm.
// Start codeing:2024-04-19 18:01:22
// 
// Powered by CP Editor (https://cpeditor.org)

#include<bits/stdc++.h>
#define int long long
#define mod 1000000007ll
#define pii pair<int,int>
#define fi first
#define se second
#define mems(x,y) memset(x,y,sizeof(x))
using namespace std;
const int maxn=510;
const int inf=1e18;
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch-48);ch=getchar();}
	return x*f;
}
bool Mbe;

int n,a[maxn],b[maxn];
int dp[maxn][maxn];
int ida[maxn],sum[maxn][maxn],idb[maxn][maxn];
void work(){
	n=read();
	for(int i=1;i<=n;i++)a[i]=read()+a[i-1];
	for(int i=1;i<=n;i++)b[i]=read()+b[i-1];
	dp[0][0]=1;
	for(int i=1;i<=n;i++){
		for(int j=0;j<i;j++)idb[i][j+1]=j;
		sort(idb[i]+1,idb[i]+i+1,[&](int u,int v){
			return (b[i]-b[u])*(i-v)<(b[i]-b[v])*(i-u);
		});
	}
	for(int i=1;i<=n;i++){
		for(int j=0;j<i;j++)ida[j+1]=j;
		sort(ida+1,ida+i+1,[&](int u,int v){
			return (a[i]-a[u])*(i-v)<(a[i]-a[v])*(i-u);
		});
		// for(int j=1;j<=i;j++)cout<<ida[j]<<" "<<1.0*(a[i]-a[ida[j]])/(i-ida[j])<<"\n";cout<<"\n";
		for(int j=1;j<=i;j++){
			for(int k=0;k<=n;k++)sum[j][k]=(sum[j-1][k]+dp[ida[j]][k])%mod;
		}
		for(int j=1;j<=n;j++){
			for(int k=1,l=0;k<=j;k++){
				while(l<i&&(a[i]-a[ida[l+1]])*(j-idb[j][k])<=(b[j]-b[idb[j][k]])*(i-ida[l+1]))l++;
				(dp[i][j]+=sum[l][idb[j][k]])%=mod;
				// cout<<i<<" "<<j<<" "<<dp[i][j]<<" "<<l<<" "<<ida[l]<<" "<<k<<" "<<idb[j][k]<<"\n";
			}
			// cout<<i<<" "<<j<<" "<<dp[i][j]<<"\n";
			// cout<<dp[i][j]<<" ";
		}
		// cout<<"\n";
	}
	printf("%lld\n",dp[n][n]);
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
