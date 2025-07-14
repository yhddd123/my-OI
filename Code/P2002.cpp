#include<bits/stdc++.h>
#define int long long
#define mod 1000000007
using namespace std;
const int maxn=1000010;
const int inf=1e9;
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+ch-48;ch=getchar();}
	return x*f;
}

int n,m,ans;
int head[maxn],tot;
struct nd{
	int nxt,from,to;
}e[maxn*5];
void add(int u,int v){
	e[++tot].nxt=head[u];e[tot].from=u;e[tot].to=v;
	head[u]=tot;
}

int st[maxn],tp;
int dfn[maxn],lw[maxn],cnt;
bool vis[maxn];
int in[maxn];
int scc[maxn],scct;
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
		while(st[tp--]!=u){
			scc[st[tp]]=scct;
			vis[st[tp]]=0;
		}
	}
}

int T;
signed main(){
//	freopen("P2002_2.in","r",stdin);
//	freopen(".out","w",stdout);

	n=read();m=read();
	for(int i=1;i<=m;i++){
		int u,v;
		u=read();v=read();
		add(u,v);
	}
	for(int i=1;i<=n;i++)if(!dfn[i])tar(i);
//	for(int i=1;i<=n;i++)cout<<scc[i]<<" ";
//	cout<<scct<<"\n";
	for(int i=1;i<=m;i++){
		if(scc[e[i].from]!=scc[e[i].to])in[scc[e[i].to]]=1;
	}
	for(int i=1;i<=scct;i++)if(!in[i])++ans;
	printf("%lld\n",ans);
}

