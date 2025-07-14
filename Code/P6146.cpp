#include<bits/stdc++.h>
#define int long long
#define mod 1000000007
using namespace std;
const int maxn=100010;
const int inf=1e18;
inline int read(){
	int x=0,f=1;
	char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){x=(x<<3)+(x<<1)+(c^48),c=getchar();}
	return x*f;
}

int n,dp[maxn],t[maxn<<1],pw[maxn];
struct nd{
	int l,r;
	bool operator <(const nd &tmp)const{return l<tmp.l;}
}a[maxn];

signed main(){
	n=read();
	for(int i=1;i<=n;i++)a[i].l=read(),a[i].r=read();
	pw[0]=1;
	for(int i=1;i<=n;i++)pw[i]=pw[i-1]*2,pw[i]%=mod;
	sort(a+1,a+n+1);
	for(int i=1;i<=n;i++)t[a[i].r]++;
	for(int i=1;i<=n<<1;i++)t[i]+=t[i-1];
	for(int i=1;i<=n;i++){
		dp[i]=dp[i-1]*2+pw[t[a[i].l-1]];
		dp[i]%=mod;
	}
	printf("%lld\n",dp[n]);
}

