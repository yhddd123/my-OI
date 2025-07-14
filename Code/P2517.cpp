#include<bits/stdc++.h>
#define int long long
#define mod 1000000007
using namespace std;
const int maxn=10010;
const int inf=1e18;
inline int read(){
	int x=0,f=1;
	char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){x=(x<<3)+(x<<1)+(c^48),c=getchar();}
	return x*f;
}

int n,m,k,s,t;
int ans,flow;
int a[maxn],p[maxn];

struct nd{
	int nxt,to,val,c;
	int from;
}e[maxn];
int head[maxn],tot=1;
void add(int u,int v,int w,int f){
	e[++tot].nxt=head[u];e[tot].to=v;e[tot].val=w;e[tot].c=f;
	head[u]=tot;e[tot].from=u;
	e[++tot].nxt=head[v];e[tot].to=u;e[tot].val=0;e[tot].c=-f;
	head[v]=tot;e[tot].from=v;
}

queue<int> q;
int dis[maxn],rad[maxn];
bool vis[maxn];
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
	n=read();m=read();k=read();
	s=n+1;t=n+2;
	for(int i=1;i<=n;i++)cin>>a[i];
	for(int i=1;i<=n;i++)cin>>p[i];
	for(int i=1;i<=n;i++)add(s,i,inf,p[i]),add(i,t,a[i],0);
	for(int i=1;i<n;i++)add(i,i+1,k,m);
	while(bfs()){
		flow+=dfs(s,inf);
	}
	printf("%lld\n",ans);
}
