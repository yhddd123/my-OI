#include<bits/stdc++.h>
#define int long long
#define mod 1000000007ll
#define pii pair<int,int>
#define fi first
#define se second
#define mems(x,y) memset(x,y,sizeof(x))
#define pb push_back
#define db double
using namespace std;
const int maxn=1000010;
const int inf=1e18;
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch-48);ch=getchar();}
	return x*f;
}
bool Mbe;

int n,m,a[maxn],ans;
int dp[maxn];
int f[maxn],g[maxn];
int fac[maxn],inv[maxn],pw[maxn];
inline int ksm(int a,int b=mod-2){
	int ans=1;
	while(b){
		if(b&1)ans=ans*a%mod;
		a=a*a%mod;
		b>>=1;
	}
	return ans;
}
int pre[maxn],cnt;
bool vis[maxn];
void work(){
	n=read();m=read();
	for(int i=1;i<=n;i++)a[read()]=i;
	int p=n-1;while(a[p]<a[p+1])p--;
	// dp[0]=1;
	// for(int i=1;i<=m;i++){
		// for(int j=n;~j;j--)dp[j]=(dp[j-1]+dp[j]*j)%mod;
	// }
	// int res=0;for(int i=p;i<=n;i++)res+=dp[i];
	// for(int i=1;i<=n;i++)cout<<dp[i]<<" ";cout<<"\n";
	fac[0]=1;for(int i=1;i<=n;i++)fac[i]=fac[i-1]*i%mod;
	inv[n]=ksm(fac[n]);for(int i=n-1;~i;i--)inv[i]=inv[i+1]*(i+1)%mod;
	pw[1]=1;for(int i=2;i<=n;i++){
		if(!vis[i])pre[++cnt]=i,pw[i]=ksm(i,m);
		for(int j=1;j<=cnt&&i*pre[j]<=n;j++){
			vis[i*pre[j]]=1;
			pw[i*pre[j]]=pw[i]*pw[pre[j]]%mod;
			if(i%pre[j]==0)continue;
		}
	}
	for(int i=0;i<=n;i++)f[i]=pw[i]*inv[i]%mod;
	for(int i=0;i<=n;i++)g[i]=((i&1)?mod-1:1)*inv[i]%mod;
	for(int i=1;i<=n;i++)(g[i]+=g[i-1])%=mod;
	for(int i=0;i<=n;i++){
		int l=p-i,r=n-i;
		l=max(l,0ll),r=min(r,n-i);
		if(l>r)continue;
		// cout<<i<<" "<<l<<" "<<r<<" "<<ans<<"\n";
		(ans+=f[i]*(g[r]+mod-(l?g[l-1]:0)))%=mod;
	}
	printf("%lld\n",ans);
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
