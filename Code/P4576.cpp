#include<bits/stdc++.h>
#define int long long
#define db double
#define mod 1000000007
using namespace std;
const int maxn=200010;
const int inf=1e9;
const db eps=1e-9;
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch-48);ch=getchar();}
	return x*f;
}

int n,x,y,xx,yy;
int dp[2][65][22][22][22][22];
int f1[4][2]={{1,0},{0,1},{-1,0},{0,-1}};
int f2[8][2]={{1,0},{0,1},{-1,0},{0,-1},{2,0},{-2,0},{0,2},{0,-2}};
int dfs(int cur,int dep,int x,int y,int xx,int yy){
	int ans;
	if(dep>3*n)return dp[cur][dep][x][y][xx][yy]=inf;
	if(dp[cur][dep][x][y][xx][yy])return dp[cur][dep][x][y][xx][yy];
	if(x==xx&&y==yy){
		if(cur)return 0;
		return inf;
	}
	if(cur){
		ans=0;
		for(int i=0;i<4;i++){
			int nx=x+f1[i][0],ny=y+f1[i][1];
			if(nx<1||ny<1||nx>n||ny>n)continue;
			ans=max(ans,dfs(cur^1,dep+1,nx,ny,xx,yy));
		}
	}
	else{
		ans=inf;
		for(int i=0;i<8;i++){
			int nx=xx+f2[i][0],ny=yy+f2[i][1];
			if(nx<1||ny<1||nx>n||ny>n)continue;
			ans=min(ans,dfs(cur^1,dep+1,x,y,nx,ny));
		}
	}
	return dp[cur][dep][x][y][xx][yy]=++ans;
}

int T;
signed main(){
	//	freopen(".in","r",stdin);
	//	freopen(".out","w",stdout);
	
	n=read();x=read();y=read();xx=read();yy=read();
	if(abs(x-xx)+abs(y-yy)<=1)printf("WHITE 1");
	else printf("BLACK %lld",dfs(1,0,x,y,xx,yy));
}
