// Problem: P8043 [COCI2016-2017#7] KLAVIR
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P8043
// Memory Limit: 64 MB
// Time Limit: 1000 ms
// Written by yhm.
// Start codeing:2024-09-08 21:35:20
// 
// Powered by CP Editor (https://cpeditor.org)

#include<bits/stdc++.h>
#define int long long
#define mod 1000000007ll
#define pii pair<int,int>
#define fi first
#define se second
#define mems(x,y) memset(x,y,sizeof(x))
#define pb push_back
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

int n,m,a[maxn];
int nxt[maxn],dp[maxn];
void work(){
	n=read();m=read();
	for(int i=1;i<=m;i++)a[i]=read();
	for(int i=2,j=0;i<=m;i++){
		while(j&&a[i]!=a[j+1])j=nxt[j];
		if(a[i]==a[j+1])j++;
		nxt[i]=j;
		// cout<<i<<" "<<nxt[i]<<"\n";
	}
	for(int i=1,mul=n;i<=m;i++){
		dp[i]=dp[nxt[i]]+mul;
		if(dp[i]>=mod)dp[i]-=mod;
		printf("%lld\n",dp[i]);
		mul=mul*n%mod;
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
