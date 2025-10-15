// Problem: P8321 『JROI-4』沈阳大街 2
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P8321
// Memory Limit: 512 MB
// Time Limit: 1000 ms
// Written by yhm.
// Start codeing:2025-10-13 21:11:54
// 
// Powered by CP Editor (https://cpeditor.org)

#include<bits/stdc++.h>
#define int long long
#define mod 998244353ll
#define pii pair<int,int>
#define fi first
#define se second
#define pb push_back
#define db long double
#define mems(a,x) memset((a),(x),sizeof(a))
using namespace std;
inline int read(){
	int x=0,fl=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')fl=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
	return x*fl;
}
const int maxn=5010;
const int inf=1e9;
bool mbe;

inline int ksm(int a,int b=mod-2){
    int ans=1;
    while(b){
        if(b&1)ans=ans*a%mod;
        a=a*a%mod;
        b>>=1;
    }
    return ans;
}
int n;pii a[maxn<<1];
int dp[2][maxn];
void work(){
	n=read();
	for(int i=1;i<=n;i++)a[i]={read(),0};
	for(int i=1;i<=n;i++)a[i+n]={read(),1};
	sort(a+1,a+2*n+1,greater<pii>());
	dp[0][0]=1;
	for(int i=1,cur=0,t0=0,t1=0;i<=2*n;i++,cur^=1){
		for(int j=0;j<=i&&j<=min(t0,t1)+1;j++)dp[i&1][j]=0;
		for(int j=0;j<i&&j<=min(t0,t1);j++)if(dp[cur][j]){
			(dp[i&1][j]+=dp[cur][j])%=mod;
			(dp[i&1][j+1]+=dp[cur][j]*a[i].fi%mod*((a[i].se?t0:t1)-j))%=mod;
		}
		(a[i].se?t1:t0)++;
		// for(int j=0;j<=i&&j<=min(t0,t1);j++)cout<<dp[i&1][j]<<" ";cout<<"\n";
	}
	int ans=dp[0][n];
	for(int i=1;i<=n;i++)ans=ans*ksm(i)%mod;
	printf("%lld\n",ans);
}

bool med;
int T;
signed main(){
	// freopen(".in","r",stdin);
	// freopen(".out","w",stdout);
	
	// cerr<<(&mbe-&med)/1024.0/1024.0<<"\n";
	
	T=1;
	while(T--)work();
}