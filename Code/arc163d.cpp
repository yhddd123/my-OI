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
const int maxn=31;
const int inf=1e9;
bool mbe;

int n,m;
int C[maxn][maxn];
int dp[maxn][maxn][maxn*maxn];
void work(){
	n=read();m=read();
	for(int i=0;i<=n;i++){
		C[i][0]=1;
		for(int j=1;j<=i;j++)C[i][j]=(C[i-1][j]+C[i-1][j-1])%mod;
	}
	dp[0][0][0]=1;
	for(int i=1;i<=n;i++){
		for(int j=0;j<i;j++){
			for(int k=0;k<=i*(i-1)/2;k++)if(dp[i-1][j][k]){
				for(int l=0;l<=j;l++)(dp[i][j+1][k+l]+=C[j][l]*dp[i-1][j][k])%=mod;
				for(int l=0;l<=i-1-j;l++)(dp[i][j][k+j+l]+=C[i-1-j][l]*dp[i-1][j][k])%=mod;
			}
		}
	}
	int ans=0;for(int j=1;j<=n;j++)(ans+=dp[n][j][m])%=mod;
	printf("%lld\n",ans);
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