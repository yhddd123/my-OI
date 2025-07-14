// Problem: P7215 [JOISC2020] 首都
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P7215
// Memory Limit: 488 MB
// Time Limit: 2500 ms
// 
// Powered by CP Editor (https://cpeditor.org)

#include<bits/stdc++.h>
using namespace std;
const int maxn=200010;
static char buf[1000000],*p1=buf,*p2=buf;
#define getchar() p1==p2&&(p2=(p1=buf)+fread(buf,1,1000000,stdin),p1==p2)?EOF:*p1++
inline int read(){
	int x=0;char ch=getchar();
	while(ch<'0'||ch>'9')ch=getchar();
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch-48);ch=getchar();}
	return x;
}

int n,m,ans;
int head[maxn*20],tot;
struct nd{
	int nxt,to;
}e[maxn*55];
void add(int u,int v){e[++tot]={head[u],v};head[u]=tot;}
int to[18][maxn],dep[maxn];
int siz[maxn],son[maxn],top[maxn];
int dfn[maxn*20],idx;
void dfs(int u,int fa){
	siz[u]=1;to[0][u]=fa;dep[u]=dep[fa]+1;
	for(int i=1;i<=17;i++)to[i][u]=to[i-1][to[i-1][u]];
	for(int i=head[u];i;i=e[i].nxt){
		int v=e[i].to;if(v==fa)continue;
		dfs(v,u);siz[u]+=siz[v];
		if(siz[v]>=siz[son[u]])son[u]=v;
	}
}
void dfs1(int u,int fa,int lst){
	dfn[u]=++idx;top[u]=lst;
	if(!son[u])return ;
	dfs1(son[u],u,lst);
	for(int i=head[u];i;i=e[i].nxt){
		int v=e[i].to;if(v==fa||v==son[u])continue;
		dfs1(v,u,v);
	}
}
int lca(int u,int v){
	while(top[u]!=top[v]){
		if(dep[top[u]]<dep[top[v]])swap(u,v);
		u=to[0][top[u]];
	}
	if(dep[u]<dep[v])swap(u,v);
	return v;
}
int id[18][maxn];
vector<int> pos[maxn];
bool cmp(int u,int v){return dfn[u]<dfn[v];}
void updata(int u,int v,int w){
	for(int i=17;~i;i--)if(dep[to[i][u]]>=dep[v])add(w,id[i][u]),u=to[i][u];
}
int lw[maxn*20],tim,st[maxn*20],tp,scc[maxn*20],scct,val[maxn*20];
void tar(int u){
	dfn[u]=lw[u]=++tim;st[++tp]=u;
	for(int i=head[u];i;i=e[i].nxt){
		int v=e[i].to;
		if(!dfn[v]){
			tar(v);
			lw[u]=min(lw[u],lw[v]);
		}
		else if(!scc[v])lw[u]=min(lw[u],dfn[v]);
	}
	if(dfn[u]==lw[u]){
		scc[st[tp]]=++scct;
		val[scct]=(st[tp]<=m);
		while(st[tp--]!=u){
			scc[st[tp]]=scct;
			val[scct]+=(st[tp]<=m);
		}
	}
}
bool fl[maxn*20];

signed main(){
	n=read();m=read();
	for(int i=1;i<n;i++){
		int u=read(),v=read();
		add(u,v),add(v,u);
	}
	dfs(1,0);dfs1(1,0,1);idx+=m;
	for(int i=1;i<=n;i++)head[i]=0;tot=0;
	for(int i=2;i<=n;i++){
		id[0][i]=++idx;
		add(id[0][i],i+m),add(id[0][i],to[0][i]+m);
	}
	for(int j=1;j<=17;j++)for(int i=1;i<=n;i++)if(to[j][i]){
		id[j][i]=++idx;
		// cout<<j<<" "<<i<<" "<<idx<<"\n";
		add(id[j][i],id[j-1][i]),add(id[j][i],id[j-1][to[j-1][i]]);
	}
	for(int i=1;i<=n;i++){
		int c=read();
		pos[c].push_back(i);
		add(i+m,c);
	}
	// for(int i=1;i<=n;i++){
		// for(int j=1;j<=n;j++)cout<<lca(i,j)<<" ";
		// cout<<"\n";
	// }
	for(int i=1;i<=m;i++){
		sort(pos[i].begin(),pos[i].end(),cmp);
		updata(pos[i][0],lca(pos[i][0],pos[i].back()),i);
		for(int j=1;j<pos[i].size();j++)updata(pos[i][j],lca(pos[i][j],pos[i][j-1]),i);
	}
	for(int i=1;i<=n;i++)dfn[i]=0;
	for(int i=1;i<=idx;i++)if(!dfn[i])tar(i);
	for(int u=1;u<=idx;u++){
		for(int i=head[u];i;i=e[i].nxt){
			int v=e[i].to;
			if(scc[u]!=scc[v])fl[scc[u]]=1;
		}
	}
	ans=n-1;for(int i=1;i<=scct;i++)if(!fl[i])ans=min(ans,val[i]-1);
	printf("%d\n",ans);
}
