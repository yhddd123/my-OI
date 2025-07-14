#include<bits/stdc++.h>
#define int long long
#define db double
#define mod 1000000007
using namespace std;
const int maxn=2010;
const int inf=1e9;
const db eps=1e-9;
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch-48);ch=getchar();}
	return x*f;
}

int n,p,w,ans;
int dp[maxn][maxn];
int q[maxn],h,t;
void sovle(){
	n=read();p=read();w=read();
	memset(dp,-0x3f,sizeof(dp));
	dp[0][0]=0;
	for(int i=1;i<=n;i++){
		int ap=read(),bp=read(),as=read(),bs=read();
		for(int j=0;j<=p;j++)dp[i][j]=dp[i-1][j];
		for(int j=0;j<=as;j++)dp[i][j]=max(dp[i][j],-ap*j);
		if(i>=w+1){
			h=1;t=0;
			for(int j=0;j<=p;j++){
				while(h<=t&&j-q[h]>as)h++;
				if(h<=t){
					int k=q[h];
					dp[i][j]=max(dp[i][j],dp[i-w-1][k]+k*ap-j*ap);
				}
				while(h<=t&&dp[i-w-1][q[t]]+q[t]*ap<=dp[i-w-1][j]+j*ap)t--;
				q[++t]=j;
			}
			h=1;t=0;
			for(int j=p;j>=0;j--){
				while(h<=t&&q[h]-j>bs)h++;
				if(h<=t){
					int k=q[h];
					dp[i][j]=max(dp[i][j],dp[i-w-1][k]+k*bp-j*bp);
				}
				while(h<=t&&dp[i-w-1][q[t]]+q[t]*bp<=dp[i-w-1][j]+j*bp)t--;
				q[++t]=j;
			}
		}
	}
	for(int i=0;i<=p;i++)ans=max(ans,dp[n][i]);
	printf("%lld\n",ans);
}

int T;
signed main(){
	//	freopen(".in","r",stdin);
	//	freopen(".out","w",stdout);
	
	T=1;
	while(T--)sovle();
}
