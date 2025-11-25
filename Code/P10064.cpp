// Problem: P10064 [SNOI2024] 公交线路
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P10064
// Memory Limit: 1024 MB
// Time Limit: 1500 ms
// Written by yhm.
// Start codeing:2025-11-24 21:24:29
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
const int inf=1e9;
bool mbe;

int n,ans;
int C[maxn][maxn],pw[maxn*maxn],pw1[maxn][maxn];
vector<int> e[maxn];
int f[maxn],g[maxn];
int siz[maxn],num[maxn],cnt;
void dfs(int u,int fa){
	siz[u]=1,num[u]=e[u].size()==1;
	if(e[u].size()==1)return ;
	for(int v:e[u])if(v!=fa)dfs(v,u);
	f[0]=1;
	for(int v:e[u])if(v!=fa){
		for(int i=0;i<=num[u];i++){
			for(int j=0;j<=num[v];j++){
				(g[i+j]+=f[i]*C[num[v]][j]%mod*pw[(siz[u]-i)*(siz[v]-j)+siz[v]*(siz[v]-1)/2])%=mod;
			}
		}
		siz[u]+=siz[v],num[u]+=num[v];
		for(int i=0;i<=num[u];i++)f[i]=g[i],g[i]=0;
	}
	for(int i=0;i<=num[u];i++){
		(ans+=((i&1)?mod-1:1)*f[i]%mod*
		pw[(siz[u]-i)*(n-siz[u]-cnt+num[u])+(n-siz[u])*(n-siz[u]-1)/2]%mod*pw1[siz[u]-i][cnt-num[u]])%=mod;
		// cout<<u<<" "<<i<<" "<<ans<<"\n";
	}
	// cout<<u<<"\n";
	// for(int i=0;i<=num[u];i++)cout<<f[i]<<" ";cout<<"\n";
	for(int i=0;i<=num[u];i++)f[i]=0;
	if(!fa)return ;
	for(int i=0;i<=num[u];i++){
		(ans+=(((i+1)&1)?mod-1:1)*C[num[u]][i]%mod
		*pw[(siz[u]-i)*(n-siz[u]-cnt+num[u])+siz[u]*(siz[u]-1)/2+(n-siz[u])*(n-siz[u]-1)/2]%mod
		*pw1[siz[u]-i][cnt-num[u]])%=mod;
	}
}
void work(){
	n=read();
	if(n==1||n==2){puts("1");return ;}
	for(int i=1;i<n;i++){
		int u=read(),v=read();
		e[u].pb(v),e[v].pb(u);
	}
	for(int i=0;i<=n;i++){
		C[i][0]=1;for(int j=1;j<=i;j++)C[i][j]=(C[i-1][j]+C[i-1][j-1])%mod;
	}
	pw[0]=1;for(int i=1;i<=n*n;i++)pw[i]=pw[i-1]*2%mod;
	for(int i=0;i<=n;i++){
		pw1[i][0]=1;for(int j=1;j<=n;j++)pw1[i][j]=pw1[i][j-1]*(pw[i]-1)%mod;
	}
	int rt=0;for(int i=1;i<=n;i++){
		if(e[i].size()>1)rt=i;
		else ++cnt;
	}
	dfs(rt,0);
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