// Problem: P6647 [CCC2019] Tourism
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P6647
// Memory Limit: 128 MB
// Time Limit: 4000 ms
// Written by yhm.
// Start codeing:2024-07-14 08:53:54
// 
// Powered by CP Editor (https://cpeditor.org)

#include<bits/stdc++.h>
#define int long long
#define mod 998244353ll
#define pii pair<int,int>
#define fi first
#define se second
#define mems(x,y) memset(x,y,sizeof(x))
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

int n,k,a[maxn];
int dp[maxn],pre[maxn],suf0[maxn],suf1[maxn];
void work(){
	n=read();k=read();
	for(int i=1;i<=n;i++)a[i]=read();
	for(int l=1,r=k;l<=n;l+=k,r=min(n,r+k)){
		for(int i=l;i<=r;i++)pre[i]=max(i==l?0:pre[i-1],a[i]);
		for(int i=l;i<=r;i++)dp[i]=max(suf0[max(0ll,i-k)]+pre[i],suf1[max(0ll,i-k)]);
		for(int i=r,suf=0;i>=l;i--)suf0[i]=max(suf0[i+1],dp[i]),suf1[i]=max(suf1[i+1],dp[i]+suf),suf=max(suf,a[i]);
	}
	printf("%lld\n",dp[n]);
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
