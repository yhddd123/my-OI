#include<bits/stdc++.h>
#define int long long
#define mod 1000000007
using namespace std;
const int maxn=110;
const int maxm=10010;
const int inf=1e9;
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch-48);ch=getchar();}
	return x*f;
}

int n,m,s,t,idx;
int head[maxm*6],tot=1;
struct nd{
	int nxt,to,w;
}e[maxm*30];
void add(int u,int v,int w){
	e[++tot]={head[u],v,w};
	head[u]=tot;
	e[++tot]={head[v],u,0};
	head[v]=tot;
}
int id(int u,int v){return (u-1)*m+v;}
int flow,sum;
int rad[maxm*6],dis[maxm*6];
queue<int> q;
bool bfs(){
	memset(dis,0,sizeof(dis));
	q.push(s);dis[s]=1;
	while(!q.empty()){
		int u=q.front();q.pop();
		rad[u]=head[u];
		for(int i=head[u];i;i=e[i].nxt){
			int v=e[i].to;
			if(!dis[v]&&e[i].w){
				dis[v]=dis[u]+1;
				q.push(v);
			}
		}
	}
	return dis[t];
}
int dfs(int u,int res){
	if(u==t)return res;
	int cnt=0;
	for(int i=rad[u];i;i=e[i].nxt){
		int v=e[i].to;rad[u]=i;
		if(dis[v]==dis[u]+1&&e[i].w){
			int out=dfs(v,min(res,e[i].w));
			res-=out;cnt+=out;
			e[i].w-=out;e[i^1].w+=out;
			if(!res)break;
		}
	}
	return cnt;
}

signed main(){
	//	freopen(".in","r",stdin);
	//	freopen(".out","w",stdout);
	
	n=read();m=read();
	idx=n*m;s=6*n*m+1,t=6*n*m+2;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			int x=read();sum+=x;
			add(s,id(i,j),x);
		}
	}
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			int x=read();sum+=x;
			add(id(i,j),t,x);
		}
	}
	for(int i=1;i<=n-1;i++){
		for(int j=1;j<=m;j++){
			int x=read();sum+=x;
			add(s,++idx,x);
			add(idx,id(i,j),inf);
			add(idx,id(i+1,j),inf);
		}
	}
	for(int i=1;i<=n-1;i++){
		for(int j=1;j<=m;j++){
			int x=read();sum+=x;
			add(++idx,t,x);
			add(id(i,j),idx,inf);
			add(id(i+1,j),idx,inf);
		}
	}
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m-1;j++){
			int x=read();sum+=x;
			add(s,++idx,x);
			add(idx,id(i,j),inf);
			add(idx,id(i,j+1),inf);
		}
	}
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m-1;j++){
			int x=read();sum+=x;
			add(++idx,t,x);
			add(id(i,j),idx,inf);
			add(id(i,j+1),idx,inf);
		}
	}
	while(bfs())flow+=dfs(s,inf);
	printf("%lld\n",sum-flow);
}
