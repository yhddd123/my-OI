#include<bits/stdc++.h>
#define int long long
#define mod 998244353ll
#define pii pair<int,int>
#define fi first
#define se second
#define mems(x,y) memset(x,y,sizeof(x))
#define pb push_back
#define db double
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

int n;
char s[maxn];
int dp[2][maxn],cur;
void work(){
	scanf("%s",s+1);n=strlen(s+1);
	mems(dp,0);dp[0][0]=1;cur=0;
	for(int i=1;i<=n;i++){
		mems(dp[i&1],0);
		for(int j=0;j<=n;j++)if(dp[cur][j]){
			(dp[i&1][j+1]+=dp[cur][j])%=mod;
			(dp[i&1][j]+=dp[cur][j]*j)%=mod;
			if(s[i]=='1')(dp[i&1][j]+=dp[cur][j]*j)%=mod;
			if(s[i]=='1'&&j)(dp[i&1][j-1]+=dp[cur][j]*j*j)%=mod;
			// cout<<i-1<<" "<<j<<" "<<dp[cur][j]<<"\n";
		}
		cur^=1;
	}
	printf("%lld\n",dp[n&1][0]);
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
	
	T=read();
	while(T--)work();
}
