// Problem: P6077 [BalticOI2007] Escape
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P6077
// Memory Limit: 125 MB
// Time Limit: 1000 ms
// Written by yhm.
// Start codeing:2024-09-25 14:36:53
// 
// Powered by CP Editor (https://cpeditor.org)

#include<bits/stdc++.h>
#define int long long
#define mod 998244353ll
#define pii pair<int,int>
#define fi first
#define se second
#define mems(x,y) memset(x,y,sizeof(x))
#define pb push_back
#define db double
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

int n,m,k;
pii a[maxn];
int s,t,flow;
int head[maxn],tot=1;
struct nd{
	int nxt,to,w;
}e[maxn<<1];
void add(int u,int v,int w){
	// cout<<u<<" "<<v<<"\n";
	e[++tot]={head[u],v,w};head[u]=tot;
	e[++tot]={head[v],u,0};head[v]=tot;
}
int dis[maxn],rad[maxn];
queue<int> q;
bool bfs(){
	for(int i=1;i<=t;i++)dis[i]=0,rad[i]=head[i];
	dis[s]=1,q.push(s);
	while(!q.empty()){
		int u=q.front();q.pop();
		for(int i=head[u];i;i=e[i].nxt){
			int v=e[i].to;
			if(e[i].w&&!dis[v])dis[v]=dis[u]+1,q.push(v);
		}
	}
	return dis[t];
}
int dfs(int u,int res){
	if(u==t)return res;
	int cnt=0;
	for(int i=rad[u];i;i=e[i].nxt){
		int v=e[i].to;rad[u]=i;
		if(e[i].w&&dis[v]==dis[u]+1){
			int out=dfs(v,min(e[i].w,res));
			e[i].w-=out,e[i^1].w+=out;
			res-=out,cnt+=out;
			if(!res)break;
		}
	}
	return cnt;
}
int chk(int u,int v,int x,int y){return (u-x)*(u-x)+(v-y)*(v-y);}
void work(){
	n=read();m=read();k=read();s=2*k+1,t=2*k+2;
	for(int i=1;i<=k;i++)a[i]={read(),read()};
	for(int i=1;i<=k;i++){
		if(a[i].se<=100)add(s,i,inf);
		add(i,i+k,1);
		for(int j=1;j<=k;j++)if(i!=j&&chk(a[i].fi,a[i].se,a[j].fi,a[j].se)<=40000)add(i+k,j,inf);
		if(m-a[i].se<=100)add(i+k,t,inf);
	}
	while(bfs())flow+=dfs(s,inf);
	printf("%lld\n",flow);
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
