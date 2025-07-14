#include<bits/stdc++.h>
using namespace std;
const int maxn=100010;
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
int f[maxn][21],dep[maxn];
void dfs(int u,int fa){
	f[u][0]=fa;dep[u]=dep[fa]+1;
	for(int i=1;i<=20;i++)f[u][i]=f[f[u][i-1]][i-1];
	for(int i=head[u];i;i=e[i].nxt){
		int v=e[i].to;
		if(v==fa)continue;
		dfs(v,u);
	}
}
int lca(int u,int v){
	if(dep[u]<dep[v])swap(u,v);
	for(int i=20;i>=0;i--)if(dep[f[u][i]]>=dep[v])u=f[u][i];
	if(u==v)return u;
	for(int i=20;i>=0;i--)if(f[u][i]!=f[v][i])u=f[u][i],v=f[v][i];
	return f[u][0];
}
vector<int> del[maxn];
#define mid (l+r>>1)
int rt[maxn],tree[maxn*40],ls[maxn*40],rs[maxn*40],idx;
void updata(int &nd,int p,int w,int l=1,int r=maxn-10){
	if(!nd)nd=++idx;
	if(l==r){
		tree[nd]+=w;
		return ;
	}
	if(p<=mid)updata(ls[nd],p,w,l,mid);
	else updata(rs[nd],p,w,mid+1,r);
	tree[nd]=max(tree[ls[nd]],tree[rs[nd]]);
}
void merge(int &nd,int nd1,int l=1,int r=maxn-10){
	if(!nd){
		nd=nd1;
		return ;
	}
	else if(!nd1)return ;
	if(l==r){
		tree[nd]+=tree[nd1];
		return ;
	}
	merge(ls[nd],ls[nd1],l,mid);
	merge(rs[nd],rs[nd1],mid+1,r);
	tree[nd]=max(tree[ls[nd]],tree[rs[nd]]);
}
int query(int nd,int l=1,int r=maxn-10){
	if(!tree[nd])return 0;
	if(l==r)return l;
	if(tree[ls[nd]]==tree[nd])return query(ls[nd],l,mid);
	return query(rs[nd],mid+1,r);
}
#undef mid
int ans[maxn];
void dfs1(int u,int fa){
	for(int i=head[u];i;i=e[i].nxt){
		int v=e[i].to;
		if(v==fa)continue;
		dfs1(v,u);
		merge(rt[u],rt[v]);
	}
	for(int i:del[u])updata(rt[u],i,-1);
	ans[u]=query(rt[u]);
}

signed main(){
	n=read();m=read();
	for(int i=1;i<n;i++){
		int u=read(),v=read();
		add(u,v);add(v,u);
	}
	dfs(1,0);
	for(int i=1;i<=m;i++){
		int u=read(),v=read(),z=read();
		int tp=lca(u,v);
		updata(rt[u],z,1);updata(rt[v],z,1);
		del[tp].push_back(z);del[f[tp][0]].push_back(z);
	}
	dfs1(1,0);
	for(int i=1;i<=n;i++)printf("%d\n",ans[i]);
}
