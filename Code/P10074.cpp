// Problem: P10074 [GDKOI2024 普及组] 刷野 III
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P10074
// Memory Limit: 512 MB
// Time Limit: 2000 ms
// Written by yhm.
// Start codeing:2024-09-10 15:16:15
// 
// Powered by CP Editor (https://cpeditor.org)

#include<bits/stdc++.h>
#define int long long
#define mod 998244353ll
#define pii pair<int,int>
#define fi first
#define se second
#define mems(x,y) memset(x,y,sizeof(x))
#define pb push_back
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

int n,m,a[maxn];
int dp[maxn],f[maxn];
int q[maxn],t;
void work(){
	n=read();m=read();
	for(int i=1;i<=n;i++)a[i]=read();
	sort(a+1,a+n+1);reverse(a+1,a+n+1);
	mems(dp,0x3f),dp[0]=0;
	for(int tt=1;tt<=m;tt++){
		mems(f,0x3f);q[t=1]=0;
		for(int i=1;i<=n;i++){
			while(t>1&&1.0*(dp[q[t]]-dp[q[t-1]])/(q[t]-q[t-1])>a[i])t--;
			f[i]=dp[q[t]]+a[i]*(i-q[t]);
			while(t>1&&1.0*(dp[i]-dp[q[t]])/(i-q[t])<1.0*(dp[q[t]]-dp[q[t-1]])/(q[t]-q[t-1]))t--;
			q[++t]=i;
		}
		for(int i=0;i<=n;i++)dp[i]=f[i];
		// for(int i=0;i<=n;i++)cout<<dp[i]<<" ";cout<<"\n";
	}
	int ans=inf;
	for(int i=1;i<=n;i++)ans=min(ans,dp[i]);
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
