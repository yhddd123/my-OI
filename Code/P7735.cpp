// Problem: P7735 [NOI2021] 轻重边
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P7735
// Memory Limit: 1 MB
// Time Limit: 1000 ms
// Written by yhm.
// Start codeing:2025-05-14 21:53:09
// 
// Powered by CP Editor (https://cpeditor.org)

#include<bits/stdc++.h>
// #define int long long
#define mod 998244353ll
#define pii pair<int,int>
#define fi first
#define se second
#define pb push_back
#define mkp make_pair
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

int n,q;
int head[maxn],tot;
struct nd{
	int nxt,to;
}e[maxn<<1];
void add(int u,int v){e[++tot]={head[u],v};head[u]=tot;}
#define mid (l+r>>1)
#define ls nd<<1
#define rs nd<<1|1
struct node{
	int num,vl,vr;
}tree[maxn<<2];
int tag[maxn<<2],len[maxn<<2];
node operator+(node u,node v){return {u.num+v.num+(u.vr==v.vl),u.vl,v.vr};}
void build(int nd,int l,int r){
	tree[nd]={0,l,r};tag[nd]=0;len[nd]=r-l+1;
	if(l==r)return ;
	build(ls,l,mid),build(rs,mid+1,r);
}
void upd(int nd,int w){
	tree[nd]={len[nd]-1,w,w},tag[nd]=w;
}
void down(int nd){
	upd(ls,tag[nd]),upd(rs,tag[nd]),tag[nd]=0;
}
void updata(int nd,int l,int r,int ql,int qr,int w){
	if(l>=ql&&r<=qr)return upd(nd,w);
	if(tag[nd])down(nd);
	if(ql<=mid)updata(ls,l,mid,ql,qr,w);
	if(qr>mid)updata(rs,mid+1,r,ql,qr,w);
	tree[nd]=tree[ls]+tree[rs];
}
node query(int nd,int l,int r,int ql,int qr){
	if(l>=ql&&r<=qr)return tree[nd];
	if(tag[nd])down(nd);
	if(qr<=mid)return query(ls,l,mid,ql,qr);
	if(ql>mid)return query(rs,mid+1,r,ql,qr);
	return query(ls,l,mid,ql,qr)+query(rs,mid+1,r,ql,qr);
}
int fa[maxn],dep[maxn],siz[maxn],son[maxn];
void dfs(int u){
	siz[u]=1,son[u]=0;dep[u]=dep[fa[u]]+1;
	for(int i=head[u];i;i=e[i].nxt){
		int v=e[i].to;if(v==fa[u])continue;
		fa[v]=u;dfs(v);siz[u]+=siz[v];
		if(siz[v]>=siz[son[u]])son[u]=v;
	}
}
int dfn[maxn],rnk[maxn],idx,tp[maxn];
void dfs(int u,int lst){
	rnk[dfn[u]=++idx]=u,tp[u]=lst;
	if(!son[u])return ;dfs(son[u],lst);
	for(int i=head[u];i;i=e[i].nxt){
		int v=e[i].to;if(v==fa[u]||v==son[u])continue;
		dfs(v,v);
	}
}
void upd(int u,int v,int w){
	while(tp[u]!=tp[v]){
		if(dep[tp[u]]<dep[tp[v]])swap(u,v);
		updata(1,1,n,dfn[tp[u]],dfn[u],w);
		u=fa[tp[u]];
	}
	if(dep[u]<dep[v])swap(u,v);
	updata(1,1,n,dfn[v],dfn[u],w);
}
int que(int u,int v){
	vector<node> up,dw;
	while(tp[u]!=tp[v]){
		if(dep[tp[u]]<dep[tp[v]])swap(u,v),swap(up,dw);
		up.pb(query(1,1,n,dfn[tp[u]],dfn[u]));
		u=fa[tp[u]];
	}
	if(dep[u]<dep[v])swap(u,v),swap(up,dw);
	up.pb(query(1,1,n,dfn[v],dfn[u]));
	node ans={0,0,0};
	for(auto p:up)ans=p+ans;
	reverse(dw.begin(),dw.end());
	for(auto&p:dw)swap(p.vl,p.vr);
	for(auto p:dw)ans=p+ans;
	return ans.num;
}
void work(){
	n=read();q=read();
	for(int i=1;i<=n;i++)head[i]=0;tot=0;
	for(int i=1;i<n;i++){
		int u=read(),v=read();
		add(u,v),add(v,u);
	}
	idx=0;dfs(1),dfs(1,1);
	build(1,1,n);
	int tim=n;
	while(q--){
		int op=read(),u=read(),v=read();
		if(op==1)upd(u,v,++tim);
		else printf("%d\n",que(u,v));
	}
}

bool med;
int T;
signed main(){
	// freopen(".in","r",stdin);
	// freopen(".out","w",stdout);
	
	// cerr<<(&mbe-&med)/1024.0/1024.0<<"\n";
	
	T=read();
	while(T--)work();
}