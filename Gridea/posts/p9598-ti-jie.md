---
title: 'P9598 题解'
date: 2025-02-21 14:35:56
tags: [题解,数据结构]
published: true
hideInList: false
feature: 
isTop: false
---
[P9598](https://www.luogu.com.cn/problem/P9598)

比较蠢的做法，原因是分块的对象错完了。

### 思路

加边删边可以线段树分治。只考虑 $[1,p]$ 部分。可以在 $[1,p-1]$ 的图的基础上加入右端点为 $p$ 的边，然后线段树分治回答所有在 $p$ 隔开的询问。同理，如果在 $[1,pl]$ 的图上线段树分治，到一个时间枚举在这个时间且 $p\in [pl,pr]$ 的询问，直接加入小于当前时间且右端点属于 $[pl+1,p]$ 的边，询问，再删除这些边。

所以分块，复杂度取决于右端点属于 $[pl+1,pr]$ 的边的数量和 $[pl,pr]$ 块数。设阈值 $B$，按右端点排序大概 $B$ 条边分成一块。对于当前左端点 $pl$，找到最小 $pr$ 满足右端点属于 $[pl,pr]$ 的边数 $>B$。但如果右端点等于 $pr$ 的边数 $>B$，就分 $[pl,pr)$ 和 $[pr,pr]$。这样可以保证右端点属于 $[pl+1,pr]$ 的边数 $<2\times B$， $[pl,pr]$ 块数 $<2\times \frac{n}{B}$。

对于每一块，都要对之前的边重新线段树分治一遍；对于每个询问，都要遍历块内之前的边。所有的加边删边操作都要可撤销并查集。复杂度 $O(\frac{n}{B}n\log^2 n+mB\log n)$。取 $B=1000$ 跑的飞快。

### code

```cp
int n,m,q,B=1000;
pii upd[maxn],que[maxn];
int ans[maxn];
vector<pii> edge[maxn],qq[maxn],ask[maxn];
int num[maxn];
#define mid (l+r>>1)
#define ls nd<<1
#define rs nd<<1|1
vector<pii> tree[maxn<<2];
int f[maxn],siz[maxn];
int fd(int x){
	if(f[x]==x)return x;
	return fd(f[x]);
}
int st[maxn],tp;
void merge(int u,int v){
	u=fd(u),v=fd(v);
	if(u==v)return ;
	if(siz[u]<siz[v])swap(u,v);
	f[v]=u,siz[u]+=siz[v],st[++tp]=v;
}
void del(){
	int v=st[tp],u=f[v];
	f[v]=v,siz[u]-=siz[v];
	tp--;
}
void build(int nd,int l,int r){
	tree[nd].clear();
	if(l==r)return ;
	build(ls,l,mid),build(rs,mid+1,r);
}
void updata(int nd,int l,int r,int ql,int qr,pii w){
	if(ql>qr)return ;
	if(l>=ql&&r<=qr){tree[nd].pb(w);return ;}
	if(ql<=mid)updata(ls,l,mid,ql,qr,w);
	if(qr>mid)updata(rs,mid+1,r,ql,qr,w);
}
bool vis[maxn<<2];
void modif(int nd,int l,int r,int p){
	vis[nd]=1;
	if(l==r)return ;
	if(p<=mid)modif(ls,l,mid,p);
	else modif(rs,mid+1,r,p);
}
int lst[maxn];
vector<int> pos;
void dfs(int nd,int l,int r){
	if(!vis[nd])return ;vis[nd]=0;
	int tmp=tp;
	for(auto[u,v]:tree[nd])merge(u,v);
	if(l==r){
		for(auto[p,id]:ask[l]){
			int nw=tp;
			for(int i:pos){
				if(i>p)break;
				for(auto[u,t]:edge[i]){
					if(t>l)break;
					lst[u]^=1;
				}
				for(auto[u,t]:edge[i]){
					if(t>l)break;
					if(lst[u])merge(u,i),lst[u]=0;
				}
			}
			ans[id]+=p-tp;
			while(tp>nw)del();
		}
		ask[l].clear();
	}
	else dfs(ls,l,mid),dfs(rs,mid+1,r);
	while(tp>tmp)del();
}
void sovle(){
	for(int i=1;i<=n;i++)edge[i].clear();
	for(int i=1;i<=m;i++){
		auto[u,v]=upd[i];
		if(u>v)swap(u,v);
		edge[v].pb({u,i});
	}
	for(int i=1;i<=n;i++)num[i]=num[i-1]+edge[i].size();
	for(int i=1;i<=n;i++)qq[i].clear();
	for(int i=1;i<=q;i++){
		auto[t,p]=que[i];
		qq[p].pb({t,i});
	}
	for(int i=1;i<=n;i++)f[i]=i,siz[i]=1;
	build(1,1,m);
	for(int l=1,r=1;l<=n;l=r+1,r=l){
		while(r<n&&num[r]-num[l-1]<B)r++;
		if(edge[r].size()>B&&l<r)r--;
		for(auto[u,t]:edge[l]){
			if(lst[u])updata(1,1,m,lst[u],t-1,{u,l}),lst[u]=0;
			else lst[u]=t;
		}
		for(auto[u,t]:edge[l])if(lst[u])updata(1,1,m,lst[u],m,{u,l}),lst[u]=0;
		for(int i=l;i<=r;i++){
			for(auto[t,id]:qq[i])ask[t].pb({i,id}),modif(1,1,m,t);
		}
		pos.clear();for(int i=l+1;i<=r;i++)if(edge[i].size())pos.pb(i);
		dfs(1,1,m);
		for(int i=l+1;i<=r;i++){
			for(auto[u,t]:edge[i]){
				if(lst[u])updata(1,1,m,lst[u],t-1,{u,i}),lst[u]=0;
				else lst[u]=t;
			}
			for(auto[u,t]:edge[i])if(lst[u])updata(1,1,m,lst[u],m,{u,i}),lst[u]=0;
		}
	}
}
void work(){
	n=read();m=read();q=read();
	for(int i=1;i<=m;i++){
		int op=read(),u=read()+1,v=read()+1;
		upd[i]={u,v};
	}
	for(int i=1;i<=q;i++){
		int t=read()+1,p=read()+1;
		que[i]={t,p};
	}
	sovle();
	for(int i=1;i<=m;i++){
		auto[u,v]=upd[i];
		upd[i]={n-u+1,n-v+1};
	}
	for(int i=1;i<=q;i++){
		auto[t,p]=que[i];
		que[i]={t,n-p};
	}
	sovle();
	for(int i=1;i<=q;i++)printf("%d\n",ans[i]);
}
```

