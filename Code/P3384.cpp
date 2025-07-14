#include<bits/stdc++.h>
#define int long long
using namespace std;
const int maxn=1000010;
int n,m,mod,root,a[maxn];

int fa[maxn],dep[maxn],siz[maxn],hson[maxn],top[maxn],dfn[maxn],rnk[maxn],bot[maxn];
//父亲;深度;节点个数;重儿子;重链顶点;DFS序;DFS序的节点编号 
int tree[maxn<<2],laz[maxn<<2],l,r,w,ans;

static char buf[1000000],*p1=buf,*p2=buf;
#define getchar() p1==p2&&(p2=(p1=buf)+fread(buf,1,1000000,stdin),p1==p2)?EOF:*p1++
inline int read(){
	int x=0;
	char ch=getchar();
	while(ch<'0' || ch>'9')	ch=getchar();
	while(ch>='0' && ch<='9'){
		x=(x<<3)+(x<<1)+(ch^48);
		ch=getchar();
	}
	return x;
}

int head[maxn],tot;
struct nd{
	int to,nxt;
}e[maxn<<1];
void add(int x,int y){//x->y
	e[++tot].nxt=head[x];
	e[tot].to=y;
	head[x]=tot;
}

void dfs1(int u){
	siz[u]=1;
	for(int i=head[u];i;i=e[i].nxt){
		int v=e[i].to;
		if(v!=fa[u]){
			dep[v]=dep[u]+1;
			fa[v]=u;
			dfs1(v);
			siz[u]+=siz[v];
			if(siz[v]>siz[hson[u]])hson[u]=v;
		}
	}
}

int cnt;
void dfs2(int u,int f){
	top[u]=f;
	dfn[u]=++cnt;
	rnk[cnt]=u;
	bot[u]=dfn[u]+siz[u]-1;
	if(hson[u]==0)return ;
	dfs2(hson[u],f);
	for(int i=head[u];i;i=e[i].nxt){
		int v=e[i].to;
		if(v!=hson[u] && v!=fa[u])dfs2(v,v);
	}
}


void build(int nd,int x,int y){
	if(x==y){
		tree[nd]=a[rnk[x]];
		return ;
	}
	int ln=2*nd,rn=2*nd+1,mid=(x+y)/2;
	build(ln,x,mid);build(rn,mid+1,y);
	tree[nd]=(tree[ln]+tree[rn])%mod;
}

void push(int nd,int x,int y){
	if(laz[nd]==0)return ;
	int ln=2*nd,rn=2*nd+1,mid=(x+y)/2;
	tree[ln]+=laz[nd]*(mid-x+1);
	tree[ln]%=mod;
	laz[ln]+=laz[nd];
	laz[ln]%=mod;
	tree[rn]+=laz[nd]*(y-mid);
	tree[rn]%=mod;
	laz[rn]+=laz[nd];
	laz[rn]%=mod;
	laz[nd]=0;
}

void updata(int nd,int x,int y){
	if(x>=l && y<=r){
		tree[nd]+=w*(y-x+1);
		tree[nd]%=mod;
		laz[nd]+=w;
		laz[nd]%=mod;
		return ;
	}
	push(nd,x,y);
	int ln=2*nd,rn=2*nd+1,mid=(x+y)/2;
	if(l<=mid)updata(ln,x,mid);
	if(r>mid)updata(rn,mid+1,y);
	tree[nd]=tree[ln]+tree[rn]; 
	tree[nd]%=mod;
}
void upd(int x,int y){//1
	while(top[x]!=top[y]){
		if(dep[top[x]]>dep[top[y]])swap(x,y);
		l=dfn[top[y]],r=dfn[y];
		updata(1,1,n);
		y=fa[top[y]];
	}
	l=min(dfn[x],dfn[y]),r=max(dfn[x],dfn[y]);
	updata(1,1,n);
}

void query(int nd,int x,int y){
	if(x>=l && y<=r){
		ans+=tree[nd];
		ans%=mod;
		return ;
	}
	push(nd,x,y);
	int ln=2*nd,rn=2*nd+1,mid=(x+y)/2;
	if(l<=mid)query(ln,x,mid);
	if(r>mid)query(rn,mid+1,y);
}
void que(int x,int y){//2
	while(top[x]!=top[y]){
		if(dep[top[x]]>dep[top[y]])swap(x,y);
		l=dfn[top[y]],r=dfn[y];
		query(1,1,n);
		y=fa[top[y]];
	}
	l=min(dfn[x],dfn[y]),r=max(dfn[x],dfn[y]);
	query(1,1,n);
}


signed main(){
	n=read();m=read();root=read();mod=read();
	for(int i=1;i<=n;i++)a[i]=read();
	for(int i=1;i<n;i++){
		int u,v;
		u=read();v=read();
		add(u,v);add(v,u);
	}
	dep[root]=1;
	fa[root]=root;
	dfs1(root);
	dfs2(root,root);
	build(1,1,n);
	for(int i=1;i<=m;i++){
		int opt;
		opt=read();
		if(opt==1){//路径改 
			l=read();r=read();w=read();
			upd(l,r);
		}
		else if(opt==2){//路径和 
			ans=0;
			l=read();r=read();
			que(l,r);
			printf("%lld\n",ans%mod);
		}
		else if(opt==3){//子树改 
			l=read();w=read();
			r=bot[l];l=dfn[l];
			updata(1,1,n);
		} 
		else if(opt==4){//子树和 
			l=read();
			r=bot[l];l=dfn[l];
			ans=0;
			query(1,1,n);
			printf("%lld\n",ans%mod);
		}
	}
}
