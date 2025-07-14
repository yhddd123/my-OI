#include<bits/stdc++.h>
#define int long long
#define mod 998244353ll
#define pii pair<int,int>
#define fi first
#define se second
#define mems(x,y) memset(x,y,sizeof(x))
#define pb push_back
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

int n,a[maxn];
int B=2500000;
bitset<2500000> dp[maxn];
mt19937 rnd(1);
void work(){
	n=read();
	for(int i=1;i<=n;i++)a[i]=read();
	dp[0][0]=1;
	for(int i=1;i<=n;i++){
		dp[i]=(dp[i-1]<<(a[i]%B))|dp[i-1]|(dp[i-1]>>(B-a[i]%B));
	}
	while(1){
		vector<int> id;
		for(int i=n,s=0;i;i--){
			if(dp[i-1][s]&&dp[i-1][(s-a[i]%B+B)%B]&&(rnd()&1))id.pb(i),s=(s-a[i]%B+B)%B;
			else if(!dp[i-1][s])id.pb(i),s=(s-a[i]%B+B)%B;
		}
		int sum=0;for(int i:id)sum+=a[i];
		if(sum==1e9){
			printf("%lld ",id.size());for(int i:id)printf("%lld ",i);
			return ;
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
