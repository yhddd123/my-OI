#include<bits/stdc++.h>
// #define int long long
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
const int maxn=4010;
const int inf=1e9;
bool mbe;

int n,m;
int a[maxn],b[maxn];
db dp[maxn][maxn];
int sa[maxn],sb[maxn];
mt19937 rnd(time(0));
const int B=10;
void work(){
	n=read();m=read();
	for(int i=1;i<=2*n;i+=2)a[i]=read();
	for(int i=2;i<=2*n;i+=2)a[i]=read();
	for(int i=1;i<=2*m;i+=2)b[i]=read();
	for(int i=2;i<=2*m;i+=2)b[i]=read();
	n=2*n-1,m=2*m-1;
	for(int i=1;i<=n;i++)sa[i]=sa[i-1]+a[i];
	for(int i=1;i<=m;i++)sb[i]=sb[i-1]+b[i];
	for(int i=0;i<=n;i++)for(int j=0;j<=m;j++)dp[i][j]=inf;
	dp[0][0]=0;
	for(int i=0;i<=n;i++){
		for(int j=0;j<=m;j++){
			dp[i+1][j]=min(dp[i+1][j],dp[i][j]+a[i+1]);
			dp[i][j+1]=min(dp[i][j+1],dp[i][j]+b[j+1]);
			if((i&1)&&!(j&1)){
				for(int k=j+1;k<=m&&k<=j+B;k+=2)dp[i+1][k]=min(dp[i+1][k],dp[i][j]+sqrtl(1.0*a[i+1]*a[i+1]+1.0*(sb[k]-sb[j])*(sb[k]-sb[j])));
			}
			if((j&1)&&!(i&1)){
				for(int k=i+1;k<=n&&k<=i+B;k+=2)dp[k][j+1]=min(dp[k][j+1],dp[i][j]+sqrtl(1.0*b[j+1]*b[j+1]+1.0*(sa[k]-sa[i])*(sa[k]-sa[i])));
			}
		}
	}
	printf("%.10Lf\n",dp[n][m]);
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