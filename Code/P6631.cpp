// Problem: P6631 [ZJOI2020] 序列
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P6631
// Memory Limit: 512 MB
// Time Limit: 1000 ms
// Written by yhm.
// Start codeing:2026-01-30 20:16:01
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
const int maxn=100010;
const int inf=1e9;
bool mbe;

int n,a[maxn];
int dp[maxn][2][2][2];
void work(){
	n=read();
	for(int i=1;i<=n;i++)a[i]=read();
	mems(dp,-0x3f);dp[0][0][0][0]=0;
	for(int i=1;i<=n;i++){
		for(int s1=0;s1<2;s1++){
			for(int s2=0;s2<2;s2++){
				for(int s3=0;s3<2;s3++){
					for(int o=-1;o<=1;o++){
						int t1=max(0ll,s1+o),t2=(i&1)?max(0ll,s2+o):s2,t3=(i&1)?s3:max(0ll,s3+o);
						if(t1<2&&t2<2&&t3<2)dp[i][t1][t2][t3]=max(dp[i][t1][t2][t3],dp[i-1][s1][s2][s3]+o*a[i]);
					}
				}
			}
		}
	}
	int ans=0;
	for(int s1=0;s1<2;s1++){
		for(int s2=0;s2<2;s2++){
			for(int s3=0;s3<2;s3++)ans=max(ans,dp[n][s1][s2][s3]);
		}
	}
	printf("%lld\n",ans);
}

bool med;
int T;
signed main(){
	// freopen(".in","r",stdin);
	// freopen(".out","w",stdout);
	
	// cerr<<(&mbe-&med)/1024.0/1024.0<<"\n";
	
	T=read();
	while(T--)work();
}