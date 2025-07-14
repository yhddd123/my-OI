#include<bits/stdc++.h>
#define int long long
#define mod 998244353ll
#define pii pair<int,int>
#define fi first
#define se second
#define mems(x,y) memset(x,y,sizeof(x))
using namespace std;
const int maxn=1000010;
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch-48);ch=getchar();}
	return x*f;
}
bool Mbe;

int n,dp[22][maxn];
void work(){
	n=read();
	mems(dp,0x3f);
	dp[0][1]=dp[1][1]=0;
	for(int i=2;i*i<=n;i++)dp[1][i]=i*(i-1)/2;
	for(int j=2;j<=20;j++){
		for(int i=2;i<=n;i++){ 
			dp[j][i]=min(dp[j][i],dp[j-1][i]);
			for(int k=2;k<=10;k++){
				dp[j][i]=min(dp[j][i],dp[j-1][i/k+i%k]+(i/k)*k*(k-1)/2);
				// if(i==n&&j==8&&dp[j][i]==1369097)cout<<k<<" "<<dp[j-1][i/k+i%k]<<"\n";
			}
		}
		cout<<j<<"\n";
	}
	for(int i=8;i<=20;i++)cout<<dp[i][n]<<" ";
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
