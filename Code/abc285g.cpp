// Problem: AT_abc285_g [ABC285G] Tatami
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/AT_abc285_g
// Memory Limit: 1 MB
// Time Limit: 3000 ms
// Written by yhm.
// Start codeing:2025-03-10 12:33:49
// 
// Powered by CP Editor (https://cpeditor.org)

#include<bits/stdc++.h>
#define int long long
#define mod 998244353ll
#define pii pair<int,int>
#define fi first
#define se second
#define pb push_back
#define mems(a,x) memset((a),(x),sizeof(a))
using namespace std;
inline int read(){
	int x=0,fl=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')fl=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
	return x*fl;
}
const int maxn=180010;
const int inf=2e9;
bool mbe;

int n,m;
int head[maxn],tot=1;
struct nd{
	int nxt,to,w;
}e[maxn*10];
void add(int u,int v,int w){
	e[++tot]={head[u],v,w};head[u]=tot;
	e[++tot]={head[v],u,0};head[v]=tot;
}
int s,t,flow,num;
int rad[maxn],dis[maxn];
queue<int> q;
bool bfs(){
	for(int i=1;i<=t;i++)rad[i]=head[i],dis[i]=0;
	dis[s]=1;q.push(s);
	while(!q.empty()){
		int u=q.front();q.pop();
		for(int i=head[u];i;i=e[i].nxt){
			int v=e[i].to;
			if(!dis[v]&&e[i].w)dis[v]=dis[u]+1,q.push(v);
		}
	}
	return dis[t];
}
int dfs(int u,int res){
	if(u==t)return res;
	int cnt=0;
	for(int i=rad[u];i;i=e[i].nxt){
		int v=e[i].to;rad[u]=i;
		if(dis[v]==dis[u]+1&&e[i].w){
			int out=dfs(v,min(e[i].w,res));
			e[i].w-=out;e[i^1].w+=out;
			cnt+=out;res-=out;
			if(!res)break;
		}
	}
	return cnt;
}
char ss[310][310];
int id(int u,int v){return (u-1)*m+v;}
int fx[4][2]={{1,0},{-1,0},{0,1},{0,-1}};
void work(){
	n=read();m=read();
	for(int i=1;i<=n;i++)scanf("%s",ss[i]+1);
	s=2*n*m+1,t=2*n*m+2;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			if(ss[i][j]=='2')add(s,id(i,j),1),++num;
			if(ss[i][j]!='1')add(id(i,j)+n*m,t,1);
			for(int k=0;k<4;k++){
				int u=i+fx[k][0],v=j+fx[k][1];
				if(u<=0||u>n||v<=0||v>m)continue;
				add(id(i,j),id(u,v)+n*m,1);
			}
		}
	}
	while(bfs())flow+=dfs(s,inf);
	if(num==flow)puts("Yes");
	else puts("No");
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