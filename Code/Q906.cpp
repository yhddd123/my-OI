#include<bits/stdc++.h>
// #define int long long
#define mod 998244353ll
#define pii pair<int,int>
#define fi first
#define se second
#define mems(x,y) memset(x,y,sizeof(x))
#define pb push_back
#define db double
using namespace std;
const int maxn=500010;
const int inf=1e19;
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch-48);ch=getchar();}
	return x*f;
}
bool Mbe;

int n,m;
int head[maxn],tot;
struct nd{
	int nxt,to;
}e[maxn];
void add(int u,int v){e[++tot]={head[u],v};head[u]=tot;}
int dfn[maxn],lw[maxn],idx;
int scc[maxn],scct;
int st[maxn],tp;
vector<int> id[maxn];
void tar(int u){
	st[++tp]=u,dfn[u]=lw[u]=++idx;
	for(int i=head[u];i;i=e[i].nxt){
		int v=e[i].to;
		if(!dfn[v]){
			tar(v);
			lw[u]=min(lw[u],lw[v]);
		}
		else if(!scc[v])lw[u]=min(lw[u],dfn[v]);
	}
	if(dfn[u]==lw[u]){
		scc[st[tp]]=++scct;id[scct].pb(st[tp]);
		while(st[tp--]!=u)scc[st[tp]]=scct,id[scct].pb(st[tp]);
	}
}
vector<int> g[maxn];
int d[maxn];
void work(){
	n=read();m=read();
	for(int i=1;i<=m;i++){
		int u=read()+1,v=read()+1;
		add(u,v);
	}
	for(int i=1;i<=n;i++)if(!dfn[i])tar(i);
	printf("%d\n",scct);
	for(int u=1;u<=n;u++){
		for(int i=head[u];i;i=e[i].nxt){
			int v=e[i].to;
			if(scc[u]!=scc[v])g[scc[u]].pb(scc[v]),d[scc[v]]++;
		}
	}
	queue<int> q;
	for(int i=1;i<=scct;i++)if(!d[i])q.push(i);
	while(!q.empty()){
		int u=q.front();q.pop();
		sort(id[u].begin(),id[u].end(),greater<int>());
		printf("%d ",id[u].size());
		for(int j:id[u])printf("%d ",j-1);puts("");
		for(int v:g[u]){
			d[v]--;
			if(!d[v])q.push(v);
		}
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