// Problem: P4516 [JSOI2018] 潜入行动
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P4516
// Memory Limit: 250 MB
// Time Limit: 1000 ms
// Written by yhm.
// Start codeing:2026-01-26 08:58:23
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
const int maxn=100010;
const int maxm=110;
const int inf=1e9;
bool mbe;

int n,k;
vector<int> e[maxn];
int f[maxn][maxm][2][2],siz[maxn],tmp[maxm][2][2];
inline void inc(int &u,int v){((u+=v)>=mod)&&(u-=mod);}
void dfs(int u,int fa){
	siz[u]=1;
	f[u][0][0][0]=1;
	f[u][1][1][0]=1;
	for(int v:e[u])if(v!=fa){
		dfs(v,u);
		for(int i=0;i<=min(siz[u],k);i++){
			for(int j=0;j<=min(siz[v],k-i);j++){
				inc(tmp[i+j][0][0],1ll*f[u][i][0][0]*f[v][j][0][1]%mod);
				inc(tmp[i+j][0][1],1ll*f[u][i][0][0]*f[v][j][1][1]%mod);
				inc(tmp[i+j][0][1],1ll*f[u][i][0][1]*f[v][j][0][1]%mod);
				inc(tmp[i+j][0][1],1ll*f[u][i][0][1]*f[v][j][1][1]%mod);
				inc(tmp[i+j][1][0],1ll*f[u][i][1][0]*f[v][j][0][0]%mod);
				inc(tmp[i+j][1][0],1ll*f[u][i][1][0]*f[v][j][0][1]%mod);
				inc(tmp[i+j][1][1],1ll*f[u][i][1][1]*f[v][j][0][0]%mod);
				inc(tmp[i+j][1][1],1ll*f[u][i][1][1]*f[v][j][0][1]%mod);
				inc(tmp[i+j][1][1],1ll*f[u][i][1][1]*f[v][j][1][0]%mod);
				inc(tmp[i+j][1][1],1ll*f[u][i][1][1]*f[v][j][1][1]%mod);
				inc(tmp[i+j][1][1],1ll*f[u][i][1][0]*f[v][j][1][0]%mod);
				inc(tmp[i+j][1][1],1ll*f[u][i][1][0]*f[v][j][1][1]%mod);
			}
		}
		siz[u]+=siz[v];
		for(int i=0;i<=min(siz[u],k);i++){
			f[u][i][0][0]=tmp[i][0][0],tmp[i][0][0]=0;
			f[u][i][0][1]=tmp[i][0][1],tmp[i][0][1]=0;
			f[u][i][1][0]=tmp[i][1][0],tmp[i][1][0]=0;
			f[u][i][1][1]=tmp[i][1][1],tmp[i][1][1]=0;
		}
	}
}
void work(){
	n=read();k=read();
	for(int i=1;i<n;i++){
		int u=read(),v=read();
		e[u].pb(v),e[v].pb(u);
	}
	dfs(1,0);
	printf("%lld\n",(f[1][k][0][1]+f[1][k][1][1])%mod);
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