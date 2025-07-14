#include<bits/stdc++.h>
#define int long long
#define db double
#define mod 1000000007
using namespace std;
const int maxn=310;
const int inf=1e9;
const db eps=1e-9;
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch-48);ch=getchar();}
	return x*f;
}

int n,a[maxn],c[maxn],num[maxn],idx;
int dp[2][maxn][maxn],cur;
void sovle(){
	n=read();
	for(int i=1;i<=n;i++)a[i]=read();
	for(int i=1;i<=n;i++){
		for(int j=1;j<i;j++){
			int s=sqrt(a[i]*a[j]);
			if(s*s==a[i]*a[j]){
				c[i]=c[j];
				break;
			}
		}
		if(!c[i])c[i]=++idx;
	}
	sort(c+1,c+n+1);
	for(int i=1,t=0;i<=n;i++){
		num[i]=++t;
		if(c[i]!=c[i+1])t=0;
	}
	dp[cur][0][0]=1;
	for(int i=1;i<n;i++){
		for(int j=0;j<=n;j++){
			for(int k=0;k+j<=i;k++){
				if(!dp[cur][j][k])continue;
//				cout<<j<<" "<<k<<" "<<dp[cur][j][k]<<"\n";
				if(c[i]!=c[i+1]){
					dp[cur^1][j+k][0]+=dp[cur][j][k]*(i+1-j-k)%mod,dp[cur^1][j+k][0]%=mod;
					if(j+k)dp[cur^1][j+k-1][0]+=dp[cur][j][k]*(j+k)%mod,dp[cur^1][j+k-1][0]%=mod;
				}
				else{
					if(j)dp[cur^1][j-1][k]+=dp[cur][j][k]*j%mod,dp[cur^1][j-1][k]%=mod;
					dp[cur^1][j][k+1]+=dp[cur][j][k]*(num[i]*2-k)%mod,dp[cur^1][j][k-1]%=mod;
					dp[cur^1][j][k]+=dp[cur][j][k]*(i+1-j-num[i]*2+k)%mod,dp[cur^1][j][k]%=mod;
				}
				dp[cur][j][k]=0;
			}
		}
		cur^=1;
	}
	printf("%lld\n",dp[cur][0][0]);
}

int T;
signed main(){
	//	freopen(".in","r",stdin);
	//	freopen(".out","w",stdout);
	
	T=1;
	while(T--)sovle();
}
