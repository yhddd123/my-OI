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
const int maxn=5010;
const int inf=1e18;
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch-48);ch=getchar();}
	return x*f;
}
bool Mbe;

int n,ans;
int dp[maxn][maxn],f[maxn];
int fac[maxn];
void inc(int &u,int v){((u+=v)>=mod)&&(u-=mod);}
inline int ksm(int a,int b=mod-2){
	int ans=1;
	while(b){
		if(b&1)ans=ans*a%mod;
		a=a*a%mod;
		b>>=1;
	}
	return ans;
}
void work(){
	n=read();
	if(n==3){puts("1");return ;}
	if(n==4){puts("2");return ;}
	n--;
	fac[0]=1;for(int i=1;i<=n;i++)fac[i]=fac[i-1]*i%mod;
	dp[1][1]=dp[2][1]=dp[3][1]=1;
	for(int i=2;i<=n;i++){
		for(int j=1;j<=i;j++){
			inc(dp[i][j],dp[i-1][j-1]);
			if(i>=2)inc(dp[i][j],dp[i-2][j-1]);
			if(i>=3)inc(dp[i][j],dp[i-3][j-1]);
			// cout<<i<<" "<<j<<" "<<dp[i][j]<<"\n";
		}
	}
	for(int i=1;i<=n;i++){
		f[i]=(dp[n-1][i]+dp[n-1][i-1]+dp[n-2][i]+dp[n-2][i-1]+dp[n-3][i-1])%mod;
		// cout<<i<<" "<<f[i]<<"\n";
	}
	for(int i=1;i<=n;i++){
		(ans+=(f[i]*fac[i]%mod*fac[n-i]%mod+mod-f[i-1]*fac[i-1]%mod*fac[n-i+1]%mod)%mod*i)%=mod;
		// cout<<i<<" "<<f[i]*fac[i]%mod*fac[n-i]%mod<<" "<<(f[i]*fac[i]%mod*fac[n-i]%mod+mod-f[i-1]*fac[i-1]%mod*fac[n-i+1]%mod)%mod<<"\n";
	}
	// cout<<ans<<" "<<fac[n]<<"\n";
	printf("%lld\n",(ans*ksm(fac[n])+1)%mod);
}

// \
444

bool Med;
int T;
signed main(){
//	freopen("color.in","r",stdin);
//	freopen("color.out","w",stdout);
	
//	ios::sync_with_stdio(0);
//	cin.tie(0);cout.tie(0);
	
//	cerr<<(&Mbe-&Med)/1048576.0<<" MB\n";
	
	T=1;
	while(T--)work();
}
