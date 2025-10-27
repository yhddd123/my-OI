#include<bits/stdc++.h>
// #define int long long
#define mod 998244353ll
#define pii pair<db,db>
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
const int maxn=300010;
const int inf=3e5+1;
const db eps=1e-12;
bool mbe;

inline int sgn(db x){
	if(fabsl(x)<eps)return 0;
	return (x>0)-(x<0);
}
int n,q;
struct seg{
	#define mid ((l+r)>>1)
	#define ls nd<<1
	#define rs nd<<1|1
	db tree[maxn<<3],tag[maxn<<3];
	void upd(int nd,int l,int r,db w){tree[nd]+=w*(r-l+1),tag[nd]+=w;}
	void down(int nd,int l,int r){upd(ls,l,mid,tag[nd]),upd(rs,mid+1,r,tag[nd]),tag[nd]=0;}
	void updata(int nd,int l,int r,int ql,int qr,db w){
		if(l>=ql&&r<=qr)return upd(nd,l,r,w);
		down(nd,l,r);
		if(ql<=mid)updata(ls,l,mid,ql,qr,w);
		if(qr>mid)updata(rs,mid+1,r,ql,qr,w);
		tree[nd]=tree[ls]+tree[rs];
	}
	db query(int nd,int l,int r,int ql,int qr){
		if(l>=ql&&r<=qr)return tree[nd];
		down(nd,l,r);
		if(qr<=mid)return query(ls,l,mid,ql,qr);
		if(ql>mid)return query(rs,mid+1,r,ql,qr);
		return query(ls,l,mid,ql,qr)+query(rs,mid+1,r,ql,qr);
	}
}t1,t2;
struct node{
	int a,b,c,d,id;
}a[maxn];
db ans[maxn];
void work(){
	n=read();
	for(int i=1;i<=n;i++)a[i]={read(),read(),read(),read(),0};
	q=read();
	for(int i=1;i<=q;i++){
		int x=read(),y=read();
		a[n+i]={x,y,x,y,i};
	}
	sort(a+1,a+n+q+1,[&](node u,node v){
		// if(u.id&&v.id)return u.a<v.a||(u.a==v.a&&u.b<v.b);
		// if(u.c<=v.a)return true;
		// if(v.c<=u.a)return false;
		// int p=max(u.a,v.a);
		// db uy=u.id?u.b:((db)1.0*(u.b-u.d)*(u.c-p)/(u.c-u.a)+u.d);
		// db vy=v.id?v.b:((db)1.0*(v.b-v.d)*(v.c-p)/(v.c-v.a)+v.d);
		// return sgn(uy-vy)==-1||(!sgn(uy-vy)&&u.id<v.id);
		return u.a+u.b<v.a+v.b||(u.a+u.b==v.a+v.b&&u.id<v.id);
	});
	db sum=0;
	for(int i=1;i<=n+q;i++){
		// cout<<a[i].a<<" "<<a[i].b<<" "<<a[i].c<<" "<<a[i].d<<" "<<a[i].id<<"\n";
		if(a[i].id){
			// cout<<t1.query(1,-inf,inf,a[i].a)<<" "<<t2.query(1,-inf,inf,a[i].b)<<"\n";
			ans[a[i].id]=sum-t1.query(1,-inf,inf,a[i].a,inf)-t2.query(1,-inf,inf,a[i].b,inf);
		}
		else{
			db len=sqrtl((db)1.0*(a[i].c-a[i].a)*(a[i].c-a[i].a)+(db)1.0*(a[i].b-a[i].d)*(a[i].b-a[i].d));
			sum+=len;
			db dx=len/(a[i].c-a[i].a);t1.updata(1,-inf,inf,a[i].a,a[i].c-1,dx);
			db dy=len/(a[i].b-a[i].d);t2.updata(1,-inf,inf,a[i].d,a[i].b-1,dy);
		}
	}
	for(int i=1;i<=q;i++)printf("%.12Lf\n",ans[i]);
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