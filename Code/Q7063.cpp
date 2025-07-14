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

int n,a[maxn];
int fac[maxn],inv[maxn],ans;
inline int ksm(int a,int b=mod-2){
	int ans=1;
	while(b){
		if(b&1)ans=ans*a%mod;
		a=a*a%mod;
		b>>=1;
	}
	return ans;
}
int C(int m,int n){
	if(m<0||n<0||m<n)return 0;
	return fac[m]*inv[n]%mod*inv[m-n]%mod;
}
int t[maxn];
#define ull unsigned long long
mt19937 rnd(1);
unordered_map<ull,int> dp[maxn];
ull val[maxn],bas;
int dfs(int dep,int sum){
	if(sum>=a[n])return fac[n-dep-t[0]];
	ull hsh=0;for(int i=1;i<=a[n];i++)hsh=hsh*bas+val[t[i]];
	if(dp[dep][hsh])return dp[dep][hsh]-1;
	int res=0;
	for(int i=1;i<=sum;i++)if(t[i]){
		t[i]--;
		(res+=(t[i]+1)*dfs(dep+1,sum+i))%=mod;
		t[i]++;
	}
	// cout<<dep<<" "<<sum<<" "<<res<<"\n";
	// for(int i=1;i<=a[n];i++)cout<<t[i]<<" ";cout<<"\n";
	dp[dep][hsh]=res+1;return res;
}
void work(){
	n=read();
	for(int i=0;i<=n;i++)a[i]=read();
	sort(a+1,a+n+1);
	for(int i=1;i<=n;i++)t[a[i]]++;
	fac[0]=1;for(int i=1;i<=n;i++)fac[i]=fac[i-1]*i%mod;
	inv[n]=ksm(fac[n]);for(int i=n-1;~i;i--)inv[i]=inv[i+1]*(i+1)%mod;
	bas=rnd();for(int i=0;i<=n;i++)val[i]=rnd();
	printf("%lld\n",dfs(0,a[0])*C(n,t[0])%mod*fac[t[0]]%mod);
}

// \
444

bool Med;
int T;
signed main(){
	// freopen("silver.in","r",stdin);
	// freopen("silver.out","w",stdout);
	
//	ios::sync_with_stdio(0);
//	cin.tie(0);cout.tie(0);
	
	// cerr<<(&Mbe-&Med)/1048576.0<<" MB\n";
	
	T=1;
	while(T--)work();
}
