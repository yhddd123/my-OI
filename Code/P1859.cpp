#include<bits/stdc++.h>
#define mod 1000000007
using namespace std;
const int maxn=110;

int n,p,a[maxn][maxn],x,y;
int dp[2][maxn][maxn][5],ans=0x3f3f3f3f;
int fx[4][2]={{-1,0},{0,-1},{1,0},{0,1}};
char c[maxn];
string s;

signed main(){
	cin>>n>>p>>x>>y;
	for(int i=1;i<=n;i++){
		cin>>c+1;
		for(int j=1;j<=n;j++){
			if(c[j]=='*'){
				a[i][j]=1;
			}
		}
	}
	memset(dp,0x3f,sizeof(dp));
	dp[0][x][y][0]=0;
	for(int i=1;i<=p;i++){
		cin>>s;
		for(int u=1;u<=n;u++){
			for(int v=1;v<=n;v++){
				for(int k=0;k<4;k++){
					if(s[0]=='L'){
						dp[i&1][u][v][k]=min(dp[(i-1)&1][u][v][k]+1,dp[(i-1)&1][u][v][(k+3)%4]);
					}
					if(s[0]=='R'){
						dp[i&1][u][v][k]=min(dp[(i-1)&1][u][v][k]+1,dp[(i-1)&1][u][v][(k+1)%4]);
					}
					if(s[0]=='F'){
						dp[i&1][u][v][k]=min(dp[(i-1)&1][u][v][k]+1,dp[(i-1)&1][u-fx[k][0]][v-fx[k][1]][k]);
					}
					if(s[0]=='B'){
						dp[i&1][u][v][k]=min(dp[(i-1)&1][u][v][k]+1,dp[(i-1)&1][u+fx[k][0]][v+fx[k][1]][k]);
					}
//					cout<<i<<" "<<s[0]<<" "<<u<<" "<<v<<" "<<k<<" "<<dp[i&1][u][v][k]<<"\n";
				}
			}
		}
		for(int u=1;u<=n;u++){
			for(int v=1;v<=n;v++){
				for(int k=0;k<4;k++){
					if(a[u][v])dp[i&1][u][v][k]=0x3f3f3f3f;
				}
			}
		}
	}
	for(int u=1;u<=n;u++){
		for(int v=1;v<=n;v++){
			for(int k=0;k<4;k++)ans=min(ans,dp[p&1][u][v][k]);
		}
	}
	printf("%lld\n",ans);
}

