// Problem: CF1322D Reality Show
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/CF1322D
// Memory Limit: 500 MB
// Time Limit: 2000 ms
// Written by yhm.
// Start codeing:2025-10-31 15:32:27
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
const int maxn=2010;
const int inf=1e9;
bool mbe;

int n,m,a[maxn],b[maxn],c[maxn<<1];
int dp[maxn<<1][maxn];
void work(){
	n=read();m=read();
	for(int i=1;i<=n;i++)a[i]=read();
	for(int i=1;i<=n;i++)b[i]=read();
	for(int i=1;i<=n+m;i++)c[i]=read();
	memset(dp,-0x3f,sizeof(dp));
	for(int i=0;i<=n+m;i++)dp[i][0]=0;
	for(int i=n;i;i--){
		for(int j=n-i+1;j;j--)dp[a[i]][j]=max(dp[a[i]][j],dp[a[i]][j-1]+c[a[i]]-b[i]);
		for(int j=a[i],s=n-i+1;j<n+m;j++,s/=2){
			for(int k=0;k<=s;k++)dp[j+1][k/2]=max(dp[j+1][k/2],dp[j][k]+c[j+1]*(k/2));
		}
	}
	printf("%lld\n",dp[n+m][0]);
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