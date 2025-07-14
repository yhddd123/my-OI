// Problem: P3172 [CQOI2015] 选数
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P3172
// Memory Limit: 125 MB
// Time Limit: 1000 ms
// Written by yhm.
// Start codeing:2024-07-11 20:03:55
// 
// Powered by CP Editor (https://cpeditor.org)

#include<bits/stdc++.h>
#define int long long
#define mod 1000000007ll
#define pii pair<int,int>
#define fi first
#define se second
#define mems(x,y) memset(x,y,sizeof(x))
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

int n,k,l,r;
int dp[maxn],ans;
inline int ksm(int a,int b){
	int ans=1;
	while(b){
		if(b&1)ans=ans*a%mod;
		a=a*a%mod;
		b>>=1;
	}
	return ans;
}
void work(){
	n=read();k=read();l=read();r=read();
	l=(l+k-1)/k,r/=k;
	// cout<<l<<" "<<r<<"\n";
	for(int i=1;i<=r-l;i++)dp[i]=(ksm(r/i-(l-1)/i,n)-r/i+(l-1)/i+mod)%mod;
	for(int i=r-l;i;i--){
		for(int j=2*i;j<=r-l;j+=i)dp[i]+=mod-dp[j];
		dp[i]%=mod;
	}
	printf("%lld\n",dp[1]+(l==1));
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
