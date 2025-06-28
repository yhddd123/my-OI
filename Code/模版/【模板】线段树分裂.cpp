// Problem: P5494 【模板】线段树分裂
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P5494
// Memory Limit: 128 MB
// Time Limit: 1000 ms
// Written by yhm.
// Start codeing:2024-11-20 17:04:11
// 
// Powered by CP Editor (https://cpeditor.org)

#include<bits/stdc++.h>
#define ll long long
#define mod 998244353ll
#define pii pair<int,int>
#define fi first
#define se second
#define mems(x,y) memset(x,y,sizeof(x))
#define pb push_back
#define db double
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

int n,q;
int a[maxn];
int rt[maxn],cnt;
#define mid (l+r>>1)
#define ls lc[nd]
#define rs rc[nd]
ll tree[maxn<<5];
int lc[maxn<<5],rc[maxn<<5],idx;
int st[maxn<<5],tp;
int newnode(){
	if(tp)return st[tp--];
	return ++idx;
}
void clr(int nd){
	tree[nd]=0,ls=rs=0;
	st[++tp]=nd;
}
void updata(int &nd,int l,int r,int p,int w){
	if(!nd)nd=newnode();
	tree[nd]+=w;
	if(l==r)return ;
	if(p<=mid)updata(ls,l,mid,p,w);
	else updata(rs,mid+1,r,p,w);
	tree[nd]=tree[ls]+tree[rs];
}
ll query(int nd,int l,int r,int ql,int qr){
	if(!nd||ql>qr)return 0;
	if(l>=ql&&r<=qr)return tree[nd];
	if(qr<=mid)return query(ls,l,mid,ql,qr);
	if(ql>mid)return query(rs,mid+1,r,ql,qr);
	return query(ls,l,mid,ql,qr)+query(rs,mid+1,r,ql,qr);
}
int fdkth(int nd,int l,int r,ll k){
	if(tree[nd]<k)return -1;
	if(l==r)return l;
	if(tree[ls]>=k)return fdkth(ls,l,mid,k);
	return fdkth(rs,mid+1,r,k-tree[ls]);
}
int merge(int u,int v,int l,int r){
	if(!u||!v)return u|v;
	if(l==r){tree[u]+=tree[v];clr(v);return u;}
	lc[u]=merge(lc[u],lc[v],l,mid);
	rc[u]=merge(rc[u],rc[v],mid+1,r);
	tree[u]=tree[lc[u]]+tree[rc[u]];clr(v);
	return u;
}
int split(int nd,int l,int r,ll k){
	if(!nd)return 0;
	int u=newnode();
	if(k>tree[ls])rc[u]=split(rs,mid+1,r,k-tree[ls]);
	else rc[u]=rs,rs=0;
	if(k<tree[ls])lc[u]=split(ls,l,mid,k);
	tree[nd]=tree[ls]+tree[rs],tree[u]=tree[lc[u]]+tree[rc[u]];
	return u;
}
void work(){
	n=read();q=read();cnt=1;
	for(int i=1;i<=n;i++)updata(rt[1],1,n,i,read());
	while(q--){
		int op=read();
		if(op==0){
			int p=read(),l=read(),r=read();
			ll v1=query(rt[p],1,n,1,l-1),v2=query(rt[p],1,n,l,r);
			// cout<<v1<<" "<<v2<<endl;
			rt[++cnt]=split(rt[p],1,n,v1);
			int nwrt=split(rt[cnt],1,n,v2);
			rt[p]=merge(rt[p],nwrt,1,n);
		}
		if(op==1){
			int u=read(),v=read();
			rt[u]=merge(rt[u],rt[v],1,n);
		}
		if(op==2){
			int p=read(),x=read(),v=read();
			updata(rt[p],1,n,v,x);
		}
		if(op==3){
			int p=read(),l=read(),r=read();
			printf("%lld\n",query(rt[p],1,n,l,r));
		}
		if(op==4){
			int p=read(),k=read();
			printf("%d\n",fdkth(rt[p],1,n,k));
		}
		// cout<<tree[rt[1]]<<" "<<tree[rt[2]]<<" a\n";
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
	
	// cerr<<(&Mbe-&Med)/1048576.0<<" MB\n";
	
	T=1;
	while(T--)work();
}
