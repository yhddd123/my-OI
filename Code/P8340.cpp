// Problem: P8340 [AHOI2022] 山河重整
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P8340
// Memory Limit: 1 MB
// Time Limit: 3000 ms
// Written by yhm.
// Start codeing:2024-07-13 19:08:50
// 
// Powered by CP Editor (https://cpeditor.org)

#include<bits/stdc++.h>
#define int long long
#define pii pair<int,int>
#define fi first
#define se second
#define mems(x,y) memset(x,y,sizeof(x))
using namespace std;
const int maxn=500010;
const int inf=1e18;
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch-48);ch=getchar();}
	return x*f;
}
bool Mbe;

int n,mod,ans;
int pw[maxn],dp[maxn],f[maxn];
void inc(int &u,int v){((u+=v)>=mod)&&(u-=mod);}
void sovle(int n){
	if(n<=1)return ;sovle(n/2);
	for(int i=1;i<=n;i++)f[i]=0;
	for(int i=sqrt(2*n);i;i--){
		for(int j=n;j>=i;j--)f[j]=f[j-i];
		for(int j=0;2*i+(i+1)*j<=n;j++)inc(f[2*i+(i+1)*j],dp[j]);
		for(int j=i;j<=n;j++)inc(f[j],f[j-i]);
	}
	for(int i=n/2+1;i<=n;i++)inc(dp[i],mod-f[i]);
}
void work(){
	n=read();mod=read();
	pw[0]=1;for(int i=1;i<=n;i++)pw[i]=pw[i-1]*2%mod;
	for(int i=sqrt(2*n);i;i--){
		for(int j=n;j>=i;j--)dp[j]=dp[j-i];
		dp[i]++;
		for(int j=i;j<=n;j++)inc(dp[j],dp[j-i]);
	}
	dp[0]=1;sovle(n);
	for(int i=0;i<n;i++)(ans+=dp[i]*pw[n-i-1])%=mod;
	printf("%lld\n",(pw[n]-ans+mod)%mod);
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
