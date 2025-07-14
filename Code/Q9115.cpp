#include<bits/stdc++.h>
#define int long long
#define pii pair<int,int>
#define fi first
#define se second
#define mems(x,y) memset(x,y,sizeof(x))
#define pb push_back
#define db double
using namespace std;
const int maxn=200010;
const int inf=1e18;
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch-48);ch=getchar();}
	return x*f;
}
bool Mbe;

int n,mod,q;
int dp[19][1<<18];
void work(){
	n=read();mod=read();q=read();
	for(int i=0;i<=n;i++){
		for(int s=0;s<(1<<n);s++)dp[i][s]=1;
	}
	while(q--){
		int u=read(),v=read(),w=read();
		(dp[v][u]*=w)%=mod;
	}
	for(int i=0;i<n;i++){
		for(int j=1;j<=n;j++){
			for(int s=0;s<(1<<n);s++){
				(dp[j-1][s^(1<<i)]*=dp[j][s])%=mod;
			}
		}
	}
	for(int s=0;s<(1<<n);s++)printf("%lld ",dp[0][s]);
	
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
