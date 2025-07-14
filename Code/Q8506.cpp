#include<bits/stdc++.h>
#define int long long
#define mod 998244353ll
#define pii pair<int,int>
#define fi first
#define se second
#define mems(x,y) memset(x,y,sizeof(x))
#define db long double
using namespace std;
const int maxn=6010;
const db inf=1e12;
const db eps=1e-9;
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch-48);ch=getchar();}
	return x*f;
}
bool Mbe;

int n,t,s;
db p[5][2];
int a[5][2],b[5][2];
db dp[6][maxn];
bool check(db x){
	for(int i=0;i<=t;i++)dp[n+1][i]=0;
	for(int i=n;i;i--){
		for(int j=0;j<=t;j++){
			dp[i][j]=inf;
			for(int k=0;k<2;k++){
				dp[i][j]=min(dp[i][j],p[i][k]*(j+a[i][k]>=t?inf:dp[i+1][j+a[i][k]]+a[i][k])+(1-p[i][k])*min(j+b[i][k]>=t?inf:dp[i+1][j+b[i][k]]+b[i][k],x));
			}
		}
	}
	// printf("%.6lf\n",dp[1][s]+s);
	return dp[1][s]+s<=x;
}
void work(){
	n=read();t=read();s=read();
	for(int i=1;i<=n;i++){
		for(int j=0;j<2;j++){
			p[i][j]=1.0*read()/100.0,a[i][j]=read(),b[i][j]=read();
		}
	}
	db l=0,r=1e18;
	for(int t=1;t<=1000;t++){
		db mid=(l+r)/2.0;
		if(check(mid))r=mid;
		else l=mid;
	}
	printf("%.10Lf\n",l);
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
