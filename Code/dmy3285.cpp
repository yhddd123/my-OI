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
const int maxn=200010;
const int inf=1e9;
bool mbe;

int n,a[maxn];
#define mid ((l+r)>>1)
#define ls nd<<1
#define rs nd<<1|1
struct node{
	int mx;
	int len;
	bool vl,vr,fl;
}tree[maxn<<2];
node merge(node u,node v){
	node res;
	res.mx=max(u.mx,v.mx);
	res.fl=u.fl|v.fl;
	if(!u.len)res.len=v.len,res.vl=v.vl,res.vr=v.vr;
	else if(!v.len)res.len=u.len,res.vl=u.vl,res.vr=u.vr;
	else{
		if(u.vr==v.vl){
			res.fl=1;
			if(u.len<v.len)res.len=v.len-u.len,res.vl=(res.len&1)?v.vr:1-v.vr,res.vr=v.vr;
			else res.len=u.len-v.len,res.vl=u.vl,res.vr=(res.len&1)?u.vl:1-u.vl;
		}
		else res.len=u.len+v.len,res.vl=u.vl,res.vr=v.vr;
	}
	return res;
}
void modif(int nd,int l,int r,int p,int w){
	if(l==r){
		tree[nd].mx=w;
		w&=1;
		if(w)tree[nd].len=1,tree[nd].vl=tree[nd].vr=(l&1);
		else tree[nd].len=tree[nd].vl=tree[nd].vr=0;
		tree[nd].fl=0;
		return ;
	}
	if(p<=mid)modif(ls,l,mid,p,w);
	else modif(rs,mid+1,r,p,w);
	tree[nd]=merge(tree[ls],tree[rs]);
}
node query(int nd,int l,int r,int ql,int qr){
	if(l>=ql&&r<=qr)return tree[nd];
	if(qr<=mid)return query(ls,l,mid,ql,qr);
	if(ql>mid)return query(rs,mid+1,r,ql,qr);
	return merge(query(ls,l,mid,ql,qr),query(rs,mid+1,r,ql,qr));
}
void work(){
	n=read();
	for(int i=1;i<=n;i++)a[i]=read(),modif(1,1,n,i,a[i]);
	int q=read();
	int t=0;
	while(q--){
		int op=read(),l=read(),r=read();
		if(op==1)modif(1,1,n,l,r),a[l]=r;
		else{
			if(l==r){puts(a[l]?"0":"1");continue;}
			node res=query(1,1,n,l,r-1);
			res.mx=max(res.mx,a[r]);
			if(!res.mx){printf("%lld\n",r-l+1);continue;}
			bool fl=!a[r];
			fl&=res.mx<=1;
			if(res.len&&res.vr==(r&1))res.len--,fl=0;
			fl&=1-res.fl;
			printf("%lld\n",r-l+1-(1-fl)-res.len);
		}
	}
}

bool med;
int T;
signed main(){
	// freopen(".in","r",stdin);
	// freopen("A.out","w",stdout);
	
	// cerr<<(&mbe-&med)/1024.0/1024.0<<"\n";
	
	T=1;
	while(T--)work();
}