#include<bits/stdc++.h>
#define int long long
#define mod 1000000007
using namespace std;
const int maxn=200010;
const int inf=1e9;
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch-48);ch=getchar();}
	return x*f;
}

int n,m,z,q,s;
int a[maxn],b[maxn];
struct ask{
	int l,r,id;
}p[maxn];
bool cmp(ask u,ask v){
	if(u.l/s==v.l/s){
		if((u.l/s)&1)return u.r<v.r;
		return u.r>v.r;
	}
	return u.l<v.l;
}
int ans[maxn];
int l=1,r;
#define ls nd<<1
#define rs nd<<1|1
#define mid (l+r>>1)
int tree[maxn<<2],sum[maxn<<2];
void updata(int val,int w,int nd=1,int l=1,int r=n){
	if(l==r){
		if(z<val+a[l])return ;
		if(sum[nd]==0)tree[nd]=1;
		sum[nd]+=w;
		if(sum[nd]==0)tree[nd]=0;
		return ;
	}
	if(z<val+a[mid+1])updata(val,w,ls,l,mid);
	else updata(val,w,rs,mid+1,r);
	sum[nd]=sum[ls]+sum[rs];
	tree[nd]=tree[ls]+tree[rs]+min(max(mid-l+1-tree[ls],0ll),sum[rs]-tree[rs]);
}
#undef ls
#undef rs
#undef mid

int T;
signed main(){
	//	freopen(".in","r",stdin);
	//	freopen(".out","w",stdout);
	
	n=read();m=read();z=read();s=sqrt(m);
	for(int i=1;i<=n;i++)a[i]=read();
	for(int i=1;i<=m;i++)b[i]=read();
	sort(a+1,a+n+1);
	q=read();
	for(int i=1;i<=q;i++)p[i]={read(),read(),i};
	sort(p+1,p+q+1,cmp);
	for(int i=1;i<=q;i++){
		while(l>p[i].l)updata(b[--l],1);
		while(r<p[i].r)updata(b[++r],1);
		while(l<p[i].l)updata(b[l++],-1);
		while(r>p[i].r)updata(b[r--],-1);
		ans[p[i].id]=tree[1];
	}
	for(int i=1;i<=q;i++)printf("%lld\n",ans[i]);
}
