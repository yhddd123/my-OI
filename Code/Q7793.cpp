#include<bits/stdc++.h>
#define int long long
#define mod 998244353ll
#define pii pair<int,int>
#define fi first
#define se second
#define mems(x,y) memset(x,y,sizeof(x))
using namespace std;
const int maxn=10010;
const int inf=1e18;
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch-48);ch=getchar();}
	return x*f;
}
bool Mbe;

int n,a[maxn];
int dp[2][maxn],cur;
void work(){
	n=read();
	for(int i=1;i<=n;i++)a[i]=read();
	sort(a+1,a+n+1);
	for(int i=1;i<=n;i++)a[i]+=a[i-1];
	dp[cur=0][1]=0;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=i+1;j++)dp[i&1][j]=inf;
		for(int j=i;j;j--){
			dp[i&1][j+1]=min(dp[i&1][j+1],dp[cur][j]+(j&-j)-1);
			if(!(j&1))dp[i&1][j>>1]=min(dp[i&1][j>>1],dp[cur][j]+a[i]);
		}
		cur^=1;
	}
	printf("%lld\n",dp[n&1][1]);
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
