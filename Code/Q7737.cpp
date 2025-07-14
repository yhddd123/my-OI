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
const int maxn=250010;
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
int s,t,ss,flow,ans;
struct nd{
	int nxt,to,w,c;
}e[maxn<<3];
int head[maxn],tot=1;
void add(int u,int v,int w,int c){
	// cout<<u<<" "<<v<<" "<<w<<" "<<c<<"\n";
	e[++tot]={head[u],v,w,c};head[u]=tot;
	e[++tot]={head[v],u,0,-c};head[v]=tot;
}
queue<int> q;
int dis[maxn],rad[maxn];
bool vis[maxn];
bool bfs1(){
	for(int i=1;i<=t;i++)dis[i]=0,rad[i]=head[i];
	q.push(s);dis[s]=1;
	while(!q.empty()){
		int u=q.front();q.pop();
		for(int i=head[u];i;i=e[i].nxt){
			int v=e[i].to;
			if(e[i].w&&!e[i].c&&!dis[v]){
				dis[v]=dis[u]+1;
				q.push(v);
			}
		}
	}
	return dis[t];
}
int dfs1(int u,int res){
	if(u==t)return res;
	int cnt=0;
	for(int i=rad[u];i;i=e[i].nxt){
		int v=e[i].to;rad[u]=i;
		if(e[i].w&&!e[i].c&&dis[v]==dis[u]+1){
			int out=dfs1(v,min(e[i].w,res));
			res-=out;cnt+=out;
			e[i].w-=out;e[i^1].w+=out;
			if(!res)break;
		}
	}
	return cnt;
}
bool bfs(){
	for(int i=1;i<=t;i++)dis[i]=inf,vis[i]=0,rad[i]=head[i];
	q.push(ss);dis[ss]=0;vis[ss]=1;
	while(!q.empty()){
		int u=q.front();q.pop();vis[u]=0;
		for(int i=head[u];i;i=e[i].nxt){
			int v=e[i].to;
			if(e[i].w&&dis[v]>dis[u]+e[i].c){
				dis[v]=dis[u]+e[i].c;
				if(!vis[v])vis[v]=1,q.push(v);
			}
		}
	}
	return dis[t]!=inf;
}
int dfs(int u,int res){
	if(u==t)return res;
	int cnt=0;vis[u]=1;
	for(int i=rad[u];i;i=e[i].nxt){
		int v=e[i].to;rad[u]=i;
		if(e[i].w&&dis[v]==dis[u]+e[i].c&&!vis[v]){
			int out=dfs(v,min(e[i].w,res));
			res-=out;cnt+=out;
			e[i].w-=out;e[i^1].w+=out;
			ans+=out*e[i].c;
			if(!res)break;
		}
	}
	vis[u]=0;
	return cnt;
}
int id(int u,int v){return u*m+v;}
int a[510][510],b[510][510];
void work(){
	n=read();m=read();k=read();
	s=(n+1)*m+1,ss=(n+1)*m+2,t=(n+1)*m+3;
	for(int i=1;i<=t;i++)head[i]=0;tot=1;
	for(int i=1;i<=n;i++){
		for(int j=1;j<m;j++){
			a[i][j]=read();
			add(id(i-1,j),id(i,j),a[i][j],0);
			add(id(i,j),id(i-1,j),a[i][j],0);
			add(id(i-1,j),id(i,j),inf,1);
			add(id(i,j),id(i-1,j),inf,1);
		}
	}
	for(int i=1;i<n;i++){
		for(int j=1;j<=m;j++){
			b[i][j]=read();
			if(j==1||j==m)continue;
			add(id(i,j-1),id(i,j),b[i][j],0);
			add(id(i,j),id(i,j-1),b[i][j],0);
			add(id(i,j-1),id(i,j),inf,1);
			add(id(i,j),id(i,j-1),inf,1);
		}
	}
	for(int j=1;j<=m;j++)add(s,id(0,j),inf,0);
	for(int j=1;j<=m;j++)add(id(n,j),t,inf,0);
	flow=ans=0;
	while(bfs1())flow+=dfs1(s,inf);
	add(ss,s,k,0);
	while(bfs())flow+=dfs(ss,inf);
	printf("%lld\n",ans);
	int num=1;
	for(int i=1;i<=n;i++){
		for(int j=1;j<m;j++){
			a[i][j]+=e[num+6].w+e[num+8].w;
			num+=8;
		}
	}
	for(int i=1;i<n;i++){
		for(int j=1;j<=m;j++){
			if(j==1||j==m)continue;
			b[i][j]+=e[num+6].w+e[num+8].w;
			num+=8;
		}
	}
	for(int i=1;i<=n;i++){
		for(int j=1;j<m;j++)printf("%lld ",a[i][j]);puts("");
	}
	for(int i=1;i<n;i++){
		for(int j=1;j<=m;j++)printf("%lld ",b[i][j]);puts("");
	}
}

// \
444

bool Med;
int T;
signed main(){
//	freopen("charge.in","r",stdin);
//	freopen("charge.out","w",stdout);
	
//	ios::sync_with_stdio(0);
//	cin.tie(0);cout.tie(0);
	
//	cerr<<(&Mbe-&Med)/1048576.0<<" MB\n";
	
	T=read();
	while(T--)work();
}
