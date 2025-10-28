#include<bits/stdc++.h>
#define int long long
#define mod 998244353ll
#define pii pair<int,int>
#define fi first
#define se second
#define pb push_back
#define db long double
#define mems(a,x) memset((a),(x),sizeof(a))
using namespace std;
inline int read(){
	int x=0;char ch=getchar();
	while(ch<'0'||ch>'9')ch=getchar();
	while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
	return x;
}
const int maxn=500010;
const int inf=1e9;
bool mbe;

int n,q,m,a[maxn];
struct sgt{
	#define mid ((l+r)>>1)
	#define ls nd<<1
	#define rs nd<<1|1
	int k;
	int mn[maxn<<2],mx[maxn<<2],tag[maxn<<2];
	void build(int nd,int l,int r){
		if(l==r){
			int v=a[l]&((1ll<<k+1)-1);
			if(v<(1ll<<k))mn[nd]=-v;
			else mn[nd]=(1ll<<k+1)-v;
			mx[nd]=mn[nd]+(1ll<<k);
			// cout<<k<<" "<<l<<" "<<v<<" "<<mn[nd]<<"\n";
			return ;
		}
		build(ls,l,mid),build(rs,mid+1,r);
		mn[nd]=min(mn[ls],mn[rs]),mx[nd]=max(mx[ls],mx[rs]);
	}
	void upd(int nd,int w){mn[nd]+=w,mx[nd]+=w,tag[nd]+=w;}
	void down(int nd){upd(ls,tag[nd]),upd(rs,tag[nd]),tag[nd]=0;}
	void updata(int nd,int l,int r,int ql,int qr,int w){
		if(l>=ql&&r<=qr){
			if(mx[nd]-w<=0)return upd(nd,(1ll<<k+1)-w);
			if(mn[nd]-w>-(1ll<<k))return upd(nd,-w);
		}
		if(tag[nd])down(nd);
		if(ql<=mid)updata(ls,l,mid,ql,qr,w);
		if(qr>mid)updata(rs,mid+1,r,ql,qr,w);
		mn[nd]=min(mn[ls],mn[rs]),mx[nd]=max(mx[ls],mx[rs]);
	}
	int query(int nd,int l,int r,int ql,int qr){
		// cout<<l<<" "<<r<<" "<<ql<<" "<<qr<<" "<<mn[nd]<<"\n";
		if(l>=ql&&r<=qr)return mn[nd];
		if(tag[nd])down(nd);
		if(qr<=mid)return query(ls,l,mid,ql,qr);
		if(ql>mid)return query(rs,mid+1,r,ql,qr);
		return min(query(ls,l,mid,ql,qr),query(rs,mid+1,r,ql,qr));
	}
	void init(int _k){
		k=_k;
		build(1,1,n);
	}
}t[32];
void work(){
	n=read();q=read();m=read();
	for(int i=1;i<=n;i++)a[i]=read();
	for(int i=0;i<m;i++)t[i].init(i);
	while(q--){
		int op=read();
		if(op==0){
			int l=read()+1,r=read(),w=read();
			for(int i=0;i<m;i++)t[i].updata(1,1,n,l,r,w&((1ll<<i+1)-1));
			// for(int i=l;i<=r;i++)a[i]=(a[i]+w)%((1ll<<m)-1);
		}
		else{
			int l=read()+1,r=read(),ans=0;
			// for(int i=l;i<=r;i++)cout<<a[i]<<" ";cout<<"\n";
			for(int i=0;i<m;i++)if(t[i].query(1,1,n,l,r)>0){
			ans|=1ll<<i;
			// cout<<i<<" "<<t[i].query(1,1,n,l,r)<<"\n";
			}
			printf("%lld\n",ans);
		}
	}
}

bool med;
int T;
signed main(){
	// freopen(".in","r",stdin);
	// freopen(".out","w",stdout);
	
	// cerr<<(&mbe-&med)/1024.0/1024.0<<"\n";
	
	T=1;
	while(T--)work();
}