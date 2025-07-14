#include<bits/stdc++.h>
#define int long long
#define mod 998244353ll
#define pii pair<int,int>
#define fi first
#define se second
#define mems(x,y) memset(x,y,sizeof(x))
#define pb push_back
using namespace std;
const int maxn=1010;
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
double dp[maxn][maxn],p;
void work(){
	n=read();m=read();p=read();
	dp[n][m]=0.0;
	for(int i=n;i;i--){
		for(int j=m;j;j--){
			if(i==n&&j==m)continue;
			else if(i==n)dp[i][j]=dp[i][j+1]+p/4.0;
			else if(j==m)dp[i][j]=dp[i+1][j]+p/4.0;
			else{
				double a=dp[i][j+1],b=dp[i+1][j];
				if(a>b)swap(a,b);
				if(b>=a+p)dp[i][j]=a+p/4.0;
				else{
					dp[i][j]=a/2.0+(b-a)/(2*p)*(a+(b-a)/2.0)+(p-b+a)/(2*p)*b;
				}
			}
		}
	}
	printf("%.10lf\n",dp[1][1]);
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
