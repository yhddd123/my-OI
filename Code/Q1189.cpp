#include<bits/stdc++.h>
#define int long long
#define mod 1000000007
#define ls nd<<1
#define rs nd<<1|1
#define mid (l+r>>1)
using namespace std;
const int maxn=400010;
const int inf=1e18;
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch-48);ch=getchar();}
	return x*f;
}

int n,m,x,y;
struct nd{
	int col,l,r;
}a[maxn];
bool cmp(nd u,nd v){return u.r<v.r;}
int b[maxn],len;
int dp[maxn],ans;
struct seg{
	int tree[maxn<<2];
	void build(int nd=1,int l=1,int r=len){
		tree[nd]=-inf;
		if(l==r)return ;
		build(ls,l,mid);build(rs,mid+1,r);
	}
	void updata(int ql,int qr,int w,int nd=1,int l=1,int r=len){
		if(ql>qr)return ;
		if(l>=ql&&r<=qr){
			tree[nd]=max(tree[nd],w);
			return ;
		}
		if(ql<=mid)updata(ql,qr,w,ls,l,mid);
		if(qr>mid)updata(ql,qr,w,rs,mid+1,r);
	}
	int query(int ql,int nd=1,int l=1,int r=len){
		if(l==r)return tree[nd];
		tree[ls]=max(tree[ls],tree[nd]);
		tree[rs]=max(tree[rs],tree[nd]);
		if(ql<=mid)return query(ql,ls,l,mid);
		else return query(ql,rs,mid+1,r);
	}
}tr[3],tr1,tr2;

int T;
signed main(){
	//	freopen(".in","r",stdin);
	//	freopen(".out","w",stdout);
	
	n=read();m=read();x=read();y=read();
	for(int i=1;i<=m;i++){
		a[i].col=read()-1;a[i].l=read();a[i].r=read();
		b[++len]=a[i].l;b[++len]=a[i].r;
	}
	sort(b+1,b+len+1);len=unique(b+1,b+len+1)-b-1;
	for(int i=1;i<=m;i++){
		a[i].l=lower_bound(b+1,b+len+1,a[i].l)-b;
		a[i].r=lower_bound(b+1,b+len+1,a[i].r)-b;
	}
	sort(a+1,a+m+1,cmp);
	tr[0].build();tr[1].build();tr[2].build();tr2.build();
	memset(dp,-0x3f,sizeof(dp));
	for(int i=1;i<=m;i++){
		dp[i]=max(dp[i],tr1.query(a[i].l)+(b[a[i].r]-b[a[i].l]+1)*x);
		dp[i]=max(dp[i],tr[a[i].col].query(a[i].l)+b[a[i].r]*x);
		dp[i]=max(dp[i],tr2.query(a[i].l)+b[a[i].r]*x+(b[a[i].l]-1)*(x+y));
		tr1.updata(a[i].r+1,len,dp[i]);
		tr[a[i].col].updata(a[i].l,a[i].r,dp[i]-b[a[i].r]*x);
		tr2.updata(a[i].l,a[i].r,dp[i]-b[a[i].r]*(2*x+y));
		ans=max(ans,dp[i]);
	}
	printf("%lld\n",ans);
}
