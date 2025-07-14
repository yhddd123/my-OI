#include<bits/stdc++.h>
#define int long long
#define db double
#define mod 1000000007
using namespace std;
const int maxn=100010;
const int inf=1e9;
const db eps=1e-9;
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch-48);ch=getchar();}
	return x*f;
}

int n,a[maxn],m,b[maxn],p;
int opt[maxn],x[maxn],y[maxn];
#define mid (l+r>>1)
#define ls nd<<1
#define rs nd<<1|1
int tree[maxn<<2],tag[maxn<<2];
void build(int nd,int l,int r){
	tag[nd]=-1;
	if(l==r){
		tree[nd]=(b[l]==1);
		return ;
	}
	build(ls,l,mid);build(rs,mid+1,r);
	tree[nd]=tree[ls]+tree[rs];
}
void push(int nd,int l,int r){
	tree[ls]=(mid-l+1)*tag[nd];
	tag[ls]=tag[nd];
	tree[rs]=(r-mid)*tag[nd];
	tag[rs]=tag[nd];
	tag[nd]=-1;
}
void updata(int nd,int l,int r,int ql,int qr,int w){
	if(ql>qr)return ;
	if(l>=ql&&r<=qr){
		tree[nd]=w*(r-l+1);
		tag[nd]=w;
		return ;
	}
	if(tag[nd]!=-1)push(nd,l,r);
	if(ql<=mid)updata(ls,l,mid,ql,qr,w);
	if(qr>mid)updata(rs,mid+1,r,ql,qr,w);
	tree[nd]=tree[ls]+tree[rs];
}
int query(int nd,int l,int r,int ql,int qr){
	if(l>=ql&&r<=qr)return tree[nd];
	if(tag[nd]!=-1)push(nd,l,r);
	if(qr<=mid)return query(ls,l,mid,ql,qr);
	if(ql>mid)return query(rs,mid+1,r,ql,qr);
	return query(ls,l,mid,ql,qr)+query(rs,mid+1,r,ql,qr);
}
bool check(int v){
	for(int i=1;i<=n;i++)b[i]=(a[i]>=v);
	build(1,1,n);
	for(int i=1;i<=m;i++){
		int num=query(1,1,n,x[i],y[i]);
		if(opt[i]==1)updata(1,1,n,x[i],x[i]+num-1,1),updata(1,1,n,x[i]+num,y[i],0);
		else updata(1,1,n,y[i]-num+1,y[i],1),updata(1,1,n,x[i],y[i]-num,0);
	}
	return query(1,1,n,p,p);
}
void work(){
	n=read();m=read();
	for(int i=1;i<=n;i++)a[i]=read();
	for(int i=1;i<=m;i++)opt[i]=read(),x[i]=read(),y[i]=read();
	p=read();
	int l=1,r=n,ans;
	while(l<=r){
		if(check(mid)){
			ans=mid;
			l=mid+1;
		}
		else r=mid-1;
	}
	printf("%lld\n",ans);
}

int T;
signed main(){
	//	freopen(".in","r",stdin);
	//	freopen(".out","w",stdout);
	
	T=1;
	while(T--)work();
}
