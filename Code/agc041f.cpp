// Problem: AT_agc041_f [AGC041F] Histogram Rooks
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/AT_agc041_f
// Memory Limit: 1024 MB
// Time Limit: 4000 ms
// Written by yhm.
// Start codeing:2025-10-12 11:52:49
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
const int maxn=410;
const int inf=1e9;
bool mbe;

int n,a[maxn];
int st[10][maxn];
int mmax(int u,int v){return a[u]<a[v]?u:v;}
int que(int l,int r){
	int k=__lg(r-l+1);
	return mmax(st[k][l],st[k][r-(1<<k)+1]);
}
int dp[maxn][maxn][2],f[maxn][2],siz[maxn];
int pw[maxn*maxn],val[maxn][maxn];
int build(int l,int r,int lst=0){
	if(l>r)return 0;
	int u=que(l,r);
	int ls=build(l,u-1,a[u]),rs=build(u+1,r,a[u]);
	siz[u]=1;dp[u][0][1]=dp[u][1][0]=1,dp[u][1][1]=mod-1;
	auto upd=[&](int v){
		if(!v)return ;
		for(int i=0;i<=siz[u];i++){
			for(int j=0;j<=siz[v];j++){
				for(int fl1:{0,1}){
					for(int fl2:{0,1}){
						(f[i+j][fl1&fl2]+=dp[u][i][fl1]*dp[v][j][fl2])%=mod;
					}
				}
			}
		}
		siz[u]+=siz[v];
		for(int i=0;i<=siz[u];i++)dp[u][i][0]=f[i][0],dp[u][i][1]=f[i][1],f[i][0]=f[i][1]=0;
	};
	upd(ls),upd(rs);
	for(int i=0;i<=siz[u];i++){
		dp[u][i][0]=dp[u][i][0]*val[siz[u]-i][a[u]-lst]%mod;
		dp[u][i][1]=dp[u][i][1]*pw[(siz[u]-i)*(a[u]-lst)]%mod;
	}
	// cout<<u<<" "<<siz[u]<<"\n";
	// for(int i=0;i<=siz[u];i++)cout<<dp[u][i][0]<<" "<<dp[u][i][1]<<"\n";
	return u;
}
void work(){
	n=read();
	for(int i=1;i<=n;i++)a[i]=read();
	for(int i=1;i<=n;i++)st[0][i]=i;
	for(int j=1;j<10;j++){
		for(int i=1;i+(1<<j)-1<=n;i++)st[j][i]=mmax(st[j-1][i],st[j-1][i+(1<<j-1)]);
	}
	pw[0]=1;for(int i=1;i<=n*n;i++)pw[i]=pw[i-1]*2%mod;
	for(int i=0;i<=n;i++){
		val[i][0]=1;for(int j=1;j<=n;j++)val[i][j]=val[i][j-1]*(pw[i]-1)%mod;
	}
	int rt=build(1,n);
	int ans=0;for(int i=0;i<=n;i++)(ans+=dp[rt][i][0]+dp[rt][i][1])%=mod;
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