// Problem: P2572 [SCOI2010] 序列操作
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P2572
// Memory Limit: 128 MB
// Time Limit: 1000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

#include<bits/stdc++.h>
#define int long long
#define mod 998244353
#define pii pair<int,int>
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
struct node{
	int sum0,sum1,lmx0,lmx1,rmx0,rmx1,mx0,mx1;
};
namespace sgt{
	#define mid (l+r>>1)
	#define ls nd<<1
	#define rs nd<<1|1
	node tree[maxn<<2];
	int tag[maxn<<2],cov[maxn<<2];
	node merge(node u,node v){
		return {u.sum0+v.sum0,u.sum1+v.sum1,u.lmx0+(!u.sum1)*v.lmx0,u.lmx1+(!u.sum0)*v.lmx1,v.rmx0+(!v.sum1)*u.rmx0,v.rmx1+(!v.sum0)*u.rmx1,max({u.mx0,v.mx0,u.rmx0+v.lmx0}),max({u.mx1,v.mx1,u.rmx1+v.lmx1})};
	}
	void build(int nd,int l,int r){
		cov[nd]=-1;
		if(l==r){
			tree[nd]={!a[l],a[l],!a[l],a[l],!a[l],a[l],!a[l],a[l]};
			return ;
		}
		build(ls,l,mid),build(rs,mid+1,r);
		tree[nd]=merge(tree[ls],tree[rs]);
		// cout<<nd<<" "<<l<<" "<<r<<" "<<tree[nd].sum1<<" "<<tree[nd].mx1<<" "<<tree[nd].lmx1<<" "<<tree[nd].rmx1<<"\n";
	}
	void push(int nd,int l,int r){
		if(~cov[nd]){
			if(!cov[nd]){
				tag[ls]=0;tree[ls]={mid-l+1,0,mid-l+1,0,mid-l+1,0,mid-l+1,0};cov[ls]=cov[nd];
				tag[rs]=0;tree[rs]={r-mid,0,r-mid,0,r-mid,0,r-mid,0};cov[rs]=cov[nd];
			}
			else{
				tag[ls]=0;tree[ls]={0,mid-l+1,0,mid-l+1,0,mid-l+1,0,mid-l+1};cov[ls]=cov[nd];
				tag[rs]=0;tree[rs]={0,r-mid,0,r-mid,0,r-mid,0,r-mid};cov[rs]=cov[nd];
			}
		}
		if(tag[nd]){
			tree[ls]={tree[ls].sum1,tree[ls].sum0,tree[ls].lmx1,tree[ls].lmx0,tree[ls].rmx1,tree[ls].rmx0,tree[ls].mx1,tree[ls].mx0};tag[ls]^=1;
			tree[rs]={tree[rs].sum1,tree[rs].sum0,tree[rs].lmx1,tree[rs].lmx0,tree[rs].rmx1,tree[rs].rmx0,tree[rs].mx1,tree[rs].mx0};tag[rs]^=1;
		}
		cov[nd]=-1;tag[nd]=0;
	}
	void updata(int nd,int l,int r,int ql,int qr,int w){
		if(l>=ql&&r<=qr){
			if(!w)tree[nd]={r-l+1,0,r-l+1,0,r-l+1,0,r-l+1,0};
			else tree[nd]={0,r-l+1,0,r-l+1,0,r-l+1,0,r-l+1};
			tag[nd]=0;cov[nd]=w;
			return ;
		}
		push(nd,l,r);
		if(ql<=mid)updata(ls,l,mid,ql,qr,w);
		if(qr>mid)updata(rs,mid+1,r,ql,qr,w);
		tree[nd]=merge(tree[ls],tree[rs]);
	}
	void rev(int nd,int l,int r,int ql,int qr){
		if(l>=ql&&r<=qr){
			tree[nd]={tree[nd].sum1,tree[nd].sum0,tree[nd].lmx1,tree[nd].lmx0,tree[nd].rmx1,tree[nd].rmx0,tree[nd].mx1,tree[nd].mx0};
			tag[nd]^=1;
			return ;
		}
		push(nd,l,r);
		if(ql<=mid)rev(ls,l,mid,ql,qr);
		if(qr>mid)rev(rs,mid+1,r,ql,qr);
		tree[nd]=merge(tree[ls],tree[rs]);
		// cout<<nd<<" "<<l<<" "<<r<<" "<<tree[nd].sum1<<" "<<tree[nd].mx1<<" "<<tree[ls].rmx1<<" "<<tree[rs].lmx1<<"\n";
	}
	node query(int nd,int l,int r,int ql,int qr){
		if(l>=ql&&r<=qr)return tree[nd];
		push(nd,l,r);
		if(qr<=mid)return query(ls,l,mid,ql,qr);
		if(ql>mid)return query(rs,mid+1,r,ql,qr);
		return merge(query(ls,l,mid,ql,qr),query(rs,mid+1,r,ql,qr));
	}
}
void work(){
	n=read();m=read();
	for(int i=1;i<=n;i++)a[i]=read();
	sgt::build(1,1,n);
	while(m--){
		int op=read(),u=read()+1,v=read()+1;
		if(op==0)sgt::updata(1,1,n,u,v,0);
		if(op==1)sgt::updata(1,1,n,u,v,1);
		if(op==2)sgt::rev(1,1,n,u,v);
		if(op==3){
			node res=sgt::query(1,1,n,u,v);
			printf("%lld\n",res.sum1);
		}
		if(op==4){
			node res=sgt::query(1,1,n,u,v);
			printf("%lld\n",res.mx1);
		}
		// for(int i=1;i<=n;i++)cout<<sgt::query(1,1,n,i,i).sum1<<" ";cout<<"\n";
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
