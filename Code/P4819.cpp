#include<bits/stdc++.h>
#define int long long
#define mod 1000000007
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

int n,m;
int head[maxn],tot;
struct nd{
	int nxt,to;
}e[maxn<<1];
void add(int u,int v){
	e[++tot]={head[u],v};
	head[u]=tot;
}
int st[maxn],tp;
int dfn[maxn],lw[maxn],cnt;
bool vis[maxn];
int scc[maxn],scct,siz[maxn];
void tar(int u){
	dfn[u]=lw[u]=++cnt;
	vis[u]=1;st[++tp]=u;
	for(int i=head[u];i;i=e[i].nxt){
		int v=e[i].to;
		if(!dfn[v]){
			tar(v);
			lw[u]=min(lw[u],lw[v]);
		}
		else if(vis[v])lw[u]=min(lw[u],dfn[v]);
	}
	if(dfn[u]==lw[u]){
		++scct;
		scc[st[tp]]=scct;
		vis[st[tp]]=0;
		++siz[scct];
		while(st[tp--]!=u){
			scc[st[tp]]=scct;
			vis[st[tp]]=0;
			++siz[scct];
		}
	}
}
map<int,int> mp;
int d[maxn],fl,ans;
vector<int> g[maxn];

int T;
signed main(){
	//	freopen(".in","r",stdin);
	//	freopen(".out","w",stdout);
	
	n=read();m=read();ans=n;
	for(int i=1;i<=m;i++){
		int u,v;
		u=read();v=read();
		add(u,v);
	}
	for(int i=1;i<=n;i++)if(!dfn[i])tar(i);
	for(int u=1;u<=n;u++){
		for(int i=head[u];i;i=e[i].nxt){
			int v=e[i].to;
			if(scc[u]!=scc[v]&&!mp[scc[u]*maxn+scc[v]]){
				if(siz[scc[u]]==1)g[scc[u]].push_back(scc[v]);
				d[scc[v]]++;
				mp[scc[u]*maxn+scc[v]]=1;
			}
		}
	}
	for(int i=1;i<=scct;i++){
		if(!d[i]){
			if(siz[i]==1){
				int f=1;
				for(int v:g[i])if(d[v]==1)f=0;
				fl|=f;
			}
			ans--;
		}
	}
	if(fl)ans++;
	printf("%.6lf",(double)1.0*ans/n);
}
