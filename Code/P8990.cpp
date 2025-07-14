// Problem: P8990 [北大集训 2021] 小明的树
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P8990
// Memory Limit: 512 MB
// Time Limit: 3000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

#include<bits/stdc++.h>
#define int long long
#define mod 998244353
#define pii pair<int,int>
using namespace std;
const int maxn=500010;
const int inf=1e18;
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch-48);ch=getchar();}
	return x*f;
}
bool Mbe;

int n,q,a[maxn];
pii e[maxn];
namespace sgt{
	#define mid (l+r>>1)
	#define ls nd<<1
	#define rs nd<<1|1
	struct nd{
		int mn,num,sum;
	}tree[maxn<<2];
	int tagx[maxn<<2],tagv[maxn<<2];
	nd merge(nd u,nd v){
		if(u.mn<v.mn)return u;
		if(u.mn>v.mn)return v;
		return {u.mn,u.num+v.num,u.sum+v.sum};
	}
	void build(int nd,int l=1,int r=n-1){
		if(l==r){
			tree[nd]={n-l,1,0};
			return ;
		}
		build(ls,l,mid),build(rs,mid+1,r);
		tree[nd]=merge(tree[ls],tree[rs]);
	}
	void addx(int nd,int w){tree[nd].mn+=w,tagx[nd]+=w;}
	void addv(int nd,int w){tree[nd].sum+=w*tree[nd].num,tagv[nd]+=w;}
	void push(int nd){
		if(tagx[nd]){
			addx(ls,tagx[nd]),addx(rs,tagx[nd]);
			tagx[nd]=0;
		}
		if(tagv[nd]){
			addv(ls,tagv[nd]),addv(rs,tagv[nd]);
			tagv[nd]=0;
		}
	}
	void updatax(int nd,int ql,int qr,int w,int l=1,int r=n-1){
		if(l>=ql&&r<=qr){
			addx(nd,w);
			return ;
		}
		push(nd);
		if(ql<=mid)updatax(ls,ql,qr,w,l,mid);
		if(qr>mid)updatax(rs,ql,qr,w,mid+1,r);
		tree[nd]=merge(tree[ls],tree[rs]);
	}
	void updatav(int nd,int ql,int qr,int w,int l=1,int r=n-1){
		if(l>=ql&&r<=qr){
			addv(nd,w);
			return ;
		}
		push(nd);
		if(ql<=mid)updatav(ls,ql,qr,w,l,mid);
		if(qr>mid)updatav(rs,ql,qr,w,mid+1,r);
		tree[nd]=merge(tree[ls],tree[rs]);
	}
}
void upd(int u,int v,int w){
	if(a[u]>a[v])swap(u,v);
	sgt::updatax(1,a[u],n-1,w);
	sgt::updatav(1,a[u],a[v]-1,w);
}
void work(){
	n=read();q=read();
	for(int i=1;i<n;i++)e[i]={read(),read()};
	for(int i=2;i<=n;i++)a[read()]=i-1;a[1]=n;
	sgt::build(1);
	for(int i=1;i<n;i++)upd(e[i].first,e[i].second,1);
	printf("%lld\n",sgt::tree[1].sum);
	while(q--){
		int u=read(),v=read(),x=read(),y=read();
		if(a[u]>a[v])swap(u,v);upd(u,v,-1);
		if(a[x]>a[y])swap(x,y);upd(x,y,1);
		printf("%lld\n",sgt::tree[1].sum);
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
