#include<bits/stdc++.h>
#define int long long
#define mod 998244353ll
#define pii pair<int,int>
#define fi first
#define se second
#define mems(x,y) memset(x,y,sizeof(x))
#define pb push_back
using namespace std;
const int maxn=5010;
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
char c[55][55];
struct nd{
	int nxt,to,w;
}e[maxn*40];
int head[maxn],tot=1,s,t;
void add(int u,int v,int w){
	// cout<<u<<" "<<v<<" "<<w<<"\n";
	e[++tot]={head[u],v,w};head[u]=tot;
	e[++tot]={head[v],u,0};head[v]=tot;
}
int rad[maxn],dis[maxn];
queue<int> q;
bool bfs(){
	for(int i=1;i<=t;i++)rad[i]=head[i],dis[i]=0;
	dis[s]=1;q.push(s);
	while(!q.empty()){
		int u=q.front();q.pop();
		for(int i=head[u];i;i=e[i].nxt){
			int v=e[i].to;
			if(!dis[v]&&e[i].w)dis[v]=dis[u]+1,q.push(v);
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
			int out=dfs(v,min(e[i].w,res));
			e[i].w-=out;e[i^1].w+=out;
			cnt+=out;res-=out;
			if(!res)break;
		}
	}
	return cnt;
}
int id(int u,int v,int fl){return (u-1)*m+v+fl*n*m;}
void work(){
	n=read();m=read();s=n*m*2+1,t=n*m*2+2;
	for(int i=1;i<=n;i++)scanf("%s",c[i]+1);
	for(int i=1;i<=m;i++)if(c[1][i]=='#')add(id(1,i,1),t,inf);
	for(int i=1;i<=m;i++)if(c[n][i]=='#')add(s,id(n,i,0),inf);
	for(int i=1;i<=n;i++)if(c[i][1]=='#')add(s,id(i,1,0),inf);
	for(int i=1;i<=n;i++)if(c[i][m]=='#')add(id(i,m,1),t,inf);
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++)if(c[i][j]=='#'){
			add(id(i,j,0),id(i,j,1),1);
			for(int nx=i-2;nx<=i+2;nx++){
				for(int ny=j-2;ny<=j+2;ny++)if(!(nx==i&&ny==j)){
					if(nx<=0||nx>n||ny<=0||ny>m||c[nx][ny]=='.')continue;
					add(id(i,j,1),id(nx,ny,0),inf);
				}
			}
		}
	}
	int flow=0;while(bfs())flow+=dfs(s,inf);
	printf("%lld\n",flow);
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
