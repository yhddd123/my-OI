// Problem: P9220 「TAOI-1」椎名真昼
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P9220
// Memory Limit: 256 MB
// Time Limit: 1000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

#include<bits/stdc++.h>
#define pii pair<int,int>
using namespace std;
const int maxn=100010;
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch-48);ch=getchar();}
	return x*f;
}
bool Mbe;

int n,m,a[maxn];
int head[maxn],tot;
struct nd{
	int nxt,to;
}e[maxn<<1];
void add(int u,int v){e[++tot]={head[u],v};head[u]=tot;}
pii g[maxn<<1];
int dfn[maxn],lw[maxn],idx;
int scc[maxn],scct;
int st[maxn],tp;
int col[maxn];
bool vis[maxn];
void tar(int u){
	lw[u]=dfn[u]=++idx;st[++tp]=u;
	for(int i=head[u];i;i=e[i].nxt){
		int v=e[i].to;
		// cout<<u<<" "<<v<<"\n";
		if(!dfn[v]){
			tar(v);
			lw[u]=min(lw[u],lw[v]);
		}
		else if(!scc[v])lw[u]=min(lw[u],dfn[v]);
	}
	if(dfn[u]==lw[u]){
		++scct;
		scc[st[tp]]=scct;
		col[scct]=a[st[tp]];
		while(st[tp--]!=u){
			scc[st[tp]]=scct;
			if(col[scct]!=a[st[tp]])col[scct]=2;
		}
	}
}
int d[maxn];
queue<int> q;
void dfs(int u){
	col[u]^=1;vis[u]=1;
	for(int i=head[u];i;i=e[i].nxt){
		int v=e[i].to;
		if(vis[v])continue;
		dfs(v);
	}
}
map<int,bool> mp[maxn];
void work(){
	n=read();m=read();
	for(int i=1;i<=n;i++)head[i]=0;tot=0;
	tp=idx=scct=0;
	for(int i=1;i<=n;i++)scc[i]=dfn[i]=lw[i]=vis[i]=0,col[i]=-1;
	for(int i=1;i<=n;i++)a[i]=read();
	for(int i=1;i<=m;i++){
		int u=read(),v=read();
		g[i]={u,v};
		add(u,v);
	}
	for(int i=1;i<=n;i++)if(!dfn[i])tar(i);
	// for(int i=1;i<=n;i++)cout<<dfn[i]<<" "<<lw[i]<<" "<<scc[i]<<"\n";
	for(int i=1;i<=scct;i++)if(col[i]==2){printf("N");return ;}
	for(int i=1;i<=n;i++)d[i]=head[i]=0,mp[i].clear();tot=0;
	for(int i=1;i<=m;i++){
		int u=g[i].first,v=g[i].second;
		if(scc[u]!=scc[v]&&!mp[scc[u]][scc[v]])add(scc[u],scc[v]),d[scc[v]]++,mp[scc[u]][scc[v]]=1;
	}
	bool fl=1;
	for(int i=1;i<=scct;i++)if(col[i])fl=0;
	if(fl){printf("B");return ;}
	for(int i=1;i<=scct;i++)if(!d[i]&&!col[i])fl=1;
	if(scct==2&&!fl){
		if(d[2]&&col[1]&&!col[2]){printf("B");return ;}
		if(d[1]&&col[2]&&!col[1]){printf("B");return ;}
		if(!d[1]&&!d[2]){printf("B");return ;}
	}
	for(int i=1;i<=scct;i++)if(!d[i])q.push(i);
	int s=0;
	while(!q.empty()){
		int u=q.front();q.pop();
		if(col[u]){s=u;break;}
		for(int i=head[u];i;i=e[i].nxt){
			int v=e[i].to;
			if(d[v]){
				d[v]--;
				if(!d[v])q.push(v);
			}
		}
	}
	while(!q.empty())q.pop();
	if(s){
		dfs(s);
		bool fl=1;
		for(int i=1;i<=scct;i++)if(col[i])fl=0;
		if(fl){printf("A");return ;}
	}
	printf("N");
}

// \
444

bool Med;
int T;
signed main(){
	// freopen("1.in","r",stdin);
//	freopen(".out","w",stdout);
	
//	ios::sync_with_stdio(0);
//	cin.tie(0);cout.tie(0);
	
	// cerr<<(&Mbe-&Med)/1048576.0<<" MB\n";
	
	T=read();
	while(T--)work();
}