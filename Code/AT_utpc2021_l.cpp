// Problem: AT_utpc2021_l Maze Game
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/AT_utpc2021_l
// Memory Limit: 1 MB
// Time Limit: 2000 ms
// Written by yhm.
// Start codeing:2025-05-23 14:36:16
// 
// Powered by CP Editor (https://cpeditor.org)

#include<bits/stdc++.h>
#define int long long
#define mod 998244353ll
#define pii pair<int,int>
#define fi first
#define se second
#define pb push_back
#define mkp make_pair
#define mems(a,x) memset((a),(x),sizeof(a))
using namespace std;
inline int read(){
	int x=0,fl=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')fl=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
	return x*fl;
}
const int maxn=110;
const int inf=1e9;
bool mbe;

int n,m,s,t;
int id(int u,int v){return (u-1)*m+v;}
char c[maxn];
bool a[maxn][maxn];
int fx[4][2]={{0,1},{0,-1},{1,0},{-1,0}};
vector<int> e[maxn*maxn];
int dep[maxn*maxn],lw[maxn*maxn],fa[maxn*maxn];
vector<int> g[maxn*maxn];int scct;
void tar(int u){
	lw[u]=dep[u];
	for(int v:e[u]){
		if(!dep[v]){
			dep[v]=dep[u]+1,fa[v]=u;tar(v);
			lw[u]=min(lw[u],lw[v]);
		}
		else lw[u]=min(lw[u],dep[v]);
	}
}
bool vis[maxn*maxn];
void work(){
	n=read();m=read();
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++)a[i][j]=0,e[id(i,j)].clear();
	}
	for(int i=1;i<=n;i++){
		scanf("%s",c+1);
		for(int j=1;j<=m;j++){
			if(c[j]=='#')a[i][j]=1;
			if(c[j]=='S')s=id(i,j);
			if(c[j]=='G')t=id(i,j);
		}
	}
	for(int u=1;u<=n;u++){
		for(int v=1;v<=m;v++)if(!a[u][v]){
			for(int i=0;i<4;i++){
				int x=u+fx[i][0],y=v+fx[i][1];
				if(1<=x&&x<=n&&1<=y&&y<=m&&!a[x][y])e[id(u,v)].pb(id(x,y));
			}
		}
	}
	for(int i=1;i<=n*m;i++)dep[i]=0;
	fa[s]=0,dep[s]=1;tar(s);
	while(fa[fa[t]]){
		if(lw[t]>=dep[t]-1){puts("Alice");return ;}
		t=fa[t];
	}
	int num=0;for(int i=1;i<=n;i++)for(int j=1;j<=m;j++)num+=1-a[i][j];
	if(num&1)puts("Alice");
	else puts("Bob");
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