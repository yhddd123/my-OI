#include<bits/stdc++.h>
#define int long long
#define mod 998244353ll
#define pii pair<int,int>
#define fi first
#define se second
#define pb push_back
#define db long double
#define mems(a,x) memset((a),(x),sizeof(a))
using namespace std;
inline int read(){
	int x=0,fl=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')fl=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
	return x*fl;
}
const int maxn=200010;
const int inf=1e9;
bool mbe;

int n,m;
vector<char> a[maxn];
char S[maxn];
int getid(int u,int v){return (u-1)*m+v;}
int fx[4][2]={{1,0},{-1,0},{0,1},{0,-1}};
vector<int> e[maxn],g[maxn];int num;
int dfn[maxn],idx,lw[maxn];
int st[maxn<<1],tp;
void tar(int u){
	dfn[u]=lw[u]=++idx;st[++tp]=u;
	for(int v:e[u]){
		if(!dfn[v]){
			tar(v);
			lw[u]=min(lw[u],lw[v]);
			if(lw[v]>=dfn[u]){
				g[++num].push_back(st[tp]);
				while(st[tp--]!=v){
					g[num].push_back(st[tp]);
				}
				g[num].push_back(u);
			}
		}
		else lw[u]=min(lw[u],dfn[v]);
	}
}
bool bk[maxn];
int head[maxn<<1],tot=1;
int s,t,flow;
struct nd{
	int nxt,to,w;
}ee[maxn*10];
void add(int u,int v,int w){
	ee[++tot]={head[u],v,w};head[u]=tot;
	ee[++tot]={head[v],u,0};head[v]=tot;
}
int rad[maxn<<1],dis[maxn<<1];
queue<int> q;
bool bfs(){
	for(int i=1;i<=2*n*m;i++)rad[i]=head[i],dis[i]=0;
	dis[s]=1;q.push(s);
	while(!q.empty()){
		int u=q.front();q.pop();
		for(int i=head[u];i;i=ee[i].nxt){
			int v=ee[i].to;
			if(!dis[v]&&ee[i].w)dis[v]=dis[u]+1,q.push(v);
		}
	}
	return dis[t];
}
int dfs(int u,int res){
	if(u==t)return res;
	int cnt=0;
	for(int i=rad[u];i;i=ee[i].nxt){
		int v=ee[i].to;rad[u]=i;
		if(dis[v]==dis[u]+1&&ee[i].w){
			int out=dfs(v,min(ee[i].w,res));
			ee[i].w-=out;ee[i^1].w+=out;
			cnt+=out;res-=out;
			if(!res)break;
		}
	}
	return cnt;
}
bool vis[maxn<<1];
vector<int> id;
void dfs(int u){
	if(vis[u])return ;vis[u]=1;
	id.pb(u);
	if(u==t)return ;
	for(int i=head[u];i;i=ee[i].nxt){
		int v=ee[i].to;if(!((i^ee[i].w)&1))dfs(v);
		if(id.back()==t)return ;
	}
	id.pop_back();
}
void work(){
	n=read();m=read();
	for(int i=0;i<=n+1;i++){
		a[i].resize(m+2);
		if(i&&i<=n){
			scanf("%s",S+1);
			for(int j=1;j<=m;j++)a[i][j]=S[j];
		}
	}
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++)if(a[i][j]=='.'){
			for(int k=0;k<4;k++){
				int ii=i+fx[k][0],jj=j+fx[k][1];
				if(a[ii][jj]=='.')e[getid(i,j)].pb(getid(ii,jj));
			}
		}
	}
	tar(1);
	int p=0;for(int i=1;i<=num;i++){
		int t=0;for(int u:g[i])t+=(u==1)+(u==n*m);
		if(t==2){p=i;break;}
	}
	if(!p){puts("NO");return ;}
	puts("YES");
	// for(int u:g[p])cout<<u<<" ";
	for(int u:g[p])bk[u]=1;
	for(int u=1;u<=n*m;u++)if(bk[u]){
		add(u,u+n*m,1);
		for(int v:e[u])if(bk[v])add(u+n*m,v,1);
	}
	s=1+n*m,t=n*m;
	for(int i=1;i<=2;i++)if(bfs())flow+=dfs(s,1);
	dfs(s);
	// for(int u:id)cout<<u<<" ";cout<<"\n";
	for(int u:id)if(u<=n*m){
		int i=(u-1)/m+1,j=(u-1)%m+1;
		a[i][j]='V';
	}
	for(int i=1;i<=2*n*m;i++)vis[i]=0;
	for(int u:id)vis[u]=1;vis[s]=vis[t]=0;
	id.clear();
	dfs(s);
	for(int u:id)if(u<=n*m){
		int i=(u-1)/m+1,j=(u-1)%m+1;
		a[i][j]='K';
	}
	a[1][1]=a[n][m]='.';
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++)printf("%c",a[i][j]);puts("");
	}
}

bool med;
int T;
signed main(){
	// freopen(".in","r",stdin);
	// freopen(".out","w",stdout);
	
	// cerr<<(&mbe-&med)/1024.0/1024.0<<"\n";
	
	T=1;
	while(T--)work();
}