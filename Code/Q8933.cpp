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
const int maxn=8010;
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
char op[3];
int dp[2][maxn],cur;
void work(){
	n=read();int num=0;
	mems(dp,-0x3f);dp[cur=0][0]=0;
	for(int i=1;i<=n;i++){
		scanf("%s",op);
		mems(dp[i&1],-0x3f);
		if(op[0]=='B'){
			++num;
			for(int j=0;j<=n;j++)dp[i&1][j+1]=max(dp[i&1][j+1],dp[cur][j]);
			for(int j=0;j<=n;j++)if(dp[cur][j]>0)dp[i&1][j]=max(dp[i&1][j],dp[cur][j]-1);
		}
		else{
			int u=read(),v=read();
			for(int j=0;j<=n;j++)dp[i&1][max(0ll,j-u)]=max(dp[i&1][max(0ll,j-u)],dp[cur][j]);
			for(int j=0;j<=n;j++)dp[i&1][j]=max(dp[i&1][j],dp[cur][j]+v);
		}
		// for(int j=0;j<=n;j++){
			// if(dp[i&1][j]<0)printf("-1 ");
			// else printf("%lld ",dp[i&1][j]);
		// }
		// puts("");
		cur^=1;
	}
	for(int j=0;j<=n;j++)if(dp[n&1][j]>=0){
		printf("%lld\n",2*num-j);
		return ;
	}
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
