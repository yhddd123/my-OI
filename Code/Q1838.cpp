#include<bits/stdc++.h>
#define int long long
#define mod 998244353ll
#define pii pair<int,int>
#define fi first
#define se second
#define mems(x,y) memset(x,y,sizeof(x))
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
bool Mbe;

int n,ans;
struct nd{
	int l,r,d,u;
}a[maxn];
int lsh[maxn],len;
int d[maxn];
int px[maxn],py[maxn];
#define mid (l+r>>1)
#define ls nd<<1
#define rs nd<<1|1
struct node{
	int sum,l,r;
}tree[maxn<<2];
node merge(node u,node v){return {u.sum+v.sum+u.r*v.l,u.l+v.l,u.r+v.r};}
void updata(int nd,int l,int r,int p,int vl,int vr){
	if(l==r){tree[nd].l+=vl,tree[nd].r+=vr;return ;}
	if(p<=mid)updata(ls,l,mid,p,vl,vr);
	else updata(rs,mid+1,r,p,vl,vr);
	tree[nd]=merge(tree[ls],tree[rs]);
}
node query(int nd,int l,int r,int ql,int qr){
	if(ql>qr)return {0,0,0};
	if(l>=ql&&r<=qr)return tree[nd];
	if(qr<=mid)return query(ls,l,mid,ql,qr);
	if(ql>mid)return query(rs,mid+1,r,ql,qr);
	return merge(query(ls,l,mid,ql,qr),query(rs,mid+1,r,ql,qr));
}
void work(){
	n=read();
	for(int i=1;i<=n;i++)a[i]={read(),read(),read(),read()};
	for(int i=1;i<=n;i++)lsh[++len]=a[i].l,lsh[++len]=a[i].r;
	sort(lsh+1,lsh+len+1);len=unique(lsh+1,lsh+len+1)-lsh-1;
	for(int i=1;i<=n;i++)a[i].l=lower_bound(lsh+1,lsh+len+1,a[i].l)-lsh,a[i].r=lower_bound(lsh+1,lsh+len+1,a[i].r)-lsh;
	len=0;for(int i=1;i<=n;i++)lsh[++len]=a[i].d,lsh[++len]=a[i].u;
	sort(lsh+1,lsh+len+1);len=unique(lsh+1,lsh+len+1)-lsh-1;
	for(int i=1;i<=n;i++)a[i].d=lower_bound(lsh+1,lsh+len+1,a[i].d)-lsh,a[i].u=lower_bound(lsh+1,lsh+len+1,a[i].u)-lsh;
	for(int i=1;i<=n;i++)px[a[i].l]=i,px[a[i].r]=-i,py[a[i].d]=i,py[a[i].u]=-i;
	for(int i=1,cnt=0;i<=2*n;i++){
		if(px[i]>0){
			int id=px[i];
			d[id]+=cnt-query(1,1,2*n,1,a[id].d-1).r-query(1,1,2*n,a[id].u+1,2*n).l;
			updata(1,1,2*n,a[id].d,1,0),updata(1,1,2*n,a[id].u,0,1);
			cnt++;
		}
		else{
			int id=-px[i];
			updata(1,1,2*n,a[id].d,-1,0),updata(1,1,2*n,a[id].u,0,-1);
			cnt--;
		}
	}
	for(int i=1,cnt=0;i<=2*n;i++){
		if(px[i]>0){
			int id=px[i];
			d[id]-=cnt-query(1,1,2*n,1,a[id].d-1).r-query(1,1,2*n,a[id].u+1,2*n).l;
			updata(1,1,2*n,a[id].d,1,0),updata(1,1,2*n,a[id].u,0,1);
			cnt++;
		}
		else{
			int id=-px[i];
			d[id]+=cnt-query(1,1,2*n,1,a[id].d-1).r-query(1,1,2*n,a[id].u+1,2*n).l;
		}
	}
	for(int i=1;i<=n;i++)updata(1,1,2*n,a[i].d,-1,0),updata(1,1,2*n,a[i].u,0,-1);
	for(int i=1;i<=n;i++)d[i]--;
	for(int i=1;i<=n;i++)ans+=d[i]*(n-2)-d[i]*(d[i]-1);
	// for(int i=1;i<=n;i++)cout<<d[i]<<" ";cout<<"\n";
	// cout<<ans<<"\n";
	ans/=2;
	//ans=c1+c2	
	for(int i=1,cnt=0;i<=2*n;i++){
		if(px[i]>0){
			int id=px[i];
			int num=cnt-query(1,1,2*n,1,a[id].d-1).r-query(1,1,2*n,a[id].u+1,2*n).l;
			ans+=num*(num-1)/2-query(1,1,2*n,a[id].d,a[id].u).sum;
			updata(1,1,2*n,a[id].d,1,0),updata(1,1,2*n,a[id].u,0,1);
			cnt++;
		}
		else{
			int id=-px[i];
			updata(1,1,2*n,a[id].d,-1,0),updata(1,1,2*n,a[id].u,0,-1);
			cnt--;
		}
	}
	printf("%lld\n",n*(n-1)*(n-2)/6-ans);
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
