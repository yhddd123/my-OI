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
const int maxn=500010;
const int inf=1e9;
bool mbe;

int n,q,a[maxn];
#define mid ((l+r)>>1)
#define ls nd<<1
#define rs nd<<1|1
struct node{
	int num,sum,pre,suf,mx;
}tree[maxn<<2];
node operator*(node u,node v){
	return {u.num+v.num,u.sum+v.sum,max(u.pre,u.sum+v.pre),max(v.suf,u.suf+v.sum),max({u.mx,u.suf+v.pre,v.mx})};
}
void build(int nd,int l,int r){
	if(l==r){
		if(a[l]==1)tree[nd]={1,1,1,1,1};
		else tree[nd]={0,-1,0,0,0};
		return ;
	}
	build(ls,l,mid),build(rs,mid+1,r);
	tree[nd]=tree[ls]*tree[rs];
}
void modif(int nd,int l,int r,int p){
	if(l==r){
		if(a[l]==1)tree[nd]={1,1,1,1,1};
		else tree[nd]={0,-1,0,0,0};
		return ;
	}
	if(p<=mid)modif(ls,l,mid,p);
	else modif(rs,mid+1,r,p);
	tree[nd]=tree[ls]*tree[rs];
}
node query(int nd,int l,int r,int ql,int qr){
	if(l>=ql&&r<=qr)return tree[nd];
	if(qr<=mid)return query(ls,l,mid,ql,qr);
	if(ql>mid)return query(rs,mid+1,r,ql,qr);
	return query(ls,l,mid,ql,qr)*query(rs,mid+1,r,ql,qr);
}
void work(){
	n=read();q=read();
	for(int i=1;i<=n;i++)a[i]=read();
	build(1,1,n);
	while(q--){
		int op=read();
		if(op==1){
			int p=read();a[p]=-a[p];
			modif(1,1,n,p);
		}
		else{
			int l=read(),r=read();
			node res=query(1,1,n,l,r);
			// cout<<res.num<<" "<<res.mx<<" "<<res.sum<<"\n";
			printf("%lld\n",2*res.num-res.mx);
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