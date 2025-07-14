#include<bits/stdc++.h>
#define int long long
#define db double
#define mod 1000000007
using namespace std;
const int maxn=2000010;
const int inf=1e9;
const db eps=1e-9;
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
void add(int u,int v){e[++tot]={head[u],v};head[u]=tot;}
int dfn[maxn],lw[maxn],idx;
int st[maxn],tp;
int scc[maxn],scct;
bool vis[maxn];
void tar(int u){
	st[++tp]=u;vis[u]=1;
	dfn[u]=lw[u]=++idx;
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
		vis[st[tp]]=0;
		while(st[tp--]!=u){
			scc[st[tp]]=scct;
			vis[st[tp]]=0;
		}
	}
}
void sovle(){
	n=read();m=read();
	for(int i=1;i<=m;i++){
		int u=read(),x=read(),v=read(),y=read();
		add(u+(1-x)*n,v+y*n);
		add(v+(1-y)*n,u+x*n);
	}
	for(int i=1;i<=2*n;i++)if(!dfn[i])tar(i);
	for(int i=1;i<=n;i++)if(scc[i]==scc[i+n]){
		printf("IMPOSSIBLE\n");
		return ;
	}
//	for(int i=1;i<=2*n;i++)cout<<scc[i]<<" ";
	printf("POSSIBLE\n");
	for(int i=1;i<=n;i++){
		if(scc[i]<scc[i+n])printf("0 ");
		else printf("1 ");
	}
}

int T;
signed main(){
	//	freopen(".in","r",stdin);
	//	freopen(".out","w",stdout);
	
	T=1;
	while(T--)sovle();
}
