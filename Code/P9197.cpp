#include<bits/stdc++.h>
#define int long long
#define mod 1000000007
#define ls nd<<1
#define rs nd<<1|1
using namespace std;
const int maxn=110;
const int maxm=1010;
const int inf=1e9;
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch-48);ch=getchar();}
	return x*f;
}

int n,m,a[maxn],ans;
int dp[2][maxn][maxm][2][2];
int cmp(int u,int v){return u>v;}

int T;
signed main(){
	//	freopen(".in","r",stdin);
	//	freopen(".out","w",stdout);
	
	n=read();m=read();
	if(n==1){
		printf("1\n");
		return 0;
	}
	for(int i=1;i<=n;i++)a[i]=read();
	sort(a+1,a+n+1,cmp);
	dp[1][1][0][0][0]=dp[1][1][0][0][1]=dp[1][1][0][1][0]=1;
	for(int i=2;i<=n;i++){
		int fl=(i-1)&1;int d=a[i-1]-a[i];
		for(int j=1;j<=i;j++){
			for(int k=0;k<=m;k++){
				dp[i&1][j][k][0][0]=dp[i&1][j][k][0][1]=dp[i&1][j][k][1][0]=dp[i&1][j][k][1][1]=0;
				
				//拓展
				if(k>=2*j*d){
					dp[i&1][j][k][0][0]+=dp[fl][j][k-2*j*d][0][0]*2*j;
					dp[i&1][j][k][0][1]+=dp[fl][j][k-2*j*d][0][0];
					dp[i&1][j][k][1][0]+=dp[fl][j][k-2*j*d][0][0];
				}
				if(k>=(2*j-1)*d){
					dp[i&1][j][k][0][1]+=dp[fl][j][k-(2*j-1)*d][0][1]*(2*j-1);
					dp[i&1][j][k][1][0]+=dp[fl][j][k-(2*j-1)*d][1][0]*(2*j-1);
					dp[i&1][j][k][1][1]+=dp[fl][j][k-(2*j-1)*d][0][1];
					dp[i&1][j][k][1][1]+=dp[fl][j][k-(2*j-1)*d][1][0];
				}
				if(k>=(2*j-2)*d)dp[i&1][j][k][1][1]+=dp[fl][j][k-(2*j-2)*d][1][1]*(2*j-2);
				
				//新增
				if(k>=(2*j-2)*d){
					dp[i&1][j][k][0][0]+=dp[fl][j-1][k-(2*j-2)*d][0][0]*j;
					dp[i&1][j][k][0][1]+=dp[fl][j-1][k-(2*j-2)*d][0][0];
					dp[i&1][j][k][1][0]+=dp[fl][j-1][k-(2*j-2)*d][0][0];
				}
				if(k>=(2*j-3)*d){
					dp[i&1][j][k][0][1]+=dp[fl][j-1][k-(2*j-3)*d][0][1]*(j-1);
					dp[i&1][j][k][1][0]+=dp[fl][j-1][k-(2*j-3)*d][1][0]*(j-1);
					dp[i&1][j][k][1][1]+=dp[fl][j-1][k-(2*j-3)*d][1][0];
					dp[i&1][j][k][1][1]+=dp[fl][j-1][k-(2*j-3)*d][0][1];
				}
				if(k>=(2*j-4)*d)dp[i&1][j][k][1][1]+=dp[fl][j-1][k-(2*j-4)*d][1][1]*(j-2);
				
				//合并
				if(k>=(2*j+2)*d)dp[i&1][j][k][0][0]+=dp[fl][j+1][k-(2*j+2)*d][0][0]*j;
				if(k>=(2*j+1)*d){
					dp[i&1][j][k][0][1]+=dp[fl][j+1][k-(2*j+1)*d][0][1]*j;
					dp[i&1][j][k][1][0]+=dp[fl][j+1][k-(2*j+1)*d][1][0]*j;
				}
				if(k>=(2*j)*d)dp[i&1][j][k][1][1]+=dp[fl][j+1][k-(2*j)*d][1][1]*j;
				
				dp[i&1][j][k][0][0]%=mod;dp[i&1][j][k][0][1]%=mod;dp[i&1][j][k][1][0]%=mod;dp[i&1][j][k][1][1]%=mod;
				
			}
		}
	}
	for(int j=0;j<=m;j++)ans+=dp[n&1][1][j][1][1],ans%=mod;
	printf("%lld\n",ans);
}
