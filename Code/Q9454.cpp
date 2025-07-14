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
const int maxn=200010;
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
int dp[maxn][4][2];
int c[10];
int nxt[4][2];
void work(){
	n=read();scanf("%s",s+1);
	for(int i=0;i<=n;i++){
		for(int j=0;j<4;j++)dp[i][j][0]=dp[i][j][1]=-inf;
	}
	c[0]=c[1]=c[3]='C',c[2]='P';
	c[4]=c[5]=c[7]='C',c[6]='P';
	nxt[0][0]=0,nxt[1][0]=0,nxt[2][0]=2,nxt[3][0]=0;
	nxt[0][1]=1,nxt[1][1]=2,nxt[2][1]=3,nxt[3][1]=1;
	dp[0][0][0]=0,dp[0][1][1]=0;
	for(int i=1;i<=n;i++){
		for(int j=0;j<4;j++){
			for(int p=0;p<2;p++)if(dp[i-1][j][p]>=0){
				// cout<<i-1<<" "<<j<<" "<<p<<" "<<dp[i-1][j][p]<<"\n";
				if(s[i]==c[j]){
					dp[i][nxt[j][1]][p]=max(dp[i][nxt[j][1]][p],dp[i-1][j][p]+(j==3));
				}
				else{
					dp[i][nxt[j][0]][p]=max(dp[i][nxt[j][0]][p],dp[i-1][j][p]);
				}
			}
			if(s[i]==c[j]){
				dp[i][nxt[nxt[j][1]][1]][1]=max(dp[i][nxt[nxt[j][1]][1]][1],dp[i-1][j][0]+(j+1>=3));
				dp[i][nxt[nxt[j][1]][0]][1]=max(dp[i][nxt[nxt[j][1]][0]][1],dp[i-1][j][0]+(j>=3));
			}
			else{
				dp[i][nxt[nxt[j][0]][1]][1]=max(dp[i][nxt[nxt[j][0]][1]][1],dp[i-1][j][0]);
			}
		}
	}
	int ans=0;
	for(int i=0;i<4;i++)ans=max({ans,dp[n][i][0],dp[n][i][1]});
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
	
	T=read();
	while(T--)work();
}
