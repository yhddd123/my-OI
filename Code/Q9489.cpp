#include<bits/stdc++.h>
#define int long long
#define mod 998244353ll
#define pii pair<int,int>
#define fi first
#define se second
#define mems(x,y) memset(x,y,sizeof(x))
#define pb push_back
#define db double
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

int n;
char s[maxn];
int dp[2][maxn][maxn],cur;
void work(){
	n=read();scanf("%s",s+1);
	dp[0][0][0]=1;
	for(int i=1;i<=n;i++){
		for(int j=0;j<-i;j++)for(int k=0;j+k<=i;k++)dp[i&1][j][k]=0;
		for(int j=0;j<i;j++){
			for(int k=0;j+k<i;k++)if(dp[i-1][j][k]){
				int l=i-1-j-k;
				
			}
		}
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
	
	// cerr<<(&Mbe-&Med)/1048576.0<<" MB\n";
	
	T=1;
	while(T--)work();
}
