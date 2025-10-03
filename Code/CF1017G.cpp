// Problem: CF1017G The Tree
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/CF1017G
// Memory Limit: 250 MB
// Time Limit: 3000 ms
// Written by yhm.
// Start codeing:2025-10-03 14:27:06
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
const int maxn=200010;
const int inf=1e9;
bool mbe;

int n,q;
int head[maxn],tot;
struct nd{
    int nxt,to;
}e[maxn<<1];
void add(int u,int v){e[++tot]={head[u],v};head[u]=tot;}
int fa[maxn],dep[maxn],siz[maxn],son[maxn];
void dfs(int u){
    dep[u]=dep[fa[u]]+1,siz[u]=1,son[u]=0;
    for(int i=head[u];i;i=e[i].nxt){
        int v=e[i].to;if(v==fa[u])continue;
        fa[v]=u;dfs(v),siz[u]+=siz[v];
        if(siz[v]>=siz[son[u]])son[u]=v;
    }
}
int dfn[maxn],rnk[maxn],idx,tp[maxn];
void dfs(int u,int lst){
    rnk[dfn[u]=++idx]=u;tp[u]=lst;
    if(!son[u])return ;dfs(son[u],lst);
    for(int i=head[u];i;i=e[i].nxt){
        int v=e[i].to;if(v==fa[u]||v==son[u])continue;
        dfs(v,v);
    }
}
#define mid ((l+r)>>1)
#define ls nd<<1
#define rs nd<<1|1
struct node{
	int sum,mx;
}tree[maxn<<2];
node operator+(node u,node v){return {u.sum+v.sum,max(u.mx+v.sum,v.mx)};}
int len[maxn<<2];
bool tag[maxn<<2];
void build(int nd,int l,int r){
	len[nd]=r-l+1;tree[nd]={-len[nd],-1};
    if(l==r)return ;
    build(ls,l,mid),build(rs,mid+1,r);
}
void upd(int nd){tree[nd].sum=-len[nd],tree[nd].mx=-1;tag[nd]=1;}
void down(int nd){upd(ls),upd(rs),tag[nd]=0;}
void updata(int nd,int l,int r,int ql,int qr){
    if(ql>qr)return ;
    if(l>=ql&&r<=qr)return upd(nd);
    if(tag[nd])down(nd);
    if(ql<=mid)updata(ls,l,mid,ql,qr);
    if(qr>mid)updata(rs,mid+1,r,ql,qr);
    tree[nd]=tree[ls]+tree[rs];
}
void modif(int nd,int l,int r,int p,int w){
    if(l==r){tree[nd].sum+=w,tree[nd].mx+=w;return ;}
    if(tag[nd])down(nd);
    if(p<=mid)modif(ls,l,mid,p,w);
    else modif(rs,mid+1,r,p,w);
    tree[nd]=tree[ls]+tree[rs];
}
node query(int nd,int l,int r,int ql,int qr){
    if(l>=ql&&r<=qr)return tree[nd];
    if(tag[nd])down(nd);
    if(qr<=mid)return query(ls,l,mid,ql,qr);
    if(ql>mid)return query(rs,mid+1,r,ql,qr);
    return query(ls,l,mid,ql,qr)+query(rs,mid+1,r,ql,qr);
}
int que(int u){
	node res={0,-1};
	while(u){
		res=query(1,1,n,dfn[tp[u]],dfn[u])+res;
		u=fa[tp[u]];
	}
	return res.mx;
}
void work(){
	n=read();q=read();
	for(int i=2;i<=n;i++)add(read(),i);
	dfs(1),dfs(1,1);
	build(1,1,n);
	while(q--){
		int op=read(),u=read();
		if(op==1)modif(1,1,n,dfn[u],1);
		if(op==2){
			updata(1,1,n,dfn[u]+1,dfn[u]+siz[u]-1);
			int v=que(u);
			if(v>=0)modif(1,1,n,dfn[u],-v-1);
		}
		if(op==3){
			int v=que(u);
			if(v>=0)puts("black");
			else puts("white");
		}
		// cout<<tree[1].mx<<"\n";
	}
}

bool med;
int T;
signed main(){
	// freopen(".in","r",stdin);
	// freopen(".out","w",stdout);
	
	// cerr<<(&mbe-&med)/1024.0/1024.0<<"\n";
	
	T=1;
	while(T--)work();
}