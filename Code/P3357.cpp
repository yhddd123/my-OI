// Problem: P3357 最长k可重线段集问题
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P3357
// Memory Limit: 125 MB
// Time Limit: 1000 ms
// Written by yhm.
// Start codeing:2024-07-21 09:31:52
// 
// Powered by CP Editor (https://cpeditor.org)

#include<bits/stdc++.h>
#define int long long
#define mod 998244353ll
#define pii pair<int,int>
#define fi first
#define se second
#define mems(x,y) memset(x,y,sizeof(x))
using namespace std;
const int maxn=200010;
const int inf=1e18;
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch-48);ch=getchar();}
	return x*f;
}
bool Mbe;

int n,k;
pii a[maxn];int val[maxn];
int b[maxn],len;
int head[maxn],tot=1;
struct nd{
	int nxt,to,w,c;
}e[maxn];
void add(int u,int v,int w,int c){
	e[++tot]={head[u],v,w,-c};head[u]=tot;
	e[++tot]={head[v],u,0,c};head[v]=tot;
}
int s,t,ans,flow;
int dis[maxn],rad[maxn];
bool vis[maxn];
queue<int> q;
bool bfs(){
	for(int i=1;i<=t;i++)dis[i]=inf,vis[i]=0,rad[i]=head[i];
	dis[s]=0,vis[s]=1,q.push(s);
	while(!q.empty()){
		int u=q.front();q.pop();vis[u]=0;
		for(int i=head[u];i;i=e[i].nxt){
			int v=e[i].to;
			if(e[i].w&&dis[v]>dis[u]+e[i].c){
				dis[v]=dis[u]+e[i].c;
				if(!vis[v]){
					vis[v]=1,q.push(v);
				}
			}
		}
	}
	return dis[t]<inf;
}
int dfs(int u,int res){
	if(u==t)return res;
	int cnt=0;vis[u]=1;
	for(int i=rad[u];i;i=e[i].nxt){
		int v=e[i].to;rad[u]=i;
		if(e[i].w&&dis[v]==dis[u]+e[i].c&&!vis[v]){
			int out=dfs(v,min(e[i].w,res));
			e[i].w-=out,e[i^1].w+=out;
			res-=out,cnt+=out;
			ans+=out*e[i].c;
			if(!res)break;
		}
	}
	vis[u]=0;
	return cnt;
}
void work(){
	n=read();k=read();
	for(int i=1;i<=n;i++){
		int x=read(),y=read(),xx=read(),yy=read();
		val[i]=sqrt((x-xx)*(x-xx)+(y-yy)*(y-yy));
		x<<=1,xx<<=1;
		if(x==xx)xx++;
		else x++;
		a[i]={x,xx};
	}
	for(int i=1;i<=n;i++)b[++len]=a[i].fi,b[++len]=a[i].se;
	sort(b+1,b+len+1);len=unique(b+1,b+len+1)-b-1;
	for(int i=1;i<=n;i++){
		a[i].fi=lower_bound(b+1,b+len+1,a[i].fi)-b;
		a[i].se=lower_bound(b+1,b+len+1,a[i].se)-b;
	}
	s=len+1,t=len+2;
	for(int i=1;i<len;i++)add(i,i+1,inf,0);
	add(s,1,k,0),add(len,t,k,0);
	for(int i=1;i<=n;i++)add(a[i].fi,a[i].se,1,val[i]);
	while(bfs())flow+=dfs(s,inf);
	printf("%lld\n",-ans);
}

// \
444

bool Med;
int T;
signed main(){
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
	
//	ios::sync_with_stdio(0);
//	cin.tie(0);cout.tie(0);
	
//	cerr<<(&Mbe-&Med)/1048576.0<<" MB\n";
	
	T=1;
	while(T--)work();
}
