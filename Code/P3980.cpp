#include<bits/stdc++.h>
#define int long long
using namespace std;
const int maxn=300010;
const int inf=1e18;
inline int read(){
	int x=0,f=1;
	char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){x=(x<<3)+(x<<1)+(c^48),c=getchar();}
	return x*f;
}

int n,m,s,t;
int ans,flow;
struct nd{
	int nxt,to,val,c;
}e[maxn];
int head[maxn],tot=1;
void ad(int u,int v,int w,int f){
	e[++tot].nxt=head[u];e[tot].to=v;e[tot].val=w;e[tot].c=f;
	head[u]=tot;
}
void add(int u,int v,int w,int f){
	ad(u,v,w,f);
	ad(v,u,0,-f);
}
int dis[maxn],rad[maxn];
bool vis[maxn];
queue<int> q;

bool bfs(){
	for(int i=1;i<=t;i++)dis[i]=inf,rad[i]=head[i],vis[i]=0;
	dis[s]=0;vis[s]=1;q.push(s);
	while(!q.empty()){
		int u=q.front();q.pop();vis[u]=0;
		for(int i=head[u];i;i=e[i].nxt){
			int v=e[i].to;
			if(dis[v]>dis[u]+e[i].c&&e[i].val){
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
		if(dis[v]==dis[u]+e[i].c&&e[i].val&&!vis[v]){
			int out=dfs(v,min(e[i].val,res));
			e[i].val-=out;e[i^1].val+=out;
			res-=out;cnt+=out;
			ans+=out*e[i].c;
			if(!res)break;
		}
	}
	vis[u]=0;
	return cnt;
}

signed main(){
	n=read();m=read();s=n+2;t=n+3;
	for(int i=1,u;i<=n;i++){
		u=read();
		add(i,i+1,inf-u,0);
	}
	for(int i=1,u,v,w;i<=m;i++){
		u=read();v=read();w=read();
		add(u,v+1,inf,w);
	}
	add(s,1,inf,0);add(n+1,t,inf,0);
	while(bfs()){
		flow+=dfs(s,inf);
	}
	printf("%lld\n",ans);
}

