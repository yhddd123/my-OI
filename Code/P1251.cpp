#include<bits/stdc++.h>
#define int long long
using namespace std;
const int maxn=4010;
const int inf=1e18;

int n,s,t;
int a[maxn];
int p,m,f,mm,ff;
int ans,flow;

struct nd{
	int nxt,to,val,c;
}e[maxn*maxn<<1];
int head[maxn],tot=1;
void add(int u,int v,int w,int f){
	e[++tot].nxt=head[u];e[tot].to=v;e[tot].val=w;e[tot].c=f;
	head[u]=tot;
	e[++tot].nxt=head[v];e[tot].to=u;e[tot].val=0;e[tot].c=-f;
	head[v]=tot;
}

int rad[maxn],dis[maxn];
bool vis[maxn];
queue<int> q;
bool bfs(){
	for(int i=1;i<=t;i++)dis[i]=inf,rad[i]=head[i],vis[i]=false;
	dis[s]=0;q.push(s);vis[s]=true;
	while(!q.empty()){
		int u=q.front();q.pop();vis[u]=false;
		for(int i=head[u];i;i=e[i].nxt){
			int v=e[i].to;
			if(e[i].val&&dis[v]>dis[u]+e[i].c){
				dis[v]=dis[u]+e[i].c;
				if(!vis[v])vis[v]=true,q.push(v);
			}
		}
	}
	return dis[t]!=inf;
}
int dfs(int u,int res){
	if(u==t)return res;
	int cnt=0;vis[u]=true;
	for(int i=rad[u];i;i=e[i].nxt){
		int v=e[i].to;rad[u]=i;
		if(e[i].val&&dis[v]==dis[u]+e[i].c&&!vis[v]){
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
	cin>>n;s=2*n+1,t=2*n+2;
	for(int i=1;i<=n;i++)cin>>a[i];
	cin>>p>>m>>f>>mm>>ff;
	for(int i=1;i<=n;i++)add(i,t,a[i],0),add(s,i+n,a[i],0);
	for(int i=1;i<=n;i++)add(s,i,inf,p);
	for(int i=1;i<n;i++)add(i+n,i+n+1,inf,0);
	for(int i=1;i+m<=n;i++)add(i+n,i+m,inf,f);
	for(int i=1;i+mm<=n;i++)add(i+n,i+mm,inf,ff);
	
	while(bfs()){
		flow+=dfs(s,inf);
	}
	cout<<ans;
}
