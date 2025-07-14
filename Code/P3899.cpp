#include<bits/stdc++.h>
#define int long long
#define mod 1000000007
using namespace std;
const int maxn=300010;
const int inf=1e9;
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch-48);ch=getchar();}
	return x*f;
}

int n,p;
int head[maxn],tot;
struct nd{
	int nxt,to;
}e[maxn<<1];
void add(int u,int v){
	e[++tot]={head[u],v};
	head[u]=tot;
}
int rt[maxn],cnt,tree[maxn*25];
int ls[maxn*25],rs[maxn*25];
int dep[maxn],siz[maxn];
int dfn[maxn],idx,rnk[maxn];
void build(int &nd,int l,int r){
	if(!nd)nd=++cnt;
	if(l==r)return ;
	int mid=l+r>>1;
	build(ls[nd],l,mid);build(rs[nd],mid+1,r);
}
void updata(int &nd,int l,int r,int pre,int ql,int w){
	nd=++cnt;tree[nd]=tree[pre];
	ls[nd]=ls[pre];rs[nd]=rs[pre];
	if(l==r){
		tree[nd]+=w;
		return ;
	}
	int mid=l+r>>1;
	if(ql<=mid)updata(ls[nd],l,mid,ls[pre],ql,w);
	else updata(rs[nd],mid+1,r,rs[pre],ql,w);
	tree[nd]=tree[ls[nd]]+tree[rs[nd]];
}
void dfs(int u,int fa){
	dep[u]=dep[fa]+1;siz[u]=1;
	dfn[u]=++idx;rnk[idx]=u;
	for(int i=head[u];i;i=e[i].nxt){
		int v=e[i].to;
		if(v!=fa){
			dfs(v,u);
			siz[u]+=siz[v];
		}
	}
}
void dfs2(int u,int fa){
	updata(rt[dfn[u]],1,n,rt[dfn[u]-1],dep[u],siz[u]-1);
	for(int i=head[u];i;i=e[i].nxt){
		int v=e[i].to;
		if(v!=fa)dfs2(v,u);
	}
}
int query(int nd,int l,int r,int ql,int qr){
	if(l>=ql&&r<=qr)return tree[nd];
	int mid=l+r>>1;
	if(qr<=mid)return query(ls[nd],l,mid,ql,qr);
	if(ql>mid)return query(rs[nd],mid+1,r,ql,qr);
	return query(ls[nd],l,mid,ql,qr)+query(rs[nd],mid+1,r,ql,qr);
}
int l,k,ans;

int T;
signed main(){
	//	freopen(".in","r",stdin);
	//	freopen(".out","w",stdout);
	
	n=read();p=read();
	for(int i=1;i<n;i++){
		int u,v;
		u=read();v=read();
		add(u,v);add(v,u);
	}
	build(rt[0],1,n);
	dfs(1,0);dfs2(1,0);
	while(p--){
		l=read();k=read();
		ans=min(k,dep[l]-1)*(siz[l]-1);
		if(siz[l]>=2)ans+=query(rt[dfn[l]+siz[l]-1],1,n,dep[l]+1,dep[l]+k)-query(rt[dfn[l]-1],1,n,dep[l]+1,dep[l]+k);
		printf("%lld\n",ans);
	}
}
