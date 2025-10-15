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
	int x=0,fl=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')fl=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
	return x*fl;
}
const int maxn=100010;
const int inf=1e9;
bool mbe;

int n,q,vu,vr;
int a[maxn];
struct bit{
#define lb(x) (x&(-x))
int tree[maxn];
void upd(int x,int w){
	while(x<=n)tree[x]+=w,x+=lb(x);
}
int que(int x){
	int res=0;
	while(x)res+=tree[x],x-=lb(x);
	return res;
}
}t;
#define mid ((l+r)>>1)
#define ls nd<<1
#define rs nd<<1|1
#define mid ((l+r)>>1)
#define ls nd<<1
#define rs nd<<1|1
int mn[maxn<<2],tag[maxn<<2];
void build(int nd,int l,int r){
    if(l==r){mn[nd]=t.que(l+vu-1)-t.que(l-1)-vr;return ;}
    build(ls,l,mid),build(rs,mid+1,r);
    mn[nd]=min(mn[ls],mn[rs]);
}
void upd(int nd,int w){mn[nd]+=w,tag[nd]+=w;}
void down(int nd){upd(ls,tag[nd]),upd(rs,tag[nd]),tag[nd]=0;}
void updata(int nd,int l,int r,int ql,int qr,int w){
    if(ql>qr)return ;
    if(l>=ql&&r<=qr)return upd(nd,w);
    if(tag[nd])down(nd);
    if(ql<=mid)updata(ls,l,mid,ql,qr,w);
    if(qr>mid)updata(rs,mid+1,r,ql,qr,w);
    mn[nd]=min(mn[ls],mn[rs]);
}
int query(int nd,int l,int r,int ql,int qr){
    if(l>=ql&&r<=qr)return mn[nd];
    if(tag[nd])down(nd);
    if(qr<=mid)return query(ls,l,mid,ql,qr);
    if(ql>mid)return query(rs,mid+1,r,ql,qr);
    return min(query(ls,l,mid,ql,qr),query(rs,mid+1,r,ql,qr));
}
#undef mid
void work(){
	n=read();vu=read();vr=read();
	for(int i=1;i<=n;i++)a[i]=read();
	q=read();
	if(vu>=n-1){
		int s=0;for(int i=1;i<=n;i++)s+=a[i];
		printf("%lld\n",s);
		while(q--){
			int p=read(),w=read();
			s-=a[p],a[p]=w,s+=a[p];
			printf("%lld\n",s);
		}
		return ;
	}
	for(int i=1;i<=n;i++)t.upd(i,a[i]);
	build(1,2,n-vu+1);
	auto sovle=[&](){
		int l=2,r=n-vu+1,res=n-vu+1;
		while(l<=r){
			int mid=l+r>>1;
			if(query(1,2,n-vu+1,2,mid)<=0)res=mid,r=mid-1;
			else l=mid+1;
		}
		// cout<<res+vu-1<<"\n";
		printf("%lld\n",t.que(res+vu-1));
	};
	sovle();
	while(q--){
		int p=read(),w=read()-a[p];a[p]+=w;
		// cout<<max(2ll,p-vu+1)<<" "<<min(p,n-vu+1)<<"\n";
		t.upd(p,w);updata(1,2,n-vu+1,max(2ll,p-vu+1),min(p,n-vu+1),w);
		sovle();
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