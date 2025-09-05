// Problem: CF2129D Permutation Blackhole
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/CF2129D
// Memory Limit: 500 MB
// Time Limit: 3000 ms
// Written by yhm.
// Start codeing:2025-09-05 15:13:36
// 
// Powered by CP Editor (https://cpeditor.org)

#include<bits/stdc++.h>
#define int long long
#define mod 998244353ll
#define pii pair<int,int>
#define fi first
#define se second
#define pb push_back
#define db long double
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
const int K=7;
bool mbe;

int n,s[maxn],ans;
int dp[maxn][maxn][K+1][K+1],sa[maxn][maxn][K+1],sb[maxn][maxn][K+1];
int C[maxn][maxn];
void work(){
	n=read();ans=0;
	for(int i=1;i<=n;i++)s[i]=read();
	for(int i=1;i<=n+1;i++)dp[i][i-1][0][0]=sa[i][i-1][0]=sb[i][i-1][0]=1;
	for(int i=0;i<=n;i++){
		C[i][0]=1;
		for(int j=1;j<=i;j++)C[i][j]=(C[i-1][j]+C[i-1][j-1])%mod;
	}
	int fac=1;for(int i=1;i<=n;i++)fac=fac*i%mod;
	for(int i=n;i;i--){
		for(int j=i;j<=n;j++){
			for(int a=0;a<=K;a++){
				sa[i][j][a]=sb[i][j][a]=0;
				for(int b=0;b<=K;b++)dp[i][j][a][b]=0;
			}
			for(int a=0;a<=K;a++){
				for(int b=0;b<=K;b++){
					for(int k=i;k<=j;k++){
						int aa=a,bb=b;
						if(i==1&&j==n){}
						else if(i==1)bb++;
						else if(j==n)aa++;
						else if(k-i>j-k)bb++;
						else aa++;
						if(aa>K||bb>K)continue;
						if(s[k]==-1)(dp[i][j][aa][bb]+=C[j-i][k-i]*sa[i][k-1][a]%mod*sb[k+1][j][b])%=mod;
						else{
							for(int c=0;c<=K&&c<=s[k];c++)if(s[k]-c<=K){
								(dp[i][j][aa][bb]+=C[j-i][k-i]*dp[i][k-1][a][c]%mod*dp[k+1][j][s[k]-c][b])%=mod;
							}
						}
					}
				}
			}
			for(int a=0;a<=K;a++){
				for(int b=0;b<=K;b++){
					// if(dp[i][j][a][b])cout<<i<<" "<<j<<" "<<a<<" "<<b<<" "<<dp[i][j][a][b]<<"\n";
					(sa[i][j][a]+=dp[i][j][a][b])%=mod,(sb[i][j][b]+=dp[i][j][a][b])%=mod;
				}
			}
		}
	}
	int ans=0;for(int a=0;a<=K;a++){
		for(int b=0;b<=K;b++)(ans+=dp[1][n][a][b])%=mod;
	}
	printf("%lld\n",ans);
}

bool med;
int T;
signed main(){
	// freopen(".in","r",stdin);
	// freopen(".out","w",stdout);
	
	// cerr<<(&mbe-&med)/1024.0/1024.0<<"\n";
	
	T=read();
	while(T--)work();
}