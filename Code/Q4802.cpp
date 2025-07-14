#include<bits/stdc++.h>
#define int long long
#define mod 998244353
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

int n,a[maxn];
int ans[maxn],res;
int b[maxn];
namespace bit{
	int c[maxn];
	void init(){memset(c,0,sizeof(c));}
	int lowbit(int x){return x&(-x);}
	void updata(int x,int w){
		while(x<=n){
			c[x]+=w;
			x+=lowbit(x);
		}
	}
	int query(int x){
		int res=0;
		while(x){
			res+=c[x];
			x-=lowbit(x);
		}
		return res;
	}
}
int l[maxn];
#define pii pair<int,int>
namespace sgt{
	pii tree[maxn<<2];
	int tag[maxn<<2];
	#define mid (l+r>>1)
	#define ls nd<<1
	#define rs nd<<1|1
	void build(int nd,int l,int r){
		tag[nd]=0;
		if(l==r){
			tree[nd]={inf,l};
			return ;
		}
		build(ls,l,mid),build(rs,mid+1,r);
		tree[nd]=min(tree[ls],tree[rs]);
	}
	void push(int nd){
		if(!tag[nd])return ;
		tree[ls].first+=tag[nd],tag[ls]+=tag[nd];
		tree[rs].first+=tag[nd],tag[rs]+=tag[nd];
		tag[nd]=0;
	}
	void modif(int nd,int l,int r,int p,int w){
		if(l==r){
			tree[nd].first=w;
			return ;
		}
		push(nd);
		if(p<=mid)modif(ls,l,mid,p,w);
		else modif(rs,mid+1,r,p,w);
		tree[nd]=min(tree[ls],tree[rs]);
	}
	void updata(int nd,int l,int r,int ql,int qr,int w){
		if(ql>qr)return ;
		if(l>=ql&&r<=qr){
			tree[nd].first+=w,tag[nd]+=w;
			return ;
		}
		push(nd);
		if(ql<=mid)updata(ls,l,mid,ql,qr,w);
		if(qr>mid)updata(rs,mid+1,r,ql,qr,w);
		tree[nd]=min(tree[ls],tree[rs]);
	}
}
void work(){
	n=read();
	for(int i=1;i<=n;i++)b[i]=a[i]=read();
	sort(b+1,b+n+1);
	for(int i=1;i<=n;i++)a[i]=lower_bound(b+1,b+n+1,a[i])-b;
	memset(ans,0x3f,sizeof(ans));
	bit::init();res=0;
	for(int i=1;i<=n;i++){
		bit::updata(a[i],1);
		l[i]=i-bit::query(a[i]);
	}
	sgt::build(1,1,n);bit::init();
	for(int i=1;i<=n;i++){
		sgt::modif(1,1,n,a[i],l[i]);
		sgt::updata(1,1,n,1,a[i]-1,-1);
		bit::updata(a[i],1);
		res+=bit::query(a[i]-1);
		while(!sgt::tree[1].first){
			int p=sgt::tree[1].second;
			bit::updata(p,-1);
			sgt::modif(1,1,n,p,inf);
		}
		ans[i]=min(ans[i],res);
		// cout<<res<<" "<<bit::query(n)<<"\n";
	}
	for(int i=1;i<=n;i++)a[i]=n-a[i]+1;
	bit::init();res=0;
	for(int i=1;i<=n;i++){
		bit::updata(a[i],1);
		l[i]=i-bit::query(a[i]);
	}
	sgt::build(1,1,n);bit::init();
	for(int i=1;i<=n;i++){
		sgt::modif(1,1,n,a[i],l[i]);
		sgt::updata(1,1,n,1,a[i]-1,-1);
		bit::updata(a[i],1);
		res+=bit::query(a[i]-1);
		while(!sgt::tree[1].first){
			int p=sgt::tree[1].second;
			bit::updata(p,-1);
			sgt::modif(1,1,n,p,inf);
		}
		ans[i]=min(ans[i],res);
		// cout<<res<<" "<<bit::query(n)<<"\n";
	}
	for(int i=1;i<=n;i++)printf("%lld\n",ans[i]);
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
