// Problem: P3343 [ZJOI2015] 地震后的幻想乡
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P3343
// Memory Limit: 125 MB
// Time Limit: 1000 ms
// Written by yhm.
// Start codeing:2024-08-07 17:11:40
// 
// Powered by CP Editor (https://cpeditor.org)

#include<bits/stdc++.h>
#define int long long
#define mod 998244353ll
#define pii pair<int,int>
#define fi first
#define se second
#define mems(x,y) memset(x,y,sizeof(x))
using namespace std;
const int maxn=10;
const int inf=1e18;
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch-48);ch=getchar();}
	return x*f;
}
bool Mbe;

int n,m;
bool e[maxn][maxn];
double dp[1<<maxn][maxn*maxn],ans;
int d[1<<maxn];
double c[maxn*maxn][maxn*maxn];
void work(){
	n=read(),m=read();
	for(int i=1;i<=m;i++){
		int u=read()-1,v=read()-1;
		e[u][v]=1;
	}
	for(int s=0;s<(1<<n);s++){
		for(int i=0;i<n;i++)if(s&(1<<i)){
			for(int j=0;j<n;j++)if(s&(1<<j))d[s]+=e[i][j];
		}
	}
	for(int i=0;i<=m;i++){
		c[i][0]=1;
		for(int j=1;j<=i;j++)c[i][j]=c[i-1][j]+c[i-1][j-1];
	}
	for(int s=1;s<(1<<n);s++){
		for(int i=0;i<=d[s];i++){
			for(int t=(s-1)&s;;t=(t-1)&s){
				if(t&(s&(-s))){
					for(int j=0;j<=min(i,d[t]);j++){
						dp[s][i]+=(c[d[t]][j]-dp[t][j])*c[d[s^t]][i-j];
					}
				}
				if(!t)break ;
			}
			// if(dp[s][i])cout<<s<<" "<<i<<" "<<dp[s][i]<<"\n";
		}
	}
	for(int i=0;i<=m;i++){
		ans+=dp[(1<<n)-1][i]/c[m][i];
	}
	printf("%.6lf\n",ans/(m+1.0));
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
