#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int MAXN=400005;
vector<int>ve[MAXN];
int fa[MAXN],n,k,m,X[MAXN],val[MAXN],lst[MAXN],son[MAXN],dep[MAXN],siz[MAXN],top[MAXN],tcnt,dfn[MAXN],pid[MAXN];
vector<int>vec[MAXN];
ll ans[MAXN];
void dfs1(int u) {
	siz[u]=1;
	for(int v:ve[u]) {
		dep[v]=dep[u]+1;
		dfs1(v);
		siz[u]+=siz[v];
		if(siz[v]>siz[son[u]])son[u]=v;
	}
}
void dfs2(int u,int tp) {
	top[u]=tp,dfn[u]=++tcnt,pid[tcnt]=u;
	if(son[u]) dfs2(son[u],tp);
	for(int v:ve[u])
		if(v^son[u])
			dfs2(v,v);
}
struct Tree {
	int l,r,mn,lt;//mn:[l,r]中size(u)-s(u)最小值，lt：懒标记
	pair<int,int>mx;//mx:[l,r]中的人(u,v)的-v的最大值和初始节点
} tr[MAXN];
multiset<int>st[MAXN];
void build(int num,int l,int r) {
	tr[num].l=l,tr[num].r=r,tr[num].mx=make_pair(0,r);//初始有人(u,0)
	if(l==r) return;
	build(num<<1,l,l+r>>1),build(num<<1|1,(l+r>>1)+1,r);
}
void updatemx(int num,int x,int v) {
	if(tr[num].l==tr[num].r) {
		tr[num].mx=make_pair(v,x);
		return;
	}
	updatemx(num<<1|(x>tr[num<<1].r),x,v);
	tr[num].mx=max(tr[num<<1].mx,tr[num<<1|1].mx);
}
pair<int,int> querymx(int num,int l,int r) {
	if(l<=tr[num].l&&tr[num].r<=r) return tr[num].mx;
	if(r<=tr[num<<1].r) return querymx(num<<1,l,r);
	if(tr[num<<1|1].l<=l) return querymx(num<<1|1,l,r);
	return max(querymx(num<<1,l,r),querymx(num<<1|1,l,r));
}
inline void upd(int num,int x) {
	tr[num].mn+=x,tr[num].lt+=x;
}
inline void push_down(int num) {
	if(!tr[num].lt) return;
	upd(num<<1,tr[num].lt),upd(num<<1|1,tr[num].lt);
	tr[num].lt=0;
}
void update(int num,int l,int r,int x) {
	if(l<=tr[num].l&&tr[num].r<=r) return upd(num,x);
	push_down(num);
	if(l<=tr[num<<1].r) update(num<<1,l,r,x);
	if(tr[num<<1|1].l<=r) update(num<<1|1,l,r,x);
	tr[num].mn=min(tr[num<<1].mn,tr[num<<1|1].mn);
}
int Findz(int num) {
	if(tr[num].l==tr[num].r) return tr[num].l;
	return push_down(num),Findz(num<<1|(!tr[num<<1|1].mn));
}
int query(int num,int l,int r) {
	if(l<=tr[num].l&&tr[num].r<=r) {
		return tr[num].mn?-1:Findz(num);
	}
	push_down(num);
	if(r<=tr[num<<1].r) return query(num<<1,l,r);
	if(tr[num<<1|1].l<=l) return query(num<<1|1,l,r);
	int res=query(num<<1|1,l,r);
	if(~res) return res;
	else return query(num<<1,l,r);
}
inline void upRange(int u,int v) {
	for(; top[u]; u=fa[top[u]]) 
		update(1,dfn[top[u]],dfn[u],v);
}
void Add(int num,int l,int r,int L,int R,int x) {
	if(L<=l&&r<=R) {
		vec[num].push_back(x);
		return;
	}
	if(L<=(l+r>>1)) Add(num<<1,l,l+r>>1,L,R,x);
	if(R> (l+r>>1)) Add(num<<1|1,(l+r>>1)+1,r,L,R,x);
}
int qry(int u) {
	int res=query(1,dfn[top[u]],dfn[u]);
	return ~res?pid[res]:qry(fa[top[u]]);
}
inline void add(int u,int v) {//答案集合加入人(u,v)
	st[u].insert(v);
	updatemx(1,dfn[u],*st[u].rbegin());
	upRange(u,-1);
}
inline void del(int u,int v) {//答案集合删去人(u,v)
	st[u].erase(st[u].lower_bound(v));
	updatemx(1,dfn[u],st[u].empty()?-0x3f3f3f3f:*st[u].rbegin());
	upRange(u,1);
}
struct node {
	int x,xv,y,yv;
};
ll res;
void solve(int num,int l,int r) {
	vector<node>vt;
	for(int v:vec[num]) {
		int u=qry(X[v]);
		pair<int,int>tmp=querymx(1,dfn[u],dfn[u]+siz[u]-1);
		if(tmp.first+val[v]>0) {
			vt.push_back(node{X[v],val[v],tmp.second,tmp.first});
			res+=tmp.first+val[v];
			del(pid[tmp.second],tmp.first);
			add(X[v],-val[v]);
		}
	}
	if(l==r) ans[l]=res;
	else {
		int mid=l+r>>1;
		solve(num<<1,l,mid),solve(num<<1|1,mid+1,r);
	}
	for(node z; !vt.empty(); vt.pop_back()) {
		z=vt.back();
		res-=z.xv+z.yv;
		del(z.x,-z.xv),add(pid[z.y],z.yv);
	}
}
int main() {
	scanf("%*d%d%d%d",&n,&k,&m);
	for(int i=1; i<=n; ++i)st[i].insert(0); //初始有人(u,0)
	for(int i=2; i<=n; ++i)scanf("%d",&fa[i]),ve[fa[i]].push_back(i);
	for(int i=1; i<=k; ++i) scanf("%d%d",&X[i],&val[i]);
	for(int i=1,op=0,x=0; i<=m; ++i) {
		scanf("%d",&op);
		if(op==1) {
			++k,lst[k]=i,scanf("%d%d",&X[k],&val[k]);
		} else {
			scanf("%d",&x),Add(1,0,m,lst[x],i-1,x),lst[x]=m+1;
		}
	}
	for(int i=1; i<=k; ++i)
		if(lst[i]<=m)
			Add(1,0,m,lst[i],m,i);
	dfs1(1),dfs2(1,1),build(1,1,n);
	solve(1,0,m);
	for(int i=0; i<=m; ++i) printf("%lld ",ans[i]);
	return 0;
} 
