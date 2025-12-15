// Problem: P11994 [JOIST 2025] 外郎糕 / Uiro
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P11994
// Memory Limit: 1024 MB
// Time Limit: 5000 ms
// Written by yhm.
// Start codeing:2025-12-15 22:30:01
// 
// Powered by CP Editor (https://cpeditor.org)

#include<bits/stdc++.h>
// #define int long long
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
const int maxn=2000010;
const int inf=1e9;
bool mbe;

#define mid ((l+r)>>1)
#define ls lc[nd]
#define rs rc[nd]
int tree[maxn<<5],lc[maxn<<5],rc[maxn<<6],rt[maxn],idx;
int st[maxn<<5],tp;
void newnode(int &nd){
	nd=tp?st[tp--]:++idx;
}
void del(int nd){
	ls=rs=tree[nd]=0;st[++tp]=nd;
}
void updata(int &nd,int l,int r,int p,int w){
	if(!nd)newnode(nd);tree[nd]+=w;
	if(l==r)return ;
	if(p<=mid)updata(ls,l,mid,p,w);
	else updata(rs,mid+1,r,p,w);
}
int query(int nd,int l,int r,int ql,int qr){
	// cout<<nd<<" "<<ls<<" "<<rs<<" "<<tree[nd]<<" "<<ql<<" "<<qr<<" q\n";
	if(!nd||(l>=ql&&r<=qr))return tree[nd];
	if(qr<=mid)return query(ls,l,mid,ql,qr);
	if(ql>mid)return query(rs,mid+1,r,ql,qr);
	return query(ls,l,mid,ql,qr)+query(rs,mid+1,r,ql,qr);
}
int merge(int u,int v,int l,int r){
	if(!u||!v)return u|v;
	if(l==r){
		tree[u]+=tree[v];del(v);
		return u;
	}
	lc[u]=merge(lc[u],lc[v],l,mid),rc[u]=merge(rc[u],rc[v],mid+1,r);
	tree[u]=tree[lc[u]]+tree[rc[u]];del(v);
	return u;
}
int n,q,a[maxn];
int head[maxn],tot;
struct nd{
	int nxt,to;
}e[maxn];
void add(int u,int v){e[++tot]={head[u],v};head[u]=tot;}
int dfn[maxn],rnk[maxn],tim,siz[maxn],dep[maxn];
void dfs(int u,int fa){
	rnk[dfn[u]=++tim]=fa;siz[u]=1;dep[u]=dep[fa]+1;
	for(int i=head[u];i;i=e[i].nxt){
		int v=e[i].to;
		dfs(v,u),siz[u]+=siz[v];
	}
}
void work(){
	n=read();
	for(int i=2;i<=n;i++)add(read(),i);
	for(int i=1;i<=n;i++)a[i]=read();
	dep[0]=-1;dfs(1,0);
	for(int i=1;i<=n;i++)updata(rt[dep[i]],1,n,dfn[i],a[i]);
	q=read();
	while(q--){
		int op=read();
		if(op==1){
			int y=read(),x=read();
			rt[x]=merge(rt[x],rt[y],1,n),rt[y]=0;
			// cout<<rt[x]<<" "<<rt[y]<<" "<<tree[rt[x]]<<"\n";
		}
		if(op==2){
			int u=read(),w=read();
			updata(rt[dep[u]],1,n,dfn[u],w);
		}
		if(op==3){
			int u=read();
			printf("%d\n",query(rt[dep[u]],1,n,dfn[u],dfn[u]+siz[u]-1));
		}
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