#include<bits/stdc++.h>
#define int long long
#define mod 998244353ll
#define pii pair<int,int>
#define fi first
#define se second
#define mems(x,y) memset(x,y,sizeof(x))
using namespace std;
const int maxn=110;
const int inf=1e18;
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch-48);ch=getchar();}
	return x*f;
}
bool Mbe;

int n,ans,a[maxn];
int dp[2][maxn][maxn*maxn];
int cur;
void inc(int &u,int v){((u+=v)>=mod)&&(u-=mod);}
int fac[maxn];
void work(){
	n=read();
	for(int i=1;i<=n;i++)a[i]=read();
	int sum=0;for(int i=1;i<=n;i++)sum+=a[i];
	if(sum&1){puts("0");return ;}
	dp[cur=1][1][a[1]]=1;
	for(int i=2;i<=n;i++){
		for(int j=0;j<=i;j++){
			for(int s=0;s<=i*100;s++)dp[i&1][j][s]=0;
		}
		for(int j=0;j<i;j++){
			for(int s=0;s<=i*100;s++)if(dp[cur][j][s]){
				inc(dp[i&1][j][s],dp[cur][j][s]);
				inc(dp[i&1][j+1][s+a[i]],dp[cur][j][s]);
				
			}
		}
		cur^=1;
	}
	// cout<<sum<<"\n";
	fac[0]=1;for(int i=1;i<=n;i++)fac[i]=fac[i-1]*i%mod;
	for(int i=1;i<n;i++)if(dp[n&1][i][sum/2])(ans+=fac[i]*fac[n-i]*2%mod*dp[n&1][i][sum/2])%=mod;
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
