#include<bits/stdc++.h>
#define int long long
#define mod 998244353ll
#define pii pair<int,int>
#define fi first
#define se second
#define mems(x,y) memset(x,y,sizeof(x))
using namespace std;
const int maxn=200010;
const int inf=1e18;
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch-48);ch=getchar();}
	return x*f;
}
bool Mbe;

int n,q,ans,sa;
int head[maxn],tot;
struct nd{
	int nxt,to;
}e[maxn<<1];
void add(int u,int v){e[++tot]={head[u],v};head[u]=tot;}
int fa[maxn],siz[maxn],dep[maxn],son[maxn];
void dfs(int u){
	siz[u]=1;dep[u]=dep[fa[u]]+1;
	for(int i=head[u];i;i=e[i].nxt){
		int v=e[i].to;if(v==fa[u])continue;
		fa[v]=u;dfs(v);siz[u]+=siz[v];
		if(siz[v]>siz[son[u]])son[u]=v;
	}
}
int dfn[maxn],rnk[maxn],idx,tp[maxn];
void dfs1(int u,int lst){
	rnk[dfn[u]=++idx]=u;tp[u]=lst;
	if(!son[u])return ;
	dfs1(son[u],lst);
	for(int i=head[u];i;i=e[i].nxt){
		int v=e[i].to;if(v==fa[u]||v==son[u])continue;
		dfs1(v,v);
	}
}
int kth(int u,int k){
	while(dep[u]-dep[fa[tp[u]]]<=k)k-=dep[u]-dep[fa[tp[u]]],u=fa[tp[u]];
	u=rnk[dfn[u]-k];return u;
}
#define mid (l+r>>1)
#define ls nd<<1
#define rs nd<<1|1
int sum[maxn<<2],tree[maxn<<2],tag[maxn<<2],tk[maxn<<2],tb[maxn<<2];
void build(int nd,int l,int r){
	if(l==r){sum[nd]=siz[rnk[l]];return ;}
	build(ls,l,mid),build(rs,mid+1,r);
	sum[nd]=sum[ls]+sum[rs];
}
void inc(int nd,int w){
	tag[nd]+=w,tree[nd]+=w*sum[nd];
}
void inc(int nd,int l,int r,int k,int b){
	tree[nd]+=(l+r)*(r-l+1)/2*k+(r-l+1)*b;
	tk[nd]+=k,tb[nd]+=b;
}
void push(int nd,int l,int r){
	if(tag[nd])inc(ls,tag[nd]),inc(rs,tag[nd]),tag[nd]=0;
	if(tk[nd]||tb[nd])inc(ls,l,mid,tk[nd],tb[nd]),inc(rs,mid+1,r,tk[nd],tb[nd]),tk[nd]=tb[nd]=0;
}
void updata(int nd,int l,int r,int ql,int qr,int w){
	if(l>=ql&&r<=qr){
		inc(nd,w);
		return ;
	}
	push(nd,l,r);
	if(ql<=mid)updata(ls,l,mid,ql,qr,w);
	if(qr>mid)updata(rs,mid+1,r,ql,qr,w);
	tree[nd]=tree[ls]+tree[rs];
}
void modif(int nd,int l,int r,int ql,int qr,int k,int b){
	if(l>=ql&&r<=qr){
		inc(nd,l,r,k,b);
		return ;
	}
	push(nd,l,r);
	if(ql<=mid)modif(ls,l,mid,ql,qr,k,b);
	if(qr>mid)modif(rs,mid+1,r,ql,qr,k,b);
	tree[nd]=tree[ls]+tree[rs];
}
void upd(int u,int w){
	while(u){
		modif(1,1,n,dfn[tp[u]],dfn[u],0,w);
		u=fa[tp[u]];
	}
}
int query(int nd,int l,int r,int ql,int qr){
	if(l>=ql&&r<=qr)return tree[nd];
	push(nd,l,r);
	if(qr<=mid)return query(ls,l,mid,ql,qr);
	if(ql>mid)return query(rs,mid+1,r,ql,qr);
	return query(ls,l,mid,ql,qr)+query(rs,mid+1,r,ql,qr);
}
void work(){
	n=read();
	for(int i=1;i<n;i++){
		int u=read(),v=read();
		add(u,v),add(v,u);
	}
	dfs(1),dfs1(1,1);
	build(1,1,n);
	q=read();
	while(q--){
		int op=read();
		if(op==1){
			int u=read(),v=read();
			if(dfn[v]<=dfn[u]&&dfn[u]<=dfn[v]+siz[v]-1){
				updata(1,1,n,1,n,1),sa+=n;
				if(u==v)continue;
				int vv=kth(u,dep[u]-dep[v]-1);
				updata(1,1,n,dfn[vv],dfn[vv]+siz[vv]-1,-1),sa-=siz[vv];
				upd(v,-siz[vv]);
			}
			else{
				sa+=siz[v];
				updata(1,1,n,dfn[v],dfn[v]+siz[v]-1,1);
				if(fa[v])upd(fa[v],siz[v]);
			}
		}
		if(op==2){
			int u=read(),v=read();
			int l1=0,l2=0;
			while(tp[u]!=tp[v]){
				if(dep[tp[u]]<dep[tp[v]])swap(u,v),swap(l1,l2);
				modif(1,1,n,dfn[tp[u]],dfn[u],-1,dfn[u]+l1+1),l1+=dep[u]-dep[tp[u]]+1;
				u=fa[tp[u]];
			}
			if(dep[u]<dep[v])swap(u,v),swap(l1,l2);
			upd(v,l2);
			modif(1,1,n,dfn[v],dfn[u],-1,dfn[u]+l1+1),l1+=dep[u]-dep[v]+1;
			if(fa[v])upd(fa[v],l1);
			sa+=l1+l2;
		}
		if(op==3){
			int u=read();
			ans=dep[u]*sa+tree[1];
			while(u){
				ans-=2*query(1,1,n,dfn[tp[u]],dfn[u]);
				u=fa[tp[u]];
			}
			printf("%lld\n",ans);
		}
	}
	
}

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
