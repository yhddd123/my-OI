#include<bits/stdc++.h>
#define mems(x,y) memset(x,y,sizeof x)
using namespace std;
const int maxn=80010;
const int maxm=265;
const int inf=1e9;
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch-48);ch=getchar();}
	return x*f;
}

int n,m,k,num,ans=inf;
int sum[maxn][maxm],to[maxn];
int dp[2][maxm],cur,val[maxm];
void work(){
	n=read();m=read();k=read();
	for(int i=1;i<=m;i++){
		int u=read(),v=read(),w=read();
		if(u==v)continue;
		to[u]|=1<<(v-u-1);
		sum[u][v-u-1]+=w;
	}
	mems(dp,0x3f);
	dp[1][1]=0;
	num=(1<<k)-1;
	for(int i=1;i<n;i++){
		ans=min(ans,dp[i&1][0]);
		mems(dp[cur],0x3f);
		for(int j=0;j<=num;j++)val[j]=val[j^(j&-j)]+sum[i][__builtin_ctz(j)];
		for(int j=1;j<=num;j++)if(dp[i&1][j]<=inf){
			if(!(j&1))dp[cur][j>>1]=min(dp[cur][j>>1],dp[i&1][j]);
			else{
				int s=to[i]&(num^(j>>1));
				for(int t=s;;t=(t-1)&s){
					dp[cur][(j>>1)|t]=min(dp[cur][(j>>1)|t],dp[i&1][j]+val[s^t]);
					if(!t)break;
				}
			}
		}
		cur^=1;
	}
	printf("%d\n",ans);
}

int T;
signed main(){
	//	freopen(".in","r",stdin);
	//	freopen(".out","w",stdout);
	
	T=1;
	while(T--)work();
}
