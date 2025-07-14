#include<bits/stdc++.h>
#define int long long
#define mod 1000000007
using namespace std;
const int maxn=55;
const int maxm=200010;
const int inf=1e18;
inline int read(){
	int x=0,f=1;
	char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){x=(x<<3)+(x<<1)+(c^48),c=getchar();}
	return x*f;
}

int n,k,s,t;
int ans,flow;
int a[maxn][maxn];
int fx[4][2]={{1,0},{0,1}};
int node(int u,int v){
	return (u-1)*n+v;
}
int calc(int u,int v){
	return n*n+node(u,v);
}
bool in(int u,int v){
	return (u>=1&&u<=n&&v>=1&&v<=n);
}

struct nd{
	int nxt,to,val,c;
	int from;
}e[maxm];
int head[maxm],tot=1;
void add(int u,int v,int w,int f){
	e[++tot].nxt=head[u];e[tot].to=v;e[tot].val=w;e[tot].c=f;
	head[u]=tot;e[tot].from=u;
	e[++tot].nxt=head[v];e[tot].to=u;e[tot].val=0;e[tot].c=-f;
	head[v]=tot;e[tot].from=v;
}

queue<int> q;
int dis[maxm],rad[maxm];
bool vis[maxm];
bool bfs(){
	for(int i=1;i<=t;i++)dis[i]=inf,rad[i]=head[i],vis[i]=false;
	dis[s]=0;vis[s]=true;q.push(s);
	while(!q.empty()){
		int u=q.front();q.pop();
		for(int i=head[u];i;i=e[i].nxt){
			int v=e[i].to;
			if(dis[v]>dis[u]+e[i].c&&e[i].val){
				dis[v]=dis[u]+e[i].c;
				if(!vis[v])vis[v]=true,q.push(v);
			}
		}
		vis[u]=false;
	}
	return dis[t]!=inf;
}
int dfs(int u,int res){
	if(u==t)return res;
	int cnt=0;vis[u]=true;
	for(int i=rad[u];i;i=e[i].nxt){
		int v=e[i].to;rad[u]=i;
		if(dis[v]==dis[u]+e[i].c&&e[i].val&&!vis[v]){
			int out=dfs(v,min(e[i].val,res));
			res-=out;cnt+=out;
			e[i].val-=out;e[i^1].val+=out;
			ans+=out*e[i].c;
			if(!res)break;
		}
	}
	vis[u]=false;
	return cnt;
}

signed main(){
	n=read();k=read();s=n*n*2+1;t=n*n*9+2;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++)cin>>a[i][j];
	}
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			add(node(i,j),calc(i,j),1,-a[i][j]);
			add(node(i,j),calc(i,j),inf,0);
			for(int k=0;k<2;k++){
				int nx,ny;
				nx=i+fx[k][0];ny=j+fx[k][1];
				if(in(nx,ny)){
					add(calc(i,j),node(nx,ny),inf,0);
				}
			}
		}
	}
	add(s,node(1,1),k,0);add(calc(n,n),t,k,0);
	while(bfs()){
		flow+=dfs(s,inf);
		//		cout<<flow<<" "<<ans<<"\n";
	}
	printf("%lld\n",-ans);
}

/*
  3 1
  1 2 3
  0 2 1
  1 4 2
  
  11
 */
