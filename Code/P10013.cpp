// Problem: P10013 [集训队互测 2023] Tree Topological Order Counting
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P10013
// Memory Limit: 512 MB
// Time Limit: 1000 ms
// Written by yhm.
// Start codeing:2025-05-30 10:29:01
// 
// Powered by CP Editor (https://cpeditor.org)

#include<bits/stdc++.h>
// #define int long long
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
const int maxn=5010;
const int inf=1e9;
bool mbe;

int n;
int head[maxn],tot;
struct nd{
	int nxt,to;
}e[maxn];
void add(int u,int v){e[++tot]={head[u],v};head[u]=tot;}
inline int ksm(int a,int b=mod-2){
	int ans=1;
	while(b){
		if(b&1)ans=1ll*ans*a%mod;
		a=1ll*a*a%mod;
		b>>=1;
	}
	return ans;
}
int fac[maxn],inv[maxn];
int C(int m,int n){return 1ll*fac[m]*inv[n]%mod*inv[m-n]%mod;}
int f[maxn],siz[maxn];
void dfs(int u,int fa){
	siz[u]=1;f[u]=1;
	for(int i=head[u];i;i=e[i].nxt){
		int v=e[i].to;if(v==fa)continue;
		dfs(v,u);
		f[u]=1ll*f[u]*C(siz[u]+siz[v]-1,siz[v])%mod*f[v]%mod;siz[u]+=siz[v];
	}
}
int dp[maxn][maxn];
void dfs1(int u,int fa){
	for(int i=head[u];i;i=e[i].nxt){
		int v=e[i].to;if(v==fa)continue;
		int val=1ll*f[u]*ksm(1ll*f[v]*C(siz[u]-1,siz[v])%mod)%mod;
		for(int k=1;k<=siz[v];k++){
			for(int j=k+1;j<=siz[u]+k-siz[v];j++){
				(dp[v][k]+=1ll*dp[u][j]*C(j-2,k-1)%mod*C(siz[u]-j,siz[v]-k)%mod*val%mod)%=mod;
			}
		}
		dfs1(v,u);
	}
}
void work(){
	n=read();
	for(int i=2;i<=n;i++)add(read(),i);
	for(int i=1;i<=n;i++)dp[1][i]=read();
	fac[0]=1;for(int i=1;i<=n;i++)fac[i]=1ll*fac[i-1]*i%mod;
	inv[n]=ksm(fac[n]);for(int i=n-1;~i;i--)inv[i]=1ll*inv[i+1]*(i+1)%mod;
	dfs(1,0);
	dfs1(1,0);
	for(int u=1;u<=n;u++)printf("%d ",1ll*dp[u][1]*f[u]%mod);
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