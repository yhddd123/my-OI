// Problem: P7717 「EZEC-10」序列
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P7717
// Memory Limit: 512 MB
// Time Limit: 1000 ms
// Written by yhm.
// Start codeing:2024-07-16 19:11:20
// 
// Powered by CP Editor (https://cpeditor.org)

#include<bits/stdc++.h>
#define int long long
#define mod 1000000007ll
#define pii pair<int,int>
#define fi first
#define se second
#define mems(x,y) memset(x,y,sizeof(x))
using namespace std;
const int maxn=500010;
const int maxm=20000010;
const int inf=1e18;
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch-48);ch=getchar();}
	return x*f;
}
bool Mbe;

int n,m,k;
int head[maxn],tot;
struct nd{
	int nxt,to,w;
}e[maxn<<1];
void add(int u,int v,int w){e[++tot]={head[u],v,w};head[u]=tot;}
int f[maxn];
int fd(int x){
	if(x==f[x])return x;
	return f[x]=fd(f[x]);
}
int g[maxn][3];
int dis[maxn];bool vis[maxn];
int tree[maxm][2],idx;
void insert(int x){
	int nd=1;
	for(int i=29;~i;i--){
		int v=(x>>i)&1;
		if(!tree[nd][v])tree[nd][v]=++idx;
		nd=tree[nd][v];
	}
}
void dfs(int u,int fa){
	vis[u]=1;insert(dis[u]);
	for(int i=head[u];i;i=e[i].nxt){
		int v=e[i].to;if(v==fa)continue;
		if(vis[v]&&(dis[v]!=(dis[u]^e[i].w))){puts("0");exit(0);}
		if(vis[v])continue;
		dis[v]=dis[u]^e[i].w;dfs(v,u);
	}
}
int ans=1,res;
void calc(int nd,int dep){
	if(dep<0){++res;return ;}
	int v=(k>>dep)&1;
	// cout<<nd<<" "<<dep<<" "<<res<<"\n";
	if(v){
		if(tree[nd][0]&&tree[nd][1])calc(tree[nd][0],dep-1),calc(tree[nd][1],dep-1);
		else if(tree[nd][0]){
			res+=(1<<dep);
			calc(tree[nd][0],dep-1);
		}
		else if(tree[nd][1]){
			res+=(1<<dep);
			calc(tree[nd][1],dep-1);
		}
	}
	else{
		if(tree[nd][0]&&tree[nd][1])return ;
		else if(tree[nd][0]){
			calc(tree[nd][0],dep-1);
		}
		else if(tree[nd][1]){
			calc(tree[nd][1],dep-1);
		}
	}
}
void work(){
	n=read();m=read();k=read();
	for(int i=1;i<=m;i++){
		g[i][0]=read(),g[i][1]=read(),g[i][2]=read();
		add(g[i][0],g[i][1],g[i][2]),add(g[i][1],g[i][0],g[i][2]);
	}
	for(int i=1;i<=n;i++)if(!vis[i]){
		while(idx)tree[idx][0]=tree[idx][1]=0,idx--;idx=1;
		dfs(i,0);res=0;calc(1,29);
		ans=ans*res%mod;
	}
	printf("%lld\n",ans);
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