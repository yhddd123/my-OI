// Problem: P8329 [ZJOI2022] 树
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P8329
// Memory Limit: 1 MB
// Time Limit: 2000 ms
// Written by yhm.
// Start codeing:2024-07-12 16:45:54
// 
// Powered by CP Editor (https://cpeditor.org)

#include<bits/stdc++.h>
#define int long long
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

int n,mod;
int dp[2][maxn][maxn],cur;
void work(){
	n=read();mod=read();
	for(int i=1;i<n;i++)dp[1][1][i]=i;cur=1;
	for(int i=2;i<=n;i++){
		mems(dp[i&1],0);
		for(int x=1;x<i;x++){
			for(int y=1;y<=n-i+1;y++)if(dp[cur][x][y]){
				(dp[i&1][x][y]+=mod-dp[cur][x][y]*x%mod*y%mod)%=mod;
				(dp[i&1][x][y-1]+=dp[cur][x][y]*x%mod*(y-1))%=mod;
				(dp[i&1][x][y]+=mod-dp[cur][x][y]*x%mod*y%mod)%=mod;
				(dp[i&1][x+1][y]+=dp[cur][x][y]*x%mod*y)%=mod;
			}
		}
		int ans=0;for(int x=1;x<=i;x++)(ans+=dp[cur][x][1]*x)%=mod;
		printf("%lld\n",ans);
		cur^=1;
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
