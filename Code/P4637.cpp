#include<bits/stdc++.h>
using namespace std;
const int maxn=4010;
const int inf=1e9;
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch-48);ch=getchar();}
	return x*f;
}

int n;
int x[maxn],d[maxn];
int head[maxn],tot;
struct nd{
	int nxt,to;
}e[maxn*maxn];
void add(int u,int v){
	e[++tot]={head[u],v};
	head[u]=tot;
}
int dfn[maxn],lw[maxn],idx;
int scc[maxn],scct;
int st[maxn],tp;
bool vis[maxn];
int siz[maxn];
bitset<maxn> f[maxn];
void tar(int u){
	dfn[u]=lw[u]=++idx;
	st[++tp]=u;vis[u]=1;
	for(int i=head[u];i;i=e[i].nxt){
		int v=e[i].to;
		if(!dfn[v]){
			tar(v);
			lw[u]=min(lw[u],lw[v]);
		}
		else if(vis[v])lw[u]=min(lw[u],dfn[v]);
	}
	if(dfn[u]==lw[u]){
		scc[st[tp]]=++scct;
		siz[scct]=1;
		vis[st[tp]]=0;
		f[scct].set(st[tp]);
		while(st[tp--]!=u){
			scc[st[tp]]=scct;
			siz[scct]++;
			vis[st[tp]]=0;
			f[scct].set(st[tp]);
		}
	}
}
bool bk[maxn][maxn];
vector<int> g[maxn];
int in[maxn];
queue<int> q;
double ans;

int T;
signed main(){
	//	freopen(".in","r",stdin);
	//	freopen(".out","w",stdout);
	
	n=read();
	for(int i=1;i<=n;i++)x[i]=read(),d[i]=read();
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			if(i==j)continue;
			if(abs(x[i]-x[j])<=d[i])add(i,j);
		}
	}
	for(int i=1;i<=n;i++)if(!dfn[i])tar(i);
	for(int u=1;u<=n;u++){
		for(int i=head[u];i;i=e[i].nxt){
			int v=e[i].to;
			if(scc[u]!=scc[v]&&!bk[scc[u]][scc[v]]){
				g[scc[u]].push_back(scc[v]);
				in[scc[v]]++;
				bk[scc[u]][scc[v]]=1;
			}
		}
	}
	for(int i=1;i<=scct;i++)if(!in[i])q.push(i);
	while(!q.empty()){
		int u=q.front();q.pop();
		for(int v:g[u]){
			in[v]--;
			f[v]|=f[u];
			if(!in[v])q.push(v);
		}
	}
	for(int i=1;i<=n;i++)ans+=(double)1.0/f[scc[i]].count();
	printf("%.4lf\n",ans);
}
