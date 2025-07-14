// Problem: #6033. 「雅礼集训 2017 Day2」棋盘游戏
// Contest: LibreOJ
// URL: https://loj.ac/p/6033
// Memory Limit: 256 MB
// Time Limit: 1000 ms
// Written by yhm.
// Start codeing:2024-07-18 17:01:46
// 
// Powered by CP Editor (https://cpeditor.org)

#include<bits/stdc++.h>
#define int long long
#define mod 998244353ll
#define pii pair<int,int>
#define fi first
#define se second
#define mems(x,y) memset(x,y,sizeof(x))
using namespace std;
const int maxn=110;
const int maxm=10010;
const int inf=1e18;
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch-48);ch=getchar();}
	return x*f;
}
bool Mbe;

int n,m;
char c[maxn];
int a[maxn][maxn];
int id(int u,int v){return (u-1)*m+v;}
int head[maxm],tot=1;
struct nd{
	int nxt,to,w;
}e[maxm<<5];
void add(int u,int v,int w){
	// cout<<u<<" "<<v<<" "<<w<<"\n";
	e[++tot]={head[u],v,w};head[u]=tot;
	e[++tot]={head[v],u,0};head[v]=tot;
}
int s,t;
int rad[maxm],dis[maxm];
queue<int> q;
bool bfs(){
	for(int i=1;i<=t;i++)rad[i]=head[i],dis[i]=0;
	dis[s]=1;q.push(s);
	while(!q.empty()){
		int u=q.front();q.pop();
		for(int i=head[u];i;i=e[i].nxt){
			int v=e[i].to;
			if(e[i].w&&!dis[v]){
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
		if(e[i].w&&dis[v]==dis[u]+1){
			int out=dfs(v,min(res,e[i].w));
			e[i].w-=out,e[i^1].w+=out;
			res-=out,cnt+=out;
			if(!res)break;
		}
	}
	return cnt;
}
int to[maxn][maxn][2];
bool vis[maxn][maxn];
vector<pii> ans;
void dfs1(int u,int v){
	if(vis[u][v])return ;vis[u][v]=1;
	ans.push_back({u,v});
	if(to[u-1][v][0])dfs1(to[u-1][v][0],to[u-1][v][1]);
	if(to[u+1][v][0])dfs1(to[u+1][v][0],to[u+1][v][1]);
	if(to[u][v-1][0])dfs1(to[u][v-1][0],to[u][v-1][1]);
	if(to[u][v+1][0])dfs1(to[u][v+1][0],to[u][v+1][1]);
}
void work(){
	n=read();m=read();
	for(int i=1;i<=n;i++){
		scanf("%s",c+1);
		for(int j=1;j<=m;j++)a[i][j]=(c[j]=='.');
	}
	s=n*m+1,t=n*m+2;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++)if(a[i][j]&&!((i+j)&1)){
			add(s,id(i,j),1);
			if(a[i+1][j])add(id(i,j),id(i+1,j),1);
			if(a[i-1][j])add(id(i,j),id(i-1,j),1);
			if(a[i][j+1])add(id(i,j),id(i,j+1),1);
			if(a[i][j-1])add(id(i,j),id(i,j-1),1);
		}
	}
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++)if(a[i][j]&&((i+j)&1))add(id(i,j),t,1);
	}
	int flow=0;while(bfs())flow+=dfs(s,inf);
	// cout<<flow<<"\n";
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++)if(a[i][j]&&!((i+j)&1)){
			for(int ii=head[id(i,j)];ii;ii=e[ii].nxt){
				int v=e[ii].to;
				if(v>n*m||e[ii].w)continue;
				int nx=(v-1)/m+1,ny=v-(nx-1)*m;
				to[i][j][0]=nx,to[i][j][1]=ny,to[nx][ny][0]=i,to[nx][ny][1]=j;
				// cout<<i<<" "<<j<<" "<<nx<<" "<<ny<<"\n";
			}
		}
	}
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++)if(a[i][j]&&!to[i][j][0])dfs1(i,j);
	}
	sort(ans.begin(),ans.end());
	printf("%lld\n",(int)ans.size());
	for(pii p:ans)printf("%lld %lld\n",p.fi,p.se);
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
