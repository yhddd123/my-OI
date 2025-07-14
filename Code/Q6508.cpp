#include<bits/stdc++.h>
#define int long long
#define mod 998244353ll
#define pii pair<int,int>
#define fi first
#define se second
#define mems(x,y) memset(x,y,sizeof(x))
using namespace std;
const int maxn=200010;
const int inf=1e9;
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch-48);ch=getchar();}
	return x*f;
}
bool Mbe;

int x,y,m;
int s,t,flow;
struct nd{
	int nxt,to,w;
}e[maxn<<3];
int head[maxn],tot=1;
void add(int u,int v,int w){
	e[++tot]={head[u],v,w};head[u]=tot;
	e[++tot]={head[v],u,0};head[v]=tot;
}
nd g[maxn<<3];
int tmp[maxn],len;
queue<int> q;
int dis[maxn],rad[maxn];
bool bfs(){
	for(int i=1;i<=t;i++)dis[i]=0,rad[i]=head[i];
	q.push(s);dis[s]=1;
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
			res-=out;cnt+=out;
			e[i].w-=out;e[i^1].w+=out;
			if(!res)break;
		}
	}
	return cnt;
}
int cnt2,cnt3;
void work(){
	x=read();y=read();m=read();
	s=x+y+1,t=x+y+2;
	for(int i=1;i<=x;i++)add(s,i,1);
	for(int i=x+1;i<=x+y;i++)add(i,t,1);
	for(int i=1;i<=m;i++){
		int u=read(),v=read();
		add(u,x+v,1);
	}
	while(bfs())cnt2+=dfs(s,inf);
	memcpy(g,e,sizeof(e));memcpy(tmp,head,sizeof(head));len=tot;
	for(int i=1;i<=x;i++)add(s,i,1);
	while(bfs())cnt3+=dfs(s,inf);
	memcpy(e,g,sizeof(g));memcpy(head,tmp,sizeof(tmp));tot=len;
	for(int i=x+1;i<=x+y;i++)add(i,t,1);
	while(bfs())cnt3+=dfs(s,inf);
	printf("%lld %lld\n",x+y-cnt2*2-cnt3,cnt3);
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
