// Problem: AT_abc309_g [ABC309G] Ban Permutation
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/AT_abc309_g
// Memory Limit: 1 MB
// Time Limit: 2000 ms
// Written by yhm.
// Start codeing:2025-04-17 18:29:08
// 
// Powered by CP Editor (https://cpeditor.org)

#include<bits/stdc++.h>
#define int long long
#define mod 998244353ll
#define pii pair<int,int>
#define fi first
#define se second
#define pb push_back
#define mkp make_pair
#define mems(a,x) memset((a),(x),sizeof(a))
using namespace std;
inline int read(){
	int x=0,fl=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')fl=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
	return x*fl;
}
const int maxn=110;
const int inf=1e9;
bool mbe;

int n,x,t1,t2,all;
int dp[maxn][maxn][1<<8];
void inc(int &u,int v){((u+=v)>=mod)&&(u-=mod);}
void work(){
	n=read();x=read()-1,all=(1<<2*x)-1;
	for(int i=0;i<2*x;i+=2)t1|=1<<i;
	for(int i=1;i<2*x;i+=2)t2|=1<<i;
	dp[0][0][all]=1;
	for(int i=1;i<=n;i++){
		for(int j=0;j<i;j++){
			for(int s=0;s<=all;s++)if(dp[i-1][j][s]){
				int c1=j-(x-__builtin_popcount(s&t1&(~t2)));
				int c2=j-(x-__builtin_popcount(s&t2&(~t1)));
				inc(dp[i][j+1][(s<<2)&all],dp[i-1][j][s]);
				inc(dp[i][j][(s<<2|1)&all],dp[i-1][j][s]*c2%mod);
				inc(dp[i][j][(s<<2|2)&all],dp[i-1][j][s]*c1%mod);
				if(j)inc(dp[i][j-1][(s<<2|3)&all],dp[i-1][j][s]*c1*c2%mod);
			}
		}
	}
	printf("%lld\n",dp[n][0][all]);
}

bool med;
int T;
signed main(){
	// freopen(".in","r",stdin);
	// freopen(".out","w",stdout);
	
	// cerr<<(&mbe-&med)/1024.0/1024.0<<"\n";
	
	T=1;
	while(T--)work();
}