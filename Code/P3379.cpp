// Problem: P3379 【模板】最近公共祖先（LCA）
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P3379
// Memory Limit: 512 MB
// Time Limit: 2000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

#include<bits/stdc++.h>
#define mod 998244353
#define pii pair<int,int>
using namespace std;
const int maxn=500010;
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch-48);ch=getchar();}
	return x*f;
}
bool Mbe;


//预处理 O(n)
//查询 O(1)
//空间 O(n)
int n,m,s;
int head[maxn],tot;
struct nd{
	int nxt,to;
}e[maxn<<1];
void add(int u,int v){e[++tot]={head[u],v};head[u]=tot;}
int idx,dfn[maxn],rnk[maxn],l[maxn],fa[maxn],dep[maxn];
void dfs(int u){
	dep[u]=dep[fa[u]]+1;
	rnk[dfn[u]=++idx]=u;l[u]=__builtin_ctz(idx);
	for(int i=head[u];i;i=e[i].nxt){
		int v=e[i].to;if(v==fa[u])continue;
		fa[v]=u;dfs(v);
		l[u]=max(l[u],l[v]);
	}
}
int tp[maxn];unsigned int a[maxn];
void dfs1(int u,int lst){
	a[u]=a[fa[u]]|(1<<l[u]);tp[u]=lst;
	for(int i=head[u];i;i=e[i].nxt){
		int v=e[i].to;if(v==fa[u])continue;
		if(l[u]==l[v])dfs1(v,lst);
		else dfs1(v,v);
	}
}
int lca(int u,int v){
	if(u==v)return u;
	int d=31^__builtin_clz(dfn[u]^dfn[v]);
	int s=__builtin_ctz(((a[u]&a[v])>>d)<<d);
	cout<<dfn[u]<<" "<<dfn[v]<<" "<<__builtin_clz(dfn[u]^dfn[v])<<" "<<d<<" "<<s<<"\n";
	int du=31^__builtin_clz(a[u]<<(32-s)>>(32-s)),uu=(l[u]!=s?fa[tp[rnk[((dfn[u]>>du)|1)<<du]]]:u);
	int dv=31^__builtin_clz(a[v]<<(32-s)>>(32-s)),vv=(l[v]!=s?fa[tp[rnk[((dfn[v]>>dv)|1)<<dv]]]:v);
	if(dep[uu]<dep[vv])return uu;
	return vv;
}
void work(){
	n=read();m=read();s=read();
	for(int i=1;i<n;i++){
		int u=read(),v=read();
		add(u,v),add(v,u);
	}
	dfs(s),dfs1(s,s);
	while(m--){
		int u=read(),v=read();
		printf("%d\n",lca(u,v));
	}
}


//预处理 O(nlog n)
//查询 O(1)
//空间 O(nlog n)
// int n,m,s;
// int head[maxn],tot;
// struct nd{
	// int nxt,to;
// }e[maxn<<1];
// void add(int u,int v){e[++tot]={head[u],v};head[u]=tot;}
// int rnk[maxn],idx;
// int st[20][maxn],lg[maxn];
// void dfs(int u,int fa){
	// st[0][rnk[u]=++idx]=fa;
	// for(int i=head[u];i;i=e[i].nxt){
		// int v=e[i].to;
		// if(v!=fa)dfs(v,u);
	// }
// }
// int lca(int u,int v){
	// if(u==v)return u;
	// u=rnk[u],v=rnk[v];
	// if(u>v)swap(u,v);u++;
	// int k=lg[v-u+1];
	// if(rnk[st[k][u]]<rnk[st[k][v-(1<<k)+1]])return st[k][u];
	// return st[k][v-(1<<k)+1];
// }
// void work(){
	// n=read();m=read();s=read();
	// for(int i=1;i<n;i++){
		// int u=read(),v=read();
		// add(u,v);add(v,u);
	// }
	// dfs(s,0);
	// for(int i=0;i<20;i++){
		// for(int j=(1<<i);j<(1<<i+1)&&j<=n;j++)lg[j]=i;
		// if((1<<i+1)>n)break;
	// }
	// for(int j=1;j<=lg[n];j++){
		// for(int i=1;i+(1<<j)-1<=n;i++){
			// if(rnk[st[j-1][i]]<rnk[st[j-1][i+(1<<j-1)]])st[j][i]=st[j-1][i];
			// else st[j][i]=st[j-1][i+(1<<j-1)];
		// }
	// }
	// while(m--){
		// int u=read(),v=read();
		// printf("%d\n",lca(u,v));
	// }
// }


//预处理 O(n)
//查询 O(nlog n)
//空间 O(n)
// int n,m,s;
// int head[maxn],tot;
// struct nd{
	// int nxt,to;
// }e[maxn<<1];
// void add(int u,int v){e[++tot]={head[u],v};head[u]=tot;}
// int dep[maxn],fa[maxn],siz[maxn],son[maxn];
// int dfn[maxn],idx,rnk[maxn],tp[maxn];
// void dfs(int u){
	// dep[u]=dep[fa[u]]+1;siz[u]=1;
	// for(int i=head[u];i;i=e[i].nxt){
		// int v=e[i].to;
		// if(v!=fa[u]){
			// fa[v]=u;
			// dfs(v);
			// siz[u]+=siz[v];
			// if(siz[v]>siz[son[u]])son[u]=v;
		// }
	// }
// }
// void dfs2(int u,int lst){
	// dfn[u]=++idx;rnk[idx]=u;
	// tp[u]=lst;
	// if(!son[u])return ;
	// dfs2(son[u],lst);
	// for(int i=head[u];i;i=e[i].nxt){
		// int v=e[i].to;
		// if(v!=fa[u]&&v!=son[u])dfs2(v,v);
	// }
// }
// int lca(int u,int v){
	// while(tp[u]!=tp[v]){
		// if(dep[tp[u]]<dep[tp[v]])swap(u,v);
		// u=fa[tp[u]];
	// }
	// if(dep[u]>dep[v])swap(u,v);
	// return u;
// }
// void work(){
	// n=read();m=read();s=read();
	// for(int i=1;i<n;i++){
		// int u=read(),v=read();
		// add(u,v);add(v,u);
	// }
	// dfs(s);dfs2(s,s);
	// while(m--){
		// int u=read(),v=read();
		// printf("%d\n",lca(u,v));
	// }
// }


//预处理 O(nlog n)
//查询 O(log n)
//空间 O(nlog n)
// int n,m,s;
// int head[maxn],tot;
// struct nd{
	// int to,nxt;
// }e[maxn<<1];
// void add(int u,int v){
	// e[++tot]={v,head[u]};
	// head[u]=tot;
// }
// int dep[maxn],f[maxn][21];
// void dfs(int u,int fa){
	// dep[u]=dep[fa]+1;f[u][0]=fa;
	// for(int i=1;i<=20;i++)f[u][i]=f[f[u][i-1]][i-1];
	// for(int i=head[u];i;i=e[i].nxt){
		// int v=e[i].to;if(v==fa)continue;
		// dfs(v,u);
	// }
// }
// int lca(int x,int y){
	// if(dep[x]>dep[y])swap(x,y);
	// for(int i=20;i>=0;i--)if(dep[f[y][i]]>=dep[x])y=f[y][i];
	// if(x==y)return x;
	// for(int i=20;i>=0;i--)if(f[y][i]!=f[x][i])x=f[x][i],y=f[y][i];
	// return f[x][0];
// }
// void work(){
	// n=read();m=read();s=read();
	// for(int i=1;i<n;i++){
		// int u=read(),v=read();
		// add(u,v);add(v,u);
	// }
	// dfs(s,s);
	// for(int i=1;i<=m;i++){
		// int u=read(),v=read();
		// printf("%d\n",lca(u,v));
	// }
// }

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
