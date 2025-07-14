#include<bits/stdc++.h>
#define int long long
#define mod 998244353ll
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

int n,m;
int l1[maxn],l2[maxn],r1[maxn],r2[maxn];
int dp[maxn][maxn][maxn<<1];
void work(){
	n=read();m=read();
	for(int i=1;i<=n;i++)l1[i]=read(),r1[i]=read();
	for(int i=1;i<=m;i++)l2[i]=read(),r2[i]=read();
	for(int i=l1[1];i<=r1[1];i++)for(int j=l2[1];j<=r2[1];j++)dp[1][1][i-j+maxn]++;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			for(int k=0;k<2*maxn;k++)if(dp[i][j][k]){
				if(k<0){
					for(int l=l1[i+1];l<=r1[i+1];l++)dp[i+1][j][k+l]+=dp[i][j][k];
				}
				else{
					for(int l=l2[i+1];l<=r2[i+1];l++)dp[i][j+1][k+l]+=dp[i][j][k];
				}
			}
			printf("%lld ",dp[i][j][maxn]);
		}
		printf("\n");
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
	
	T=1;
	while(T--)work();
}
