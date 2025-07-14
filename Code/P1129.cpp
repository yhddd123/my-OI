#include<bits/stdc++.h>
#define int long long
#define db double
#define mod 1000000007
using namespace std;
const int maxn=210;
const int inf=1e9;
const db eps=1e-9;
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch-48);ch=getchar();}
	return x*f;
}

int n;
int head[maxn<<1],tot=1;
struct nd{
	int nxt,to,val;
}e[maxn*maxn<<1];
void add(int u,int v,int w){
	e[++tot]={head[u],v,w};head[u]=tot;
	e[++tot]={head[v],u,0};head[v]=tot;
}
int s,t,flow;
queue<int> q;
int dis[maxn<<1],rad[maxn<<1];
bool bfs(){
	memset(dis,0,sizeof(dis));
	dis[s]=1;q.push(s);
	while(!q.empty()){
		int u=q.front();q.pop();
		rad[u]=head[u];
		for(int i=head[u];i;i=e[i].nxt){
			int v=e[i].to;
			if(e[i].val&&!dis[v]){
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
		if(e[i].val&&dis[v]==dis[u]+1){
			int out=dfs(v,min(res,e[i].val));
			e[i].val-=out;e[i^1].val+=out;
			res-=out;cnt+=out;
			if(!res)break;
		}
	}
	return cnt;
}
void solve(){
	memset(head,0,sizeof(head));tot=1;
	n=read();s=2*n+1,t=2*n+2;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++)if(read()==1)add(i,j+n,1);
	}
	for(int i=1;i<=n;i++)add(s,i,1);
	for(int i=1;i<=n;i++)add(i+n,t,1);
	flow=0;
	while(bfs())flow+=dfs(s,inf);
	if(flow==n)printf("Yes\n");
	else printf("No\n");
}

int T;
signed main(){
	//	freopen(".in","r",stdin);
	//	freopen(".out","w",stdout);
	
	T=read();
	while(T--)solve();
}
