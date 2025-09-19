#include<bits/stdc++.h>
#define int long long
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
const int maxn=510;
const int inf=1e18;
bool mbe;

int n,d,r,a[maxn];
int f[maxn][maxn],g[maxn][maxn];
int dp[maxn];
void work(){
	n=read();d=read(),r=read();
	for(int i=1;i<=n;i++)a[i]=read()+a[i-1];
	for(int i=n;i;i--){
		for(int j=i;j<=n;j++){
			g[i][j]=0;for(int p=i;p<j;p++)g[i][j]=max(g[i][j],g[i][p]+f[p+1][j]);
			f[i][j]=0;for(int k=0;k<=j-i&&k<=g[i][j];k++)if((a[j]-a[i-1]-(k+1)*r)%d==0){f[i][j]=k+1;break;}
			g[i][j]=max(g[i][j],f[i][j]);
		}
	}
	// for(int i=1;i<=n;i++){
		// for(int j=i;j<=n;j++)cout<<i<<" "<<j<<" "<<f[i][j]<<" "<<g[i][j]<<"\n";
	// }`
	for(int i=1;i<=n;i++){
		dp[i]=dp[i-1];
		for(int j=1;j<=i;j++)if(f[j][i])dp[i]=max(dp[i],dp[j-1]+(a[i]-a[j-1]-f[j][i]*r)/d);
	}
	printf("%lld\n",dp[n]);
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