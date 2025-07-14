// Problem: QTREE6 - Query on a tree VI
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/SP16549
// Memory Limit: 1 MB
// Time Limit: 5000 ms
// Written by yhm.
// Start codeing:2024-05-21 20:03:30
// 
// Powered by CP Editor (https://cpeditor.org)

#include<bits/stdc++.h>
#define int long long
#define mod 998244353ll
#define pii pair<int,int>
#define fi first
#define se second
#define mems(x,y) memset(x,y,sizeof(x))
using namespace std;
const int maxn=100010;
const int inf=1e18;
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
int dep[maxn],fa[maxn],siz[maxn],son[maxn];
void dfs(int u){
	dep[u]=dep[fa[u]]+1;siz[u]=1;
	for(int i=head[u];i;i=e[i].nxt){
		int v=e[i].to;if(v==fa[u])continue;
		fa[v]=u;dfs(v);siz[u]+=siz[v];
		if(siz[v]>siz[son[u]])son[u]=v;
	}
}
int dfn[maxn],rnk[maxn],idx,tp[maxn];
void dfs1(int u,int lst){
	rnk[dfn[u]=++idx]=u;tp[u]=lst;
	if(!son[u])return ;dfs1(son[u],lst);
	for(int i=head[u];i;i=e[i].nxt){
		int v=e[i].to;if(v==fa[u]||v==son[u])continue;
		dfs1(v,v);
	}
}
#define mid (l+r>>1)
#define ls nd<<1
#define rs nd<<1|1
int sum[maxn<<2][2],fr[maxn<<2][2];
void up(int nd){
	fr[nd][0]=max(fr[ls][0],fr[rs][0]);
	fr[nd][1]=max(fr[ls][1],fr[rs][1]);
}
void down(int nd){
	for(int i=0;i<2;i++)if(sum[nd][i]){
		sum[ls][i]+=sum[nd][i],sum[rs][i]+=sum[nd][i];
		sum[nd][i]=0;
	}
}
void build(int nd,int l,int r){
	fr[nd][0]=r,fr[nd][1]=-inf;
	if(l==r){
		sum[nd][0]=siz[rnk[l]],sum[nd][1]=1;
		// cout<<l<<" "<<rnk[l]<<" "<<siz[rnk[l]]<<"\n";
		return ;
	}
	build(ls,l,mid),build(rs,mid+1,r);
}
void modif(int nd,int l,int r,int p){
	if(l==r){
		swap(fr[nd][0],fr[nd][1]);
		return ;
	}
	if(p<=mid)modif(ls,l,mid,p);
	else modif(rs,mid+1,r,p);
	up(nd);
}
int ask(int nd,int l,int r,int ql,int qr,int op){
	if(l>=ql&&r<=qr)return fr[nd][op];
	if(qr<=mid)return ask(ls,l,mid,ql,qr,op);
	if(ql>mid)return ask(rs,mid+1,r,ql,qr,op);
	return max(ask(ls,l,mid,ql,qr,op),ask(rs,mid+1,r,ql,qr,op));
}
void updata(int nd,int l,int r,int ql,int qr,int op,int w){
	if(l>=ql&&r<=qr){
		sum[nd][op]+=w;
		return ;
	}
	down(nd);
	if(ql<=mid)updata(ls,l,mid,ql,qr,op,w);
	if(qr>mid)updata(rs,mid+1,r,ql,qr,op,w);
}
int query(int nd,int l,int r,int p,int op){
	if(l==r)return sum[nd][op];
	down(nd);
	if(p<=mid)return query(ls,l,mid,p,op);
	else return query(rs,mid+1,r,p,op);
}
int find(int u,int op){
	while(u){
		int p=ask(1,1,n,dfn[tp[u]],dfn[u],op);
		// cout<<u<<" "<<tp[u]<<" "<<p<<" fd\n";
		if(p>0)return rnk[p];
		u=fa[tp[u]];
	}
	return 1;
}
void upd(int u,int v,int op,int w){
	while(tp[u]!=tp[v]){
		if(dep[tp[u]]<dep[tp[v]])swap(u,v);
		updata(1,1,n,dfn[tp[u]],dfn[u],op,w);
		u=fa[tp[u]];
	}
	if(dep[u]<dep[v])swap(u,v);
	updata(1,1,n,dfn[v],dfn[u],op,w);
}
int getfa(int u,int v){
	while(dep[fa[tp[u]]]>dep[v])u=fa[tp[u]];
	if(dep[tp[u]]>dep[v])u=tp[u];
	if(dep[u]==dep[v]+1)return dfn[u];
	else return dfn[v]+1;
}
void work(){
	n=read();
	for(int i=1;i<n;i++){
		int u=read(),v=read();
		add(u,v),add(v,u);
	}
	dfs(1),dfs1(1,1);
	build(1,1,n);
	m=read();
	while(m--){
		int op=read(),x=read();
		if(!op){
			int p=find(x,a[x]^1);
			// cout<<p<<" ";
			if(a[x]==a[p])p=dfn[p];
			else p=getfa(x,p);
			// cout<<p<<" ";
			printf("%lld\n",query(1,1,n,p,a[x]));
		}
		else{
			int v[2],p[2];
			for(int i=0;i<2;i++){
				v[i]=query(1,1,n,dfn[x],i);
				if(fa[x])p[i]=find(fa[x],i);
			}
			if(fa[x]){
				upd(fa[x],p[a[x]^1],a[x],-v[a[x]]);
				upd(fa[x],p[a[x]],a[x]^1,v[a[x]^1]);
			}
			modif(1,1,n,dfn[x]);a[x]^=1;
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
