#include<bits/stdc++.h>
#define int long long
#define mod 1000000007
using namespace std;
const int maxn=100010;
const int inf=1e9;
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch-48);ch=getchar();}
	return x*f;
}

int n,a[maxn],m;
int tree[maxn<<2],mx[maxn<<2];
void build(int nd,int l,int r){
	if(l==r){
		tree[nd]=a[l];
		mx[nd]=a[l];
		return ;
	}
	int mid=l+r>>1,ls=nd<<1,rs=nd<<1|1;
	build(ls,l,mid);build(rs,mid+1,r);
	tree[nd]=tree[ls]+tree[rs];
	mx[nd]=max(mx[ls],mx[rs]);
}
void updata(int nd,int l,int r,int ql,int qr){
	if(mx[nd]==1)return ;
	if(l==r){
		mx[nd]=tree[nd]=sqrt(tree[nd]);
		return ;
	}
	int mid=l+r>>1,ls=nd<<1,rs=nd<<1|1;
	if(ql<=mid)updata(ls,l,mid,ql,qr);
	if(qr>mid)updata(rs,mid+1,r,ql,qr);
	tree[nd]=tree[ls]+tree[rs];
	mx[nd]=max(mx[ls],mx[rs]);
}
int query(int nd,int l,int r,int ql,int qr){
	if(l>=ql&&r<=qr)return tree[nd];
	int mid=l+r>>1,ls=nd<<1,rs=nd<<1|1;
	if(qr<=mid)return query(ls,l,mid,ql,qr);
	if(ql>mid)return query(rs,mid+1,r,ql,qr);
	return query(ls,l,mid,ql,qr)+query(rs,mid+1,r,ql,qr);
}
int opt,l,r;

int T;
signed main(){
	//	freopen(".in","r",stdin);
	//	freopen(".out","w",stdout);
	
	n=read();
	for(int i=1;i<=n;i++)a[i]=read();
	build(1,1,n);
	m=read();
	while(m--){
		opt=read();l=read();r=read();
		if(l>r)swap(l,r);
		if(!opt)updata(1,1,n,l,r);
		else printf("%lld\n",query(1,1,n,l,r));
	}
}
