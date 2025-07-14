#include<bits/stdc++.h>
#define int long long
#define db double
#define mod 1000000007
using namespace std;
const int maxn=510;
const int inf=1e18;
const int eps=1e-8;
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch-48);ch=getchar();}
	return x*f;
}

int n,d,r;
db c[maxn][maxn];
db dp[maxn][maxn],f[maxn][maxn];
db sum,num;
void work(){
	n=read();d=read();r=read();
	c[0][0]=1;
	for(int i=1;i<=n;i++){
		c[i][0]=1;
		for(int j=1;j<=i;j++)c[i][j]=c[i-1][j-1]+c[i-1][j];
	}
	dp[0][n]=1;
	for(int s=0;s<d;s++){
		for(int i=1;i<=n;i++){
			for(int j=1;j<=i&&s+j<=d;j++){
				dp[s+j][j]+=dp[s][i]*c[i][j];
				f[s+j][j]+=(f[s][i]+dp[s][i]*min(j,r))*c[i][j];
			}
		}
	}
	for(int i=1;i<=n;i++)sum+=(db)f[d][i];
	for(int i=1;i<=n;i++)num+=(db)dp[d][i];
	printf("%.8lf\n",sum/num+r);
}

int T;
signed main(){
	//	freopen(".in","r",stdin);
	//	freopen(".out","w",stdout);
	
	T=1;
	while(T--)work();
}
