// Problem: P8436 【模板】边双连通分量
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P8436
// Memory Limit: 512 MB
// Time Limit: 2000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

#include<bits/stdc++.h>
#define int long long
#define mod 998244353
#define pii pair<int,int>
#define mems(x,y) memset(x,y,sizeof x)
using namespace std;
const int maxn=2000010;
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
int head[maxn],tot=1;
struct nd{
	int nxt,to;
}e[maxn<<1];
void add(int u,int v){e[++tot]={head[u],v};head[u]=tot;}
int dfn[maxn],lw[maxn],idx;
int st[maxn],tp;
vector<int> g[maxn];
int num;
bool vis[maxn];
void tar(int u,int fl){
	dfn[u]=lw[u]=++idx;st[++tp]=u;
	for(int i=head[u];i;i=e[i].nxt){
		int v=e[i].to;
		if(i==(fl^1))continue;
		if(!dfn[v]){
			tar(v,i);
			lw[u]=min(lw[u],lw[v]);
		}
		else lw[u]=min(lw[u],dfn[v]);
	}
	if(lw[u]==dfn[u]){
		++num;
		g[num].push_back(st[tp]);
		while(st[tp--]!=u){
			g[num].push_back(st[tp]);
		}
	}
}
void work(){
	n=read();m=read();
	for(int i=1;i<=m;i++){
		int u=read(),v=read();
		add(u,v),add(v,u);
	}
	for(int i=1;i<=n;i++)if(!dfn[i])tar(i,0);
	printf("%lld\n",num);
	for(int i=1;i<=num;i++){
		printf("%lld ",g[i].size());
		for(int j:g[i])printf("%lld ",j);
		printf("\n");
	}
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
