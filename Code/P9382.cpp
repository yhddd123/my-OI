// Problem: P9382 [THUPC 2023 决赛] Freshman Dream
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P9382
// Memory Limit: 128 MB
// Time Limit: 1000 ms
// Written by yhm.
// Start codeing:2024-07-11 14:52:33
// 
// Powered by CP Editor (https://cpeditor.org)

#include<bits/stdc++.h>
#define int long long
#define mod 998244353ll
#define pii pair<int,int>
#define fi first
#define se second
#define bs bitset<110>
#define mems(x,y) memset(x,y,sizeof(x))
using namespace std;
const int maxn=110;
const int inf=1e18;
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch-48);ch=getchar();}
	return x*f;
}
bool Mbe;

int n,k;
int dp[maxn][maxn*maxn];
bs a[maxn],b[maxn],p[maxn],st[maxn],ans[maxn],cur;
bs fr[maxn][maxn*maxn];
bool vis[maxn];
void insert(bs x){
	for(int i=1;i<=n;i++)if(x[i]){
		if(!p[i][i]){p[i]=x;return ;}
		x^=p[i];
	}
}
void work(){
	n=read();k=read();dp[0][0]=1;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++)a[i][j]=read();
	}
	for(int t=1;t<=n;t++){
		for(int i=1;i<=n;i++)b[i]=a[i];
		for(int i=1;i<=n;i++)b[i][i]=b[i][i]^a[i][t];
		for(int i=1;i<=n;i++)p[i].reset();
		for(int i=1;i<=n;i++)insert(b[i]);
		for(int i=n;i;i--)if(p[i][i]){
			for(int j=1;j<i;j++)if(p[j][i])p[j]^=p[i];
		}
		int tp=0;
		for(int i=1;i<=n;i++)if(!p[i][i]){
			cur.reset();cur[i]=1;
			for(int j=1;j<i;j++)if(p[j][i])cur[j]=1;
			st[tp++]=cur;
		}
		for(int i=0;i<=n;i++)vis[i]=0;
		for(int s=0;s<(1<<tp);s++){
			cur.reset();
			for(int i=0;i<tp;i++)if(s&(1<<i))cur^=st[i];
			int cnt=cur.count();if(vis[cnt])continue;vis[cnt]=1;
			for(int i=cnt;i<=k;i++)if(!dp[t][i]&&dp[t-1][i-cnt])dp[t][i]=1,fr[t][i]=cur;
		}
	}
	if(!dp[n][k])puts("-1");
	else{
		puts("1");
		for(int i=n;i;i--){
			bs cur=fr[i][k];k-=cur.count();
			ans[i]=cur;
		}
		for(int i=1;i<=n;i++){
			for(int j=1;j<=n;j++)printf("%lld ",(int)ans[j][i]);
			printf("\n");
		}
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
