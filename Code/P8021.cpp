#include<iostream>
#include<queue>
using namespace std;
const int maxn=5000;
const int inf=1e9;
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch-48);ch=getchar();}
	return x*f;
}

int n,s,t,ans;
int head[25010],tot=1;
struct nd{
	int nxt,to,w,c;
}e[150010];
void add(int u,int v,int w,int c){
	e[++tot]={head[u],v,w,-c};
	head[u]=tot;
	e[++tot]={head[v],u,0,c};
	head[v]=tot;
}
void build(int nd,int l,int r){
	if(l==r){
		add(s,nd,1,0);
		return ;
	}
	int mid=l+r>>1,ls=nd<<1,rs=nd<<1|1;
	build(ls,l,mid);build(rs,mid+1,r);
	add(ls,nd,mid-l+1,0);add(rs,nd,r-mid,0);
}
void updata(int nd,int l,int r,int ql,int qr,int u,int w){
	if(l>=ql&&r<=qr){
		add(nd,u,1,w);
		return ;
	}
	int mid=l+r>>1,ls=nd<<1,rs=nd<<1|1;
	if(ql<=mid)updata(ls,l,mid,ql,qr,u,w);
	if(qr>mid)updata(rs,mid+1,r,ql,qr,u,w);
}
queue<int> q;
int dis[25010],rad[25010];
bool vis[25010];
bool bfs(){
	for(int i=1;i<=maxn*5+2;i++)dis[i]=inf,vis[i]=false,rad[i]=head[i];
	q.push(s);dis[s]=0;vis[s]=true;
	while(!q.empty()){
		int u=q.front();q.pop();vis[u]=false;
		for(int i=head[u];i;i=e[i].nxt){
			int v=e[i].to;
			if(e[i].w&&dis[v]>dis[u]+e[i].c){
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
		if(e[i].w&&dis[v]==dis[u]+e[i].c&&!vis[v]){
			int out=dfs(v,min(e[i].w,res));
			res-=out;cnt+=out;
			e[i].w-=out;e[i^1].w+=out;
			ans+=out*e[i].c;
			if(!res)break;
		}
	}
	vis[u]=false;
	return cnt;
}

signed main(){
	n=read();s=maxn*5+1,t=maxn*5+2;
	build(1,1,maxn);
	for(int i=1;i<=n;i++){
		int u,v,w;
		u=read();v=read()-1;w=read();
		updata(1,1,maxn,u,v,maxn*4+i,w);
		add(maxn*4+i,t,1,0);
	}
	while(bfs())dfs(s,inf);
	printf("%d",-ans);
}
