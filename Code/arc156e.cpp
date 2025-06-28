// Problem: AT_arc156_e [ARC156E] Non-Adjacent Matching
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/AT_arc156_e
// Memory Limit: 1 MB
// Time Limit: 4000 ms
// Written by yhm.
// Start codeing:2025-05-30 15:52:22
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
const int maxn=3010;
const int maxm=10000010;
const int inf=1e9;
bool mbe;

int n,m,k,ans,ans1,ans2;
inline int ksm(int a,int b=mod-2){
	int ans=1;
	while(b){
		if(b&1)ans=ans*a%mod;
		a=a*a%mod;
		b>>=1;
	}
	return ans;
}
int fac[maxm],inv[maxm];
int C(int m,int n){return fac[m]*inv[n]%mod*inv[m-n]%mod;}
int sum[maxm][2],cnt[maxn][maxn<<1][2];
int dp[maxn][maxn<<1];
void work(){
	n=read();m=read();k=read();
	fac[0]=1;for(int i=1;i<=n+k;i++)fac[i]=fac[i-1]*i%mod;
	inv[n+k]=ksm(fac[n+k]);for(int i=n+k-1;~i;i--)inv[i]=inv[i+1]*(i+1)%mod;
	sum[0][0]=C(n-1,n-1);
	for(int i=1;i<=k;i++){
		sum[i][0]=sum[i-1][0],sum[i][1]=sum[i-1][1];
		(sum[i][i&1]+=C(i+n-1,n-1))%=mod;
	}
	for(int i=0;i<=n&&(m+1)*i<=k;i++){
		int val=sum[k-(m+1)*i][((m+1)*i)&1];
		(ans+=((i&1)?mod-1:1)*C(n,i)%mod*val)%=mod;
	}
	dp[0][0]=1;
	for(int i=1;i<=n;i++){
		for(int j=0,s=0;j<=2*m;j++){
			(s+=dp[i-1][j])%=mod;
			if(j>=m+1)(s+=mod-dp[i-1][j-m-1])%=mod;
			dp[i][j]=s;
		}
	}
	for(int t=2;t<=2*m&&t<=k;t++){
		int num=min(m,t)-max(0ll,t-m)+1;
		for(int s=(t&1);s<t&&s+t<=k;s+=2)(ans1+=dp[n-2][s]*num)%=mod;
	}
	for(int a=0;a<=m;a++){
		for(int b=0;b<=m;b++)cnt[abs(a-b)][a+b][(a+b)&1]++;
	}
	for(int i=0;i<=m;i++){
		for(int j=0;j<=2*m;j++){
			for(auto c:{0,1}){
				if(i)(cnt[i][j][c]+=cnt[i-1][j][c])%=mod;
				if(j)(cnt[i][j][c]+=cnt[i][j-1][c])%=mod;
				if(i&&j)(cnt[i][j][c]+=mod-cnt[i-1][j-1][c])%=mod;
			}
		}
	}
	for(int b=0;b<=m;b++){
		for(int s=0;s<b&&s+b<=k;s++){
			(ans2+=dp[n-3][s]*cnt[b-s-1][min(2*m,k-b-s)][(b+s)&1])%=mod;
		}
	}
	// cout<<ans<<" "<<ans1<<" "<<ans2<<"\n";
	(ans+=mod-ans1*n%mod+ans2*n%mod)%=mod;
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