// Problem: P9351 [JOI 2023 Final] Maze
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P9351
// Memory Limit: 2 MB
// Time Limit: 2000 ms
// Written by yhm.
// Start codeing:2024-07-26 14:52:11
// 
// Powered by CP Editor (https://cpeditor.org)

#include<bits/stdc++.h>
#define mod 998244353ll
#define pii pair<int,int>
#define fi first
#define se second
#define mems(x,y) memset(x,y,sizeof(x))
using namespace std;
const int maxn=6000010;
const int inf=1e9;
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch-48);ch=getchar();}
	return x*f;
}
bool Mbe;

int n,m,d;
int sx,sy,ex,ey;
char s[maxn];
vector<vector<int>> a,dis;
int fx[4][2]={{1,0},{-1,0},{0,1},{0,-1}};
vector<vector<int>> f;
int fd(int id,int x){
	if(x==f[id][x])return x;
	return f[id][x]=fd(id,f[id][x]);
}
pii q[maxn];int h=1,t=0;
pii st[maxn];int tp;
int ans;
void work(){
	n=read(),m=read(),d=read();
	a.resize(n+1),dis.resize(n+1);
	for(int i=1;i<=n;i++){
		a[i].resize(m+1),dis[i].resize(m+1);
		for(int j=1;j<=m;j++)dis[i][j]=inf;
	}
	f.resize(n+m+1);
	for(int i=1;i<=n;i++){
		f[i].resize(m+2);f[i][m+1]=m+1;
		for(int j=1;j<=m;j++)f[i][j]=j;
	}
	for(int i=n+1;i<=n+m;i++){
		f[i].resize(n+2);f[i][n+1]=n+1;
		for(int j=1;j<=n;j++)f[i][j]=j;
	}
	sx=read(),sy=read(),ex=read(),ey=read();
	for(int i=1;i<=n;i++){
		scanf("%s",s+1);
		for(int j=1;j<=m;j++)a[i][j]=(s[j]=='.');
	}
	dis[sx][sy]=0,q[++t]={sx,sy};
	int cnt=0;ans=inf;
	while(h<=t){
		tp=0;
		while(h<=t){
			int u=q[h].fi,v=q[h].se;h++;
			if(abs(u-ex)<=d+1&&abs(v-ey)<=d+1&&abs(u-ex)+abs(v-ey)<=2*d)ans=min(ans,dis[u][v]+1);
			f[u][v]=fd(u,v+1);f[v+n][u]=fd(v+n,u+1);
			// cerr<<u<<" "<<v<<" "<<dis[u][v]<<"\n";
			if(1){	
				int i=max(1,u-d);
				int l=max(1,(i==u-d||i==u+d)?v-d+1:v-d);
				int r=min(m,(i==u-d||i==u+d)?v+d-1:v+d);
				for(int j=fd(i,l);j<=r;j=fd(i,j)){
					if(dis[i][j]>dis[u][v]+1){
						dis[i][j]=dis[u][v]+1;
						st[++tp]={i,j};
					}
					f[i][j]=fd(i,j+1);f[j+n][i]=fd(j+n,i+1);
				}
			}
			if(1){	
				int i=min(n,u+d);
				int l=max(1,(i==u-d||i==u+d)?v-d+1:v-d);
				int r=min(m,(i==u-d||i==u+d)?v+d-1:v+d);
				for(int j=fd(i,l);j<=r;j=fd(i,j)){
					if(dis[i][j]>dis[u][v]+1){
						dis[i][j]=dis[u][v]+1;
						st[++tp]={i,j};
					}
					f[i][j]=fd(i,j+1);f[j+n][i]=fd(j+n,i+1);
				}
			}
			if(1){	
				int i=max(1,v-d);
				int l=max(1,(i==v-d||i==v+d)?u-d+1:u-d);
				int r=min(n,(i==v-d||i==v+d)?u+d-1:u+d);
				for(int j=fd(i+n,l);j<=r;j=fd(i+n,j)){
					if(dis[j][i]>dis[u][v]+1){
						dis[j][i]=dis[u][v]+1;
						st[++tp]={j,i};
					}
					f[i+n][j]=fd(i+n,j+1);f[j][i]=fd(j,i+1);
				}
			}
			if(1){	
				int i=min(m,v+d);
				int l=max(1,(i==v-d||i==v+d)?u-d+1:u-d);
				int r=min(n,(i==v-d||i==v+d)?u+d-1:u+d);
				for(int j=fd(i+n,l);j<=r;j=fd(i+n,j)){
					if(dis[j][i]>dis[u][v]+1){
						dis[j][i]=dis[u][v]+1;
						st[++tp]={j,i};
					}
					f[i+n][j]=fd(i+n,j+1);f[j][i]=fd(j,i+1);
				}
			}
			for(int i=0;i<4;i++){
				int nx=u+fx[i][0],ny=v+fx[i][1];
				if(nx<=0||nx>n||ny<=0||ny>m)continue;
				if(!a[nx][ny])continue;
				if(dis[nx][ny]>dis[u][v]){
					dis[nx][ny]=dis[u][v],q[++t]={nx,ny};
				}
			}
		}
		h=1,t=0;
		// cerr<<cnt<<" "<<dis[ex][ey]<<"\n";
		cnt++;
		if(dis[ex][ey]!=inf||ans==cnt)break;
		for(int i=1;i<=tp;i++){
			pii p=st[i];
			if(dis[p.fi][p.se]!=cnt)continue;
			q[++t]=p;
		}
	}
	printf("%d\n",min(ans,dis[ex][ey]));
}

// \
444

bool Med;
int T;
signed main(){
	// freopen("stamp.in","r",stdin);
	// freopen("stamp.out","w",stdout);
	
//	ios::sync_with_stdio(0);
//	cin.tie(0);cout.tie(0);
	
	// cerr<<(&Mbe-&Med)/1048576.0<<" MB\n";
	
	T=1;
	while(T--)work();
}
