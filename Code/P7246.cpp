// Problem: P7246 手势密码
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P7246
// Memory Limit: 500 MB
// Time Limit: 1000 ms
// Written by yhm.
// Start codeing:2026-01-30 19:41:48
// 
// Powered by CP Editor (https://cpeditor.org)

#include<bits/stdc++.h>
#define int long long
// #define mod 998244353ll
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
const int maxn=3000010;
const int inf=1e9;
bool mbe;

static const int mod=1e9;
namespace Generate{
	int n,seed;
	int Rand(int x){
		seed=(1ll*seed*0x66CCF+19260817ll)%x+1;
		seed=(1ll*seed*0x77CCF+20060428ll)%x+1;
		seed=(1ll*seed*0x88CCF+12345678ll)%x+1;
		seed=(1ll*seed*0x33CCCCFF+10086001ll)%x+1;
		return seed;
	}
};
int op,n,a[maxn];
int head[maxn],tot;
struct nd{
	int nxt,to;
}e[maxn<<1];
void add(int u,int v){e[++tot]={head[u],v};head[u]=tot;}
int f[maxn][2],g[maxn][3][2],h[3][2];
inline void chkmx(int &u,int v){(u<v)&&(u=v);}
void dfs(int u,int fa){
	g[u][0][0]=g[u][0][1]=g[u][1][0]=g[u][1][1]=g[u][2][0]=g[u][2][1]=-inf;
	g[u][0][0]=-a[u];
	g[u][1][0]=0;
	g[u][2][1]=a[u];
	for(int i=head[u];i;i=e[i].nxt){
		int v=e[i].to;if(v==fa)continue;
		dfs(v,u);
		h[0][0]=h[0][1]=h[1][0]=h[1][1]=h[2][0]=h[2][1]=-inf;
		chkmx(h[0][0],g[u][0][0]+f[v][0]);
		chkmx(h[0][0],g[u][0][0]+f[v][1]);
		chkmx(h[0][1],g[u][0][1]+f[v][0]);
		chkmx(h[0][1],g[u][0][1]+f[v][1]);
		
		chkmx(h[1][0],g[u][1][0]+f[v][0]);
		chkmx(h[1][1],g[u][1][0]+f[v][1]);
		chkmx(h[1][1],g[u][1][1]+f[v][0]);
		
		chkmx(h[2][1],g[u][2][1]+f[v][0]);
		
		g[u][0][0]=h[0][0],g[u][0][1]=h[0][1],g[u][1][0]=h[1][0],g[u][1][1]=h[1][1],g[u][2][1]=h[2][1];
	}
	f[u][0]=f[u][1]=-inf;
	chkmx(f[u][0],g[u][0][0]);
	chkmx(f[u][0],g[u][1][0]);
	chkmx(f[u][0],g[u][2][0]);
	chkmx(f[u][1],g[u][0][1]);
	chkmx(f[u][1],g[u][1][1]);
	chkmx(f[u][1],g[u][2][1]);
}
void work(){
	op=read();
	if(op==1){
		n=read();
		for(int i=1;i<=n;i++)a[i]=read();
		for(int i=1;i<n;i++){
			int u=read(),v=read();
			add(u,v),add(v,u);
		}
	}
	else{
		Generate::seed=read(),Generate::n=n=read();
		for(int i=1;i<=n;i++)a[i]=Generate::Rand(mod); 
		for(int i=2;i<=n;i++){
			int fa=Generate::Rand(i-1);
			add(fa,i);
		}
	}
	dfs(1,0);
	printf("%lld\n",max(f[1][0],f[1][1]));
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