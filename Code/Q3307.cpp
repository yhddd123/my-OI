#include<bits/stdc++.h>
#define int long long
#define mod 998244353
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

int n,q;
int head[maxn],tot;
struct nd{
	int nxt,to;
}e[maxn<<1];
void add(int u,int v){e[++tot]={head[u],v};head[u]=tot;}
int siz[maxn],dep[maxn],fa[maxn],son[maxn];
int f[maxn][17];
void dfs1(int u){
	dep[u]=dep[fa[u]]+1;siz[u]=1;
	f[u][0]=fa[u];for(int i=1;i<=16;i++)f[u][i]=f[f[u][i-1]][i-1];
	for(int i=head[u];i;i=e[i].nxt){
		int v=e[i].to;
		if(v==fa[u])continue;
		fa[v]=u;dfs1(v);siz[u]+=siz[v];
		if(siz[v]>siz[son[u]])son[u]=v;
	}
}
int top[maxn],dfn[maxn],idx,rnk[maxn];
void dfs2(int u,int lst){
	rnk[dfn[u]=++idx]=u;top[u]=lst;
	if(!son[u])return ;
	dfs2(son[u],lst);
	for(int i=head[u];i;i=e[i].nxt){
		int v=e[i].to;
		if(v==fa[u]||v==son[u])continue;
		dfs2(v,v);
	}
}
namespace sgt{
	#define mid (l+r>>1)
	#define ls nd<<1
	#define rs nd<<1|1
	int tree[maxn<<2],tag[maxn<<2];
	void push(int nd,int l,int r){
		tree[ls]+=tag[nd]*(mid-l+1),tag[ls]+=tag[nd];
		tree[rs]+=tag[nd]*(r-mid),tag[rs]+=tag[nd];
		tag[nd]=0;
	}
	void updata(int nd,int l,int r,int ql,int qr,int w){
		if(l>=ql&&r<=qr){
			tree[nd]+=(r-l+1)*w,tag[nd]+=w;
			return ;
		}
		if(tag[nd])push(nd,l,r);
		if(ql<=mid)updata(ls,l,mid,ql,qr,w);
		if(qr>mid)updata(rs,mid+1,r,ql,qr,w);
		tree[nd]=tree[ls]+tree[rs];
	}
	int query(int nd,int l,int r,int ql,int qr){
		if(l>=ql&&r<=qr)return tree[nd];
		if(tag[nd])push(nd,l,r);
		if(qr<=mid)return query(ls,l,mid,ql,qr);
		if(ql>mid)return query(rs,mid+1,r,ql,qr);
		return query(ls,l,mid,ql,qr)+query(rs,mid+1,r,ql,qr);
	}
	int find(int nd,int l,int r,int val){
		if(l==r)return l;
		if(tag[nd])push(nd,l,r);
		if(tree[ls]>=val)return find(ls,l,mid,val);
		else return find(rs,mid+1,r,val-tree[ls]);
	}
}
void updata(int u,int v,int w){
	while(top[u]!=top[v]){
		if(dfn[top[u]]<dfn[top[v]])swap(u,v);
		sgt::updata(1,1,n,dfn[top[u]],dfn[u],w);
		u=fa[top[u]];
	}
	if(dfn[u]<dfn[v])swap(u,v);
	sgt::updata(1,1,n,dfn[v],dfn[u],w);
}
void work(){
	n=read();
	for(int i=1;i<n;i++){
		int u=read(),v=read();
		add(u,v),add(v,u);
	}
	dfs1(1),dfs2(1,1);
	q=read();
	while(q--){
		int op=read();
		if(op==1){
			int u=read();
			sgt::updata(1,1,n,dfn[u],dfn[u]+siz[u]-1,1);
		}
		else{
			int u=read(),v=read();
			updata(u,v,1);
		}
		int sum=sgt::tree[1];
		int pos=rnk[sgt::find(1,1,n,sum/2+1)];
		if(sgt::query(1,1,n,dfn[pos],dfn[pos]+siz[pos]-1)*2<=sum){
			for(int i=16;~i;i--)if(f[pos][i]){
				if(sgt::query(1,1,n,dfn[f[pos][i]],dfn[f[pos][i]]+siz[f[pos][i]]-1)*2<=sum)pos=f[pos][i];
			}
			pos=f[pos][0];
		}
		printf("%lld\n",pos);
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
