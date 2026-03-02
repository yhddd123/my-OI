// Problem: AT_agc033_e [AGC033E] Go around a Circle
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/AT_agc033_e
// Memory Limit: 1024 MB
// Time Limit: 2000 ms
// Written by yhm.
// Start codeing:2026-03-02 22:13:06
// 
// Powered by CP Editor (https://cpeditor.org)

#include<bits/stdc++.h>
#define int long long
#define mod 1000000007ll
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
const int maxn=200010;
const int inf=1e9;
bool mbe;

inline void inc(int &u,int v){((u+=v)>=mod)&&(u-=mod);}
int n,m,a[maxn],ans;
char s[maxn];
int b[maxn],k;
namespace sub1{
	int f[maxn][2][2];
	void sovle(){
		f[1][0][0]=f[1][1][1]=1;
		for(int i=2;i<=n;i++){
			for(int o=0;o<2;o++){
				inc(f[i][o][0]=f[i-1][o][0],f[i-1][o][1]);
				f[i][o][1]=f[i-1][o][0];
			}
		}
		printf("%lld\n",(f[n][0][0]+f[n][0][1]+f[n][1][0])%mod);
	}
}
int dp[maxn],sum[maxn];
void work(){
	n=read();m=read();scanf("%s",s+1);
	for(int i=1;i<=m;i++)a[i]=s[i]=='R';
	if(!a[1])for(int i=1;i<=m;i++)a[i]^=1;
	for(int l=1,r;l<=m;l=r+1){
		r=l;while(r<m&&a[l]==a[r+1])r++;
		b[++k]=r-l+1;
	}
	if(k==1)return sub1::sovle();
	if(n&1){puts("0");return ;}
	if(k&1)k--;
	int lim=b[1]+(!(b[1]&1));
	for(int i=3;i<=k;i+=2)if(b[i]&1)lim=min(lim,b[i]);
	n>>=1,lim=(lim+1)/2;
	dp[0]=sum[0]=1;
	// cout<<n<<" "<<lim<<"\n";
	for(int i=1;i<=n;i++){
		inc(dp[i]=sum[i-1],(i-lim-1>=0)?mod-sum[i-lim-1]:0);
		inc(sum[i]=sum[i-1],dp[i]);
	}
	for(int i=1;i<=min(n,lim);i++)inc(ans,1ll*dp[n-i]*(2*i)%mod);
	// for(int i=1;i<=n;i++)cout<<dp[i]<<" ";cout<<"\n";
	printf("%lld\n",ans);
}

bool med;
signed main(){
	// freopen(".in","r",stdin);
	// freopen(".out","w",stdout);
	
	cerr<<(&mbe-&med)/1024.0/1024.0<<"\n";
	
	int T=1;
	while(T--)work();
}