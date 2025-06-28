// Problem: AT_agc031_e [AGC031E] Snuke the Phantom Thief
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/AT_agc031_e
// Memory Limit: 1 MB
// Time Limit: 5000 ms
// Written by yhm.
// Start codeing:2025-03-31 12:46:14
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
const int maxn=325;
const int inf=1e15;
bool mbe;

int n,q,res;
int x[maxn],y[maxn],w[maxn];
int mnx[maxn],mxx[maxn],mny[maxn],mxy[maxn];
int head[maxn],tot=1;
struct node{
	int nxt,to,w,c;
}e[maxn*maxn<<1];
void add(int u,int v,int w,int c){
	e[++tot]={head[u],v,w,c};head[u]=tot;
	e[++tot]={head[v],u,0,-c};head[v]=tot;
}
int flow,ans,s,t;
int dis[maxn],rad[maxn];
bool vis[maxn];
bool bfs(){
	queue<int> q;
	for(int i=1;i<=t;i++)rad[i]=head[i],dis[i]=inf,vis[i]=0;
	dis[s]=0;q.push(s),vis[s]=1;
	while(!q.empty()){
		int u=q.front();q.pop();vis[u]=0;
		for(int i=head[u];i;i=e[i].nxt){
			int v=e[i].to;
			if(e[i].w&&dis[v]>dis[u]+e[i].c){
				dis[v]=dis[u]+e[i].c;
				if(!vis[v])q.push(v),vis[v]=1;
			}
		}
	}
	return dis[t]!=inf;
}
int dfs(int u,int res){
	if(u==t)return res;
	vis[u]=1;
	int val=0;
	for(int i=rad[u];i;i=e[i].nxt){
		int v=e[i].to;rad[u]=i;
		if(e[i].w&&dis[v]==dis[u]+e[i].c&&!vis[v]){
			int out=dfs(v,min(e[i].w,res));
			res-=out,val+=out;
			e[i].w-=out,e[i^1].w+=out;
			ans+=out*e[i].c;
			if(!res)break;
		}
	}
	vis[u]=0;
	return val;
}
void work(){
	n=read();
	for(int i=1;i<=n;i++)x[i]=read(),y[i]=read(),w[i]=read();
	for(int i=1;i<=n;i++)mnx[i]=mny[i]=100;
	q=read();
	while(q--){
		char op[3];scanf("%s",op);int u=read(),v=read();
		if(op[0]=='L')mxx[v+1]=max(mxx[v+1],u+1);
		if(op[0]=='R')mnx[v+1]=min(mnx[v+1],u-1);
		if(op[0]=='D')mxy[v+1]=max(mxy[v+1],u+1);
		if(op[0]=='U')mny[v+1]=min(mny[v+1],u-1);
	}
	for(int i=2;i<=n;i++)mxx[i]=max(mxx[i],mxx[i-1]);
	for(int i=2;i<=n;i++)mnx[i]=min(mnx[i],mnx[i-1]);
	for(int i=2;i<=n;i++)mxy[i]=max(mxy[i],mxy[i-1]);
	for(int i=2;i<=n;i++)mny[i]=min(mny[i],mny[i-1]);
	s=4*n+1,t=4*n+2;
	for(int k=1;k<=n;k++){
		for(int i=1;i<=t;i++)head[i]=0;tot=1;
		for(int i=1;i<=n;i++)add(i,n+i,1,-w[i]);
		for(int i=1;i<=k;i++)add(s,2*n+i,1,0),add(3*n+i,t,1,0);
		for(int i=1;i<=n;i++){
			for(int j=1;j<=k;j++){
				if(mxx[j]<=x[i]&&mnx[k-j+1]>=x[i])add(2*n+j,i,1,0);
				if(mxy[j]<=y[i]&&mny[k-j+1]>=y[i])add(n+i,3*n+j,1,0);
			}
		}
		ans=flow=0;
		while(bfs())flow+=dfs(s,inf);
		res=max(res,-ans);
		// cout<<k<<" "<<ans<<" "<<flow<<"\n";
	}
	printf("%lld\n",res);
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