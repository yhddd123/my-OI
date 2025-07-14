#include<bits/stdc++.h>
using namespace std;
const int maxn=310;
const int inf=1e9;
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch-48);ch=getchar();}
	return x*f;
}

int n,l,r;
int a[maxn],s[maxn];
int dp[maxn][maxn],f[maxn][maxn];
void sovle(){
	n=read();l=read();r=read();
	for(int i=1;i<=n;i++)a[i]=read(),s[i]=s[i-1]+a[i];
	if(r<=1){
		printf("0\n");
		return ;
	}
	r=min(r,n);
	if(r==n){
		printf("%lld\n",s[n]);
		return ;
	}
	memset(dp,0x3f,sizeof(dp));
	for(int i=1;i<=n;i++)dp[i][i]=0;
	for(int i=n;i>=1;i--){
		memset(f,0x3f,sizeof(f));
		f[i][1]=0;
		for(int j=i+1;j<=n;j++){
			for(int k=r;k>=1;k--){
				for(int p=i;p<=j;p++)f[j][k]=min(f[j][k],f[p][k-1]+dp[p+1][j]);
			}
			for(int k=l;k<=r;k++)dp[i][j]=min(dp[i][j],f[j][k]);
			dp[i][j]+=s[j]-s[i-1];
			f[j][1]=dp[i][j];
		}
	}
	if(dp[1][n]>=inf)dp[1][n]=0;
	printf("%lld\n",dp[1][n]);
}

int T;
signed main(){
	//	freopen(".in","r",stdin);
	//	freopen(".out","w",stdout);
	
	T=read();
	while(T--)sovle();
}
