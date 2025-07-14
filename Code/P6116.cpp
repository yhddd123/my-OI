#include<bits/stdc++.h>
#define mod 1000000007
using namespace std;
const int maxn=410;
const int inf=1e9;
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch-48);ch=getchar();}
	return x*f;
}

int n,dp[2][maxn][maxn][3],ans=inf,cur;
int cnt0,cnt1,cnt2,pos[maxn][3],sum[maxn][3];
char c[maxn];

int T;
signed main(){
	//	freopen(".in","r",stdin);
	//	freopen(".out","w",stdout);
	
	scanf("%d%s",&n,c+1);
	for(int i=1;i<=n;i++){
		sum[i][0]=sum[i-1][0];
		sum[i][1]=sum[i-1][1];
		sum[i][2]=sum[i-1][2];
		if(c[i]=='R'){
			pos[++cnt0][0]=i;
			sum[i][0]++;
		}
		if(c[i]=='G'){
			pos[++cnt1][1]=i;
			sum[i][1]++;
		}
		if(c[i]=='Y'){
			pos[++cnt2][2]=i;
			sum[i][2]++;
		}
	}
	if(cnt0>n/2||cnt1>n/2||cnt2>n/2){
		printf("-1\n");
		return 0;
	}
	cur=1;
	dp[1][1][0][0]=pos[1][0]-1;
	dp[1][0][1][1]=pos[1][1]-1;
	dp[1][0][0][2]=pos[1][2]-1;
	for(int i=2;i<=n;i++){
		cur^=1;
		memset(dp[cur],0x3f,sizeof(dp[cur]));
		for(int j=0;j<=cnt0&&j<=i;j++){
			for(int k=0;k<=cnt1&&j+k<=i;k++){
				if(i-j-k<=cnt2){
					if(j)dp[cur][j][k][0]=min(dp[cur^1][j-1][k][1],dp[cur^1][j-1][k][2])+pos[j][0]-i+max(0,k-sum[pos[j][0]][1])+max(0,i-j-k-sum[pos[j][0]][2]);
					if(k)dp[cur][j][k][1]=min(dp[cur^1][j][k-1][0],dp[cur^1][j][k-1][2])+pos[k][1]-i+max(0,j-sum[pos[k][1]][0])+max(0,i-j-k-sum[pos[k][1]][2]);
					if(i-j-k>0)dp[cur][j][k][2]=min(dp[cur^1][j][k][0],dp[cur^1][j][k][1])+pos[i-j-k][2]-i+max(0,j-sum[pos[i-j-k][2]][0])+max(0,k-sum[pos[i-j-k][2]][1]);
					if(i==n){
						ans=min({ans,dp[cur][j][k][0],dp[cur][j][k][1],dp[cur][j][k][2]});
					}
				}
			}
		}
	}
	printf("%d\n",ans);
}
