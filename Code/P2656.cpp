#include<bits/stdc++.h>
#define int long long
#define mod 1000000007
using namespace std;
const int maxn=200010;
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch-48);ch=getchar();}
	return x*f;
}

int n,m,s;
int head[maxn],tot;
struct nd{
	int nxt,to,w,w1;
}e[maxn];
void add(int u,int v,int w,int w1){
	e[++tot]={head[u],v,w,w1};
	head[u]=tot;
}
bool vis[maxn];
int dfn[maxn],idx,lw[maxn];
int st[maxn],tp;
int scct,scc[maxn];
void tar(int u){
	st[++tp]=u;dfn[u]=lw[u]=++idx;vis[u]=1;
	for(int i=head[u];i;i=e[i].nxt){
		int v=e[i].to;
		if(!dfn[v]){
			tar(v);
			lw[u]=min(lw[u],lw[v]);
		}
		else if(vis[v])lw[u]=min(lw[u],dfn[v]);
	}
	if(lw[u]==dfn[u]){
		scc[st[tp]]=++scct;
		vis[st[tp]]=0;
		while(st[tp--]!=u){
			scc[st[tp]]=scct;
			vis[st[tp]]=0;
		}
	}
}
int val[maxn];
int head1[maxn],tot1;
struct nd1{
	int nxt,to,w;
}e1[maxn];
void add1(int u,int v,int w){
	e1[++tot1]={head1[u],v,w};
	head1[u]=tot1;
}
int f[maxn];
void dfs(int u){
	if(f[u])return ;
	for(int i=head1[u];i;i=e1[i].nxt){
		int v=e1[i].to;
		dfs(v);
		f[u]=max(f[u],f[v]+e1[i].w);
	}
	f[u]+=val[u];
}

signed main(){
	n=read();m=read();
	for(int i=1;i<=m;i++){
		int u,v,w,w1,lst;
		u=read();v=read();w=w1=read();
		long double p;scanf("%Lf",&p);
		lst=w;while(lst){
			lst=lst*p;
			w1+=lst;
		}
		add(u,v,w,w1);
	}
	s=read();
	tar(s);
	for(int u=1;u<=n;u++){
		for(int i=head[u];i;i=e[i].nxt){
			int v=e[i].to;
			if(scc[u]==scc[v])val[scc[u]]+=e[i].w1;
			else add1(scc[u],scc[v],e[i].w);
		}
	}
	dfs(scc[s]);
	printf("%lld\n",f[scc[s]]);
}
