// Problem: AT_wtf22_day1_c Shrink the Tree
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/AT_wtf22_day1_c
// Memory Limit: 1024 MB
// Time Limit: 5000 ms
// Written by yhm.
// Start codeing:2026-02-25 15:16:06
// 
// Powered by CP Editor (https://cpeditor.org)

#include<bits/stdc++.h>
// #define int long long
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
const int maxn=155;
const int inf=1e9;
bool mbe;

inline void inc(int &u,int v){((u+=v)>=mod)&&(u-=mod);}
int n,ans;
vector<int> e[maxn];
int col[maxn],fa[maxn];
void dfsc(int u){
	col[u]=col[fa[u]]^1;
	for(int v:e[u])if(v!=fa[u])fa[v]=u,dfsc(v);
}
int siz[maxn][2],num[maxn];
int val[maxn],c[maxn][2];
void dfs(int u,int fa){
	siz[u][0]=siz[u][1]=0;
	for(int v:e[u])if(v!=fa){
		dfs(v,u);siz[u][0]+=siz[v][0],siz[u][1]+=siz[v][1];
	}
	num[u]=abs(siz[u][0]-siz[u][1])+2*(e[u].size()>1&&siz[u][col[u]]>=siz[u][col[u]^1]);
	for(int v:e[u])if(v!=fa){
		num[u]=max(num[u],siz[v][0]+siz[v][1]+num[v]-siz[u][0]-siz[u][1]);
	}
	num[u]++;
	siz[u][col[u]]++;
}
int f[maxn][maxn][maxn][4],g[maxn][maxn][4];
void dfs(int u,int fa,int all){
	f[u][0][0][0]=1;
	siz[u][0]=siz[u][1]=0;
	for(int v:e[u])if(v!=fa){
		dfs(v,u,all);
		for(int i0=0;i0<=siz[u][0];i0++){
			for(int j0=0;j0<=siz[u][1]&&i0+j0<=all;j0++){
				for(int c0=0;c0<4;c0++)if(f[u][i0][j0][c0]){
					for(int i1=0;i1<=siz[v][0];i1++){
						for(int j1=0;j1<=siz[v][1];j1++){
							for(int c1=0;c1<4;c1++)if(f[v][i1][j1][c1]){
								if(i0+j0+i1+j1<=all)inc(g[i0+i1][j0+j1][c0|c1],1ll*f[u][i0][j0][c0]*f[v][i1][j1][c1]%mod);
							}
						}
					}
					if(i0+j0+siz[v][0]+siz[v][1]<=all&&num[v]<=all-siz[v][0]-siz[v][1]){
						inc(g[i0+siz[v][0]][j0+siz[v][1]][c0|(1<<col[v])],f[u][i0][j0][c0]);
					}
				}
			}
		}
		siz[u][0]+=siz[v][0],siz[u][1]+=siz[v][1];
		for(int i=0;i<=siz[u][0];i++){
			for(int j=0;j<=siz[u][1];j++){
				for(int c=0;c<4;c++)f[u][i][j][c]=g[i][j][c],g[i][j][c]=0;
			}
		}
	}
	siz[u][col[u]]++;
}
bool in(int v,int l,int r){return l<=v&&v<=r;}
void work(){
	n=read();
	for(int i=1;i<n;i++){
		int u=read(),v=read();
		e[u].pb(v),e[v].pb(u);
	}
	dfsc(1);
	for(int i=2;i<=n;i++){
		dfs(i,0);
		val[i]=num[fa[i]],c[i][0]=siz[fa[i]][0],c[i][1]=siz[fa[i]][1];
	}
	dfs(1,0);
	ans=(siz[1][0]==siz[1][1])+1;
	// for(int i=1;i<=n;i++)cout<<num[i]<<" ";cout<<"\n";
	for(int s=2;s<n;s+=2){
		dfs(1,0,s);
		for(int u=1;u<=n;u++){
			int i=s/2-c[u][0],j=s/2-c[u][1];
			// cout<<s<<" "<<u<<" "<<i<<" "<<j<<"\n";
			if(val[u]<=s-c[u][0]-c[u][1]&&in(i,0,siz[u][0])&&in(j,0,siz[u][1])){
				inc(ans,f[u][i][j][3]);
				if(fa[u])inc(ans,f[u][i][j][3-(1<<col[fa[u]])]);
			}
		}
	}
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