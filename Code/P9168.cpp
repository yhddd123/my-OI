// Problem: P9168 [省选联考 2023] 人员调度
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P9168
// Memory Limit: 512 MB
// Time Limit: 5000 ms
// Written by yhm.
// Start codeing:2026-03-03 18:37:50
// 
// Powered by CP Editor (https://cpeditor.org)

#include<bits/stdc++.h>
#define int long long
#define mod 998244353ll
#define pii pair<int,int>
#define fi first
#define se second
#define pb push_back
#define db long double
#define mems(a,x) memset((a),(x),sizeof(a))
using namespace std;
inline int read(){
	int x=0,fl=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')fl=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
	return x*fl;
}
const int maxn=100010;
const int inf=1e9;
bool mbe;

int n,k,q,ans,res[maxn];
pii a[maxn<<1];int tim[maxn<<1];
vector<int> e[maxn];
int fa[maxn],dep[maxn],siz[maxn],son[maxn];
void dfs(int u){
	dep[u]=dep[fa[u]]+1,siz[u]=1,son[u]=0;
	for(int v:e[u])if(v!=fa[u]){
		dfs(v),siz[u]+=siz[v];
		if(siz[v]>siz[son[u]])son[u]=v;
	}
}
int dfn[maxn],rnk[maxn],idx,tp[maxn],ed[maxn];
void dfs(int u,int lst){
	rnk[dfn[u]=++idx]=u;tp[u]=lst;ed[u]=u;
	if(!son[u])return ;dfs(son[u],lst);ed[u]=ed[son[u]];
	for(int v:e[u])if(v!=fa[u]&&v!=son[u])dfs(v,v);
}
#define mid ((l+r)>>1)
int rt[maxn];
namespace sgt1{
#define ls lc[nd]
#define rs rc[nd]
int mn[maxn<<1],tag[maxn<<1];
int lc[maxn<<1],rc[maxn<<1],idx;
void build(int &nd,int l,int r){
	nd=++idx;
	if(l==r)return ;
	build(ls,l,mid),build(rs,mid+1,r);
}
void upd(int nd,int w){mn[nd]+=w,tag[nd]+=w;}
void down(int nd){upd(ls,tag[nd]),upd(rs,tag[nd]),tag[nd]=0;}
void updata(int nd,int l,int r,int ql,int qr,int w){
	if(l>=ql&&r<=qr)return upd(nd,w);
	if(tag[nd])down(nd);
	if(ql<=mid)updata(ls,l,mid,ql,qr,w);
	if(qr>mid)updata(rs,mid+1,r,ql,qr,w);
	mn[nd]=min(mn[ls],mn[rs]);
}
int find(int nd,int l,int r,int p){
	if(mn[nd])return -1;
	if(l==r)return l;
	if(tag[nd])down(nd);
	if(p<=mid)return find(ls,l,mid,p);
	else{
		int res=find(rs,mid+1,r,p);
		if(res==-1)return find(ls,l,mid,p);
		else return res;
	}
}
#undef ls
#undef rs
}
#define all(u) rt[u],dfn[u],dfn[ed[u]]
void upd(int u,int v,int w){
	while(tp[u]!=tp[v]){
		sgt1::updata(all(tp[u]),dfn[tp[u]],dfn[u],w);
		u=fa[tp[u]];
	}
	if(u!=v)sgt1::updata(all(tp[u]),dfn[v]+1,dfn[u],w);
}
int que(int u){
	while(u){
		int p=sgt1::find(all(tp[u]),dfn[u]);
		if(p==-1)u=fa[tp[u]];
		else return rnk[p];
	}
	return 1;
}
namespace sgt2{
#define ls nd<<1
#define rs nd<<1|1
pii mn[maxn<<2];
multiset<int> s[maxn];
void build(int nd,int l,int r){
	if(l==r){
		int u=rnk[l];
		s[u].insert(0);
		mn[nd]={0,u};
	return ;}
	build(ls,l,mid),build(rs,mid+1,r);
	mn[nd]=min(mn[ls],mn[rs]);
}
void modif(int nd,int l,int r,int p,int w,int o){
	if(l==r){
		int u=rnk[l];
		if(o==1)s[u].insert(w);
		else s[u].erase(s[u].find(w));
		mn[nd]={s[u].size()?(*s[u].begin()):inf,u};
		return ;
	}
	if(p<=mid)modif(ls,l,mid,p,w,o);
	else modif(rs,mid+1,r,p,w,o);
	mn[nd]=min(mn[ls],mn[rs]);
}
pii query(int nd,int l,int r,int ql,int qr){
	if(l>=ql&&r<=qr)return mn[nd];
	if(qr<=mid)return query(ls,l,mid,ql,qr);
	if(ql>mid)return query(rs,mid+1,r,ql,qr);
	return min(query(ls,l,mid,ql,qr),query(rs,mid+1,r,ql,qr));
}
}
vector<int> tree[maxn<<2];
void updata(int nd,int l,int r,int ql,int qr,int w){
	if(l>=ql&&r<=qr){tree[nd].pb(w);return ;}
	if(ql<=mid)updata(ls,l,mid,ql,qr,w);
	if(qr>mid)updata(rs,mid+1,r,ql,qr,w);
}
pair<int,pii> tmp[maxn<<1];
void dfs(int nd,int l,int r){
	for(int id:tree[nd]){
		auto[u,w]=a[id];
		int tp=que(u);
		pii res=sgt2::query(1,1,n,dfn[tp],dfn[tp]+siz[tp]-1);
		if(res.fi<w){
			tmp[id]={tp,res};
			ans+=w-res.fi;
			upd(u,tp,-1),upd(res.se,tp,1);
			sgt2::modif(1,1,n,dfn[res.se],res.fi,-1);
			sgt2::modif(1,1,n,dfn[u],w,1);
		}
		else tmp[id]={0,{0,0}};
		// cout<<u<<" "<<w<<" "<<tp<<" "<<res.fi<<" "<<res.se<<" "<<ans<<endl;
	}
	if(l==r){
		res[l]=ans;
	}
	else dfs(ls,l,mid),dfs(rs,mid+1,r);	
	for(int i=(int)tree[nd].size()-1;~i;i--){
		int id=tree[nd][i];auto[u,w]=a[id];
		if(tmp[id].fi){
			auto[tp,res]=tmp[id];ans-=w-res.fi;
			upd(u,tp,1),upd(res.se,tp,-1);
			sgt2::modif(1,1,n,dfn[u],w,-1);
			sgt2::modif(1,1,n,dfn[res.se],res.fi,1);
		}
	}
}
void work(){
	n=read();k=read();q=read();
	for(int i=2;i<=n;i++)e[fa[i]=read()].pb(i);
	dfs(1),dfs(1,1);
	for(int u=1;u<=n;u++)if(tp[u]==u)sgt1::build(all(u));
	sgt2::build(1,1,n);
	for(int i=1;i<=k;i++)a[i]={read(),read()};
	for(int t=1;t<=q;t++){
		int o=read();
		if(o==1){
			a[++k]={read(),read()};tim[k]=t;
		}
		else{
			int id=read();
			updata(1,0,q,tim[id],t-1,id);tim[id]=-1;
		}
	}
	for(int i=1;i<=k;i++)if(tim[i]!=-1)updata(1,0,q,tim[i],q,i);
	dfs(1,0,q);
	for(int i=0;i<=q;i++)printf("%lld ",res[i]);
}

bool med;
signed main(){
	// freopen(".in","r",stdin);
	// freopen(".out","w",stdout);
	
	cerr<<(&mbe-&med)/1024.0/1024.0<<"\n";
	
	read();int T=1;
	while(T--)work();
}