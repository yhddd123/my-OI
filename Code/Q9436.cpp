#include<bits/stdc++.h>
#define int long long
#define mod 998244353ll
#define pii pair<int,int>
#define fi first
#define se second
#define mems(x,y) memset(x,y,sizeof(x))
using namespace std;
const int maxn=3010;
const int inf=1e18;
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch-48);ch=getchar();}
	return x*f;
}
bool Mbe;

int n,m,a[maxn];
int dp[maxn][maxn<<1];
int ans[maxn];
int fac[maxn],inv[maxn];
inline int ksm(int a,int b=mod-2){
	int ans=1;
	while(b){
		if(b&1)ans=ans*a%mod;
		b>>=1;
		a=a*a%mod;
	}
	return ans;
}
int C(int m,int n){return fac[m]*inv[n]%mod*inv[m-n]%mod;}
int f[maxn][maxn];
void work(){
	n=read();m=read();
	for(int i=1;i<=n;i++)a[i]=read();
	sort(a+1,a+n+1);
	fac[0]=1;for(int i=1;i<=n;i++)fac[i]=fac[i-1]*i%mod;
	inv[n]=ksm(fac[n]);for(int i=n-1;~i;i--)inv[i]=inv[i+1]*(i+1)%mod;
	for(int i=0;i<=n;i++){
		for(int j=i;~j;j--)f[i][j]=(f[i][j+1]+C(i,j))%mod;
	}
	dp[n+1][0]=1;
	for(int i=n;i;i--){
		int res=0;
		for(int s=0;s<=m;s++){
			(dp[i][s]+=dp[i+1][s])%=mod;
			if(s+a[i]>=m){
				(res+=dp[i+1][s])%=mod;
			}
			else{
				(dp[i][s+a[i]]+=dp[i+1][s])%=mod;
			}
		}
		// cout<<i<<" "<<res<<"\n";
		for(int j=0;j<=i-1;j++){
			(ans[j]+=res*f[i-1][j])%=mod;
		}
	}
	for(int i=0;i<=n;i++)printf("%lld\n",ans[i]);
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