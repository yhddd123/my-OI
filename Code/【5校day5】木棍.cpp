#include<bits/stdc++.h>
#define int long long
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

int n,m,k;
pii a[maxn];
int x[maxn],y[maxn],c[maxn];
int lsh[maxn],len;
int f[maxn],g[maxn];
namespace sgt1{
	#define mid (l+r>>1)
	#define ls nd<<1
	#define rs nd<<1|1
	int tree[maxn<<2],tag[maxn<<2];
	void build(int nd,int l,int r){
		tree[nd]=inf,tag[nd]=0;
		if(l==r)return ;
		build(ls,l,mid),build(rs,mid+1,r);
	}
	void down(int nd){
		tree[ls]+=tag[nd],tag[ls]+=tag[nd];
		tree[rs]+=tag[nd],tag[rs]+=tag[nd];
		tag[nd]=0;
	}
	void updata(int nd,int l,int r,int ql,int qr,int w){
		if(l>=ql&&r<=qr){
			tree[nd]+=w,tag[nd]+=w;
			return ;
		}
		if(tag[nd])down(nd);
		if(ql<=mid)updata(ls,l,mid,ql,qr,w);
		if(qr>mid)updata(rs,mid+1,r,ql,qr,w);
		tree[nd]=min(tree[ls],tree[rs]);
	}
	void modif(int nd,int l,int r,int p,int w){
		if(l==r){
			tree[nd]=w;
			return ;
		}
		if(tag[nd])down(nd);
		if(p<=mid)modif(ls,l,mid,p,w);
		else modif(rs,mid+1,r,p,w);
		tree[nd]=min(tree[ls],tree[rs]);
	}
	int query(int nd,int l,int r,int ql,int qr){
		if(ql>qr)return inf;
		if(l>=ql&&r<=qr)return tree[nd];
		if(tag[nd])down(nd);
		if(qr<=mid)return query(ls,l,mid,ql,qr);
		if(ql>mid)return query(rs,mid+1,r,ql,qr);
		return min(query(ls,l,mid,ql,qr),query(rs,mid+1,r,ql,qr));
	}
	#undef ls
	#undef rs
}
namespace sgt2{
	#define mid (l+r>>1)
	#define ls lc[nd]
	#define rs rc[nd]
	int tree[maxn<<6],lc[maxn<<6],rc[maxn<<6],idx;
	void updata(int &nd,int l,int r,int p,int w){
		if(!nd)nd=++idx,tree[nd]=inf,ls=rs=0;
		if(l==r){
			tree[nd]=min(tree[nd],w);
			return ;
		}
		if(p<=mid)updata(ls,l,mid,p,w);
		else updata(rs,mid+1,r,p,w);
		tree[nd]=min(tree[ls],tree[rs]);
	}
	int query(int nd,int l,int r,int ql,int qr){
		if(!nd||ql>qr)return inf;
		if(l>=ql&&r<=qr)return tree[nd];
		if(qr<=mid)return query(ls,l,mid,ql,qr);
		if(ql>mid)return query(rs,mid+1,r,ql,qr);
		return min(query(ls,l,mid,ql,qr),query(rs,mid+1,r,ql,qr));
	}
}
vector<int> pos[maxn];
void work(){
	n=read();m=read();k=read();
	for(int i=1;i<=n;i++)a[i]={read()+1,read()+1-k};
	for(int i=1;i<=n;i++)if(a[i].fi>a[i].se){puts("No");return ;}
	for(int i=1;i<=m;i++)x[i]=read()+1,y[i]=read()+1-k,c[i]=read();
	lsh[++len]=0;lsh[++len]=inf;
	for(int i=1;i<=n;i++)lsh[++len]=a[i].fi-1,lsh[++len]=a[i].se;
	for(int i=1;i<=m;i++)lsh[++len]=x[i]-1,lsh[++len]=y[i];
	sort(lsh+1,lsh+len+1),len=unique(lsh+1,lsh+len+1)-lsh-1;
	for(int i=1;i<=n;i++)a[i].fi=lower_bound(lsh+1,lsh+len+1,a[i].fi-1)-lsh;
	for(int i=1;i<=n;i++)a[i].se=lower_bound(lsh+1,lsh+len+1,a[i].se)-lsh;
	for(int i=1;i<=n;i++)pos[a[i].fi].pb(a[i].se);
	for(int i=1;i<=m;i++)x[i]=lower_bound(lsh+1,lsh+len+1,x[i]-1)-lsh;
	for(int i=1;i<=m;i++)y[i]=lower_bound(lsh+1,lsh+len+1,y[i])-lsh;
	// for(int i=1;i<=len;i++)cout<<lsh[i]<<" ";cout<<"\n";
	// for(int i=1;i<=n;i++)cout<<a[i].fi<<" "<<a[i].se<<"\n";
	for(int t=1;t<=len;t++){
		// cout<<t<<"\n";
		for(int i=1;i<=len+1;i++)f[i]=inf;
		for(int i=len;i;i--)f[i]=min(f[i+1],g[i]);
		sgt2::idx=0;int rt=0;
		for(int i=1;i<=len;i++){
			f[i]=min(f[i],lsh[i]/k+sgt2::query(rt,0,k-1,0,lsh[i]%k-1)+1);
			f[i]=min(f[i],lsh[i]/k+sgt2::query(rt,0,k-1,lsh[i]%k,k-1));
			sgt2::updata(rt,0,k-1,lsh[i]%k,g[i]-lsh[i]/k);
		}
		for(int i=1;i<=m;i++)f[y[i]]=min(f[y[i]],g[x[i]]+c[i]);
		sgt1::build(1,1,len);
		for(int i=len;i;i--){
			for(int j:pos[i])sgt1::updata(1,1,len,j,len,-1);
			// cout<<i<<" "<<f[i]<<"\n";
			f[i]=min(f[i],sgt1::query(1,1,len,1,len));
			// cout<<i<<" "<<f[i]<<"\n";
			sgt1::modif(1,1,len,i,g[i]);
		}
		bool fl=0;
		for(int i=1;i<=len;i++)if(f[i]!=g[i])fl=1;
		// for(int i=1;i<=len;i++)cout<<f[i]<<" ";cout<<"\n";
		if(!fl){
			puts("Yes");
			return ;
		}
		for(int i=1;i<=len;i++)g[i]=f[i];
	}
	puts("No");
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
