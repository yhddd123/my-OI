#include<bits/stdc++.h>
#define int long long
using namespace std;
const int maxn=210;
const int inf=1e18;
inline int read(){
	int x=0,f=1;
	char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){x=(x<<3)+(x<<1)+(c^48),c=getchar();}
	return x*f;
}

int n,m,s,t,k,T;
int flow,ans;
int tim[maxn][maxn],f[maxn][maxn];
struct ask{
	int a,b,ss,tt,c;
}p[maxn];

struct nd{
	int nxt,to,val,c;
}e[210010];
int head[maxn],tot=1;
void add(int u,int v,int w,int f){
	e[++tot].nxt=head[u];e[tot].to=v;e[tot].val=w;e[tot].c=f;
	head[u]=tot;
	e[++tot].nxt=head[v];e[tot].to=u;e[tot].val=0;e[tot].c=-f;
	head[v]=tot;
}

queue<int> q;
int dis[maxn],rad[maxn];
bool vis[maxn];

bool bfs(){
	for(int i=1;i<=t;i++)dis[i]=inf,vis[i]=false,rad[i]=head[i];
	q.push(s);dis[s]=0;vis[s]=true;
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
	n=read();m=read();k=read();T=read();s=2*m+1;t=2*m+3;
	for(int i=1;i<=n;i++)for(int j=1;j<=n;j++)tim[i][j]=read();
	for(int i=1;i<=n;i++)for(int j=1;j<=n;j++)f[i][j]=read();
	for(int i=1;i<=m;i++)cin>>p[i].a>>p[i].b>>p[i].ss>>p[i].tt>>p[i].c,++p[i].a,++p[i].b;
	for(int i=1;i<=m;i++){
		add(i,i+m,1,-p[i].c);
		if(p[i].tt+tim[p[i].b][1]<=T)add(i+m,t,inf,f[p[i].b][1]);
		else continue;
		if(p[i].ss>=tim[1][p[i].a])add(t-1,i,inf,f[1][p[i].a]);
		for(int j=1;j<=m;j++){
			if(p[j].ss>=p[i].tt+tim[p[i].b][p[j].a])add(i+m,j,inf,f[p[i].b][p[j].a]);
		}
	}
	add(s,t-1,k,0);
	while(bfs()){
		flow+=dfs(s,inf);
	}
	printf("%lld\n",-ans);
}

