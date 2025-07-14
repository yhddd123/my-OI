#include<bits/stdc++.h>
#define ll unsigned long long
#define pii pair<ll,ll>
#define fi first
#define se second
using namespace std;
const int maxn=200010;
static char buf[1000000],*p1=buf,*p2=buf;
#define getchar() p1==p2&&(p2=(p1=buf)+fread(buf,1,1000000,stdin),p1==p2)?EOF:*p1++
inline int read(){int x=0;char c=getchar();while(c<'0'||c>'9')c=getchar();while(c>='0'&&c<='9'){x=(x<<3)+(x<<1)+c-48;c=getchar();}return x;}

int n,m,a[maxn];
int head[maxn],tot;
struct nd{
	int nxt,to;
}e[maxn];
void add(int u,int v){e[++tot]={head[u],v};head[u]=tot;}
int fa[maxn],dep[maxn],siz[maxn],son[maxn];ll sum[maxn];
void dfs(int u){
	siz[u]=1;dep[u]=dep[fa[u]]+1;sum[u]=a[u];
	for(int i=head[u];i;i=e[i].nxt){
		int v=e[i].to;
		dfs(v);siz[u]+=siz[v];sum[u]+=sum[v];
		if(siz[v]>=siz[son[u]])son[u]=v;
	}
}
int dfn[maxn],rnk[maxn],idx,tp[maxn];
int idl[maxn],idr[maxn],st[maxn],ed[maxn];
void dfs(int u,int lst){
	tp[u]=lst;
	if(!son[u])return ;
	st[u]=idx+1;
	rnk[dfn[son[u]]=++idx]=son[u];dfs(son[u],lst);
	idl[u]=idx+1;
	for(int i=head[u];i;i=e[i].nxt){
		int v=e[i].to;if(v==son[u])continue;
		rnk[dfn[v]=++idx]=v;
	}
	idr[u]=idx;
	for(int i=head[u];i;i=e[i].nxt){
		int v=e[i].to;if(v==son[u])continue;
		dfs(v,v);
	}
	ed[u]=idx;
}
#define mid (l+r>>1)
#define ls nd<<1
#define rs nd<<1|1
ll sum2[maxn<<2],sum1[maxn<<2];
ll siz1[maxn<<2],siz2[maxn<<2],mul[maxn<<2];
ll tag[maxn<<2],laz[maxn<<2],len[maxn<<2];
void up(int nd){
	sum2[nd]=sum2[ls]+sum2[rs],sum1[nd]=sum1[ls]+sum1[rs];
	mul[nd]=mul[ls]+mul[rs];
}
void build(int nd,int l,int r){
	if(l==r){
		sum2[nd]=(ll)sum[rnk[l]]*sum[rnk[l]],sum1[nd]=sum[rnk[l]];
		siz2[nd]=(ll)siz[rnk[l]]*siz[rnk[l]],siz1[nd]=siz[rnk[l]];
		mul[nd]=(ll)sum[rnk[l]]*siz[rnk[l]];len[nd]=1;
		return ;
	}
	build(ls,l,mid),build(rs,mid+1,r);
	up(nd);
	siz2[nd]=siz2[ls]+siz2[rs],siz1[nd]=siz1[ls]+siz1[rs];
	len[nd]=len[ls]+len[rs];
}
void upd(int nd,ll w){
	sum2[nd]+=w*w*len[nd]+2*w*sum1[nd],sum1[nd]+=w*len[nd];
	mul[nd]+=w*siz1[nd];
	tag[nd]+=w;
}
void mdf(int nd,ll w){
	sum2[nd]+=w*w*siz2[nd]+2*w*mul[nd],sum1[nd]+=w*siz1[nd];
	mul[nd]+=w*siz2[nd];
	laz[nd]+=w;
}
void down(int nd){
	if(tag[nd])upd(ls,tag[nd]),upd(rs,tag[nd]),tag[nd]=0;
	if(laz[nd])mdf(ls,laz[nd]),mdf(rs,laz[nd]),laz[nd]=0;
}
void updata(int nd,int l,int r,int ql,int qr,ll w){
	if(ql>qr)return ;
	if(l>=ql&&r<=qr){
		upd(nd,w);
		return ;
	}
	down(nd);
	if(ql<=mid)updata(ls,l,mid,ql,qr,w);
	if(qr>mid)updata(rs,mid+1,r,ql,qr,w);
	up(nd);
}
void treeupd(int u,ll w){
	while(u){
		updata(1,1,n,dfn[tp[u]],dfn[tp[u]],w);
		if(tp[u]!=u)updata(1,1,n,dfn[son[tp[u]]],dfn[u],w);
		u=fa[tp[u]];
	}
}
void modif(int nd,int l,int r,int ql,int qr,ll w){
	if(ql>qr)return ;
	if(l>=ql&&r<=qr){
		mdf(nd,w);
		return ;
	}
	down(nd);
	if(ql<=mid)modif(ls,l,mid,ql,qr,w);
	if(qr>mid)modif(rs,mid+1,r,ql,qr,w);
	up(nd);
}
pii query(int nd,int l,int r,int ql,int qr){
	if(ql>qr)return {0,0};
	if(l>=ql&&r<=qr)return {sum2[nd],sum1[nd]};
	down(nd);
	if(qr<=mid)return query(ls,l,mid,ql,qr);
	if(ql>mid)return query(rs,mid+1,r,ql,qr);
	pii u=query(ls,l,mid,ql,qr),v=query(rs,mid+1,r,ql,qr);
	return {u.fi+v.fi,u.se+v.se};	
}
ll query(int u){
	ll ans1=0,ans2=0;
	pii res=query(1,1,n,dfn[u],dfn[u]);
	ans1+=res.fi,ans2+=res.se;
	if(son[u]){
		res=query(1,1,n,dfn[son[u]],dfn[son[u]]);
		ans1-=res.fi,ans2-=res.se;
		if(idl[u]<=idr[u]){
			res=query(1,1,n,idl[u],idr[u]);
			ans1-=res.fi,ans2-=res.se;
		}
	}
	return (ans1-ans2*ans2)/2;
}
char op[3];
void work(){
	n=read();m=read();
	for(int i=2;i<=n;i++){
		fa[i]=read();
		add(fa[i],i);
	}
	for(int i=1;i<=n;i++)a[i]=read();
	dfs(1);rnk[dfn[1]=++idx]=1;dfs(1,1);
	build(1,1,n);
	while(m--){
		char op=getchar();
		while(op!='S'&&op!='M'&&op!='Q')op=getchar();
		if(op=='S'){
			int u=read(),w=read();
			treeupd(u,w);
		}
		if(op=='M'){
			int u=read(),w=read();
			treeupd(u,(ll)w*siz[u]);
			if(siz[u]>1)modif(1,1,n,st[u],ed[u],w);
		}
		if(op=='Q'){
			int u=read();
			printf("%llu\n",query(u));
		}
	}
}

int T;
signed main(){
	T=1;
	while(T--)work();
}