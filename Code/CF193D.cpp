// Problem: CF193D Two Segments
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/CF193D
// Memory Limit: 250 MB
// Time Limit: 5000 ms
// Written by yhm.
// Start codeing:2025-04-14 12:22:44
// 
// Powered by CP Editor (https://cpeditor.org)

#include<bits/stdc++.h>
#define int long long
#define mod 998244353ll
#define pii pair<int,int>
#define fi first
#define se second
#define pb push_back
#define mkp make_pair
#define mems(a,x) memset((a),(x),sizeof(a))
using namespace std;
inline int read(){
	int x=0,fl=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')fl=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
	return x*fl;
}
const int maxn=300010;
const int inf=1e9;
bool mbe;

int n,a[maxn],b[maxn],ans;
#define mid (l+r>>1)
#define ls nd<<1
#define rs nd<<1|1
struct node{
	int mn,cnt,se,num;
}tree[maxn<<2];
int tag[maxn<<2];
node merge(node u,node v){
	node res;
	res.mn=min(u.mn,v.mn);
	res.cnt=(u.mn==res.mn)*u.cnt+(v.mn==res.mn)*v.cnt;
	res.se=min({u.se,v.se,u.mn!=res.mn?u.mn:(v.mn!=res.mn?v.mn:inf)});
	res.num=(u.mn==res.se)*u.cnt+(v.mn==res.se)*v.cnt+(u.se==res.se)*u.num+(v.se==res.se)*v.num;
	return res;
}
void build(int nd,int l,int r){
	tree[nd]={0,r-l+1,inf,0};
	if(l==r)return ;
	build(ls,l,mid),build(rs,mid+1,r);
}
void upd(int nd,int w){tree[nd].mn+=w,tree[nd].se+=w,tag[nd]+=w;}
void down(int nd){upd(ls,tag[nd]),upd(rs,tag[nd]),tag[nd]=0;}
void updata(int nd,int l,int r,int ql,int qr,int w){
	if(l>=ql&&r<=qr)return upd(nd,w);
	if(tag[nd])down(nd);
	if(ql<=mid)updata(ls,l,mid,ql,qr,w);
	if(qr>mid)updata(rs,mid+1,r,ql,qr,w);
	tree[nd]=merge(tree[ls],tree[rs]);
}
node query(int nd,int l,int r,int ql,int qr){
	if(l>=ql&&r<=qr)return tree[nd];
	if(tag[nd])down(nd);
	if(qr<=mid)return query(ls,l,mid,ql,qr);
	if(ql>mid)return query(rs,mid+1,r,ql,qr);
	return merge(query(ls,l,mid,ql,qr),query(rs,mid+1,r,ql,qr));
}
void work(){
	n=read();
	for(int i=1;i<=n;i++)a[i]=read(),b[a[i]]=i;
	build(1,1,n);
	a[0]=a[n+1]=inf;
	for(int i=1;i<=n;i++){
		updata(1,1,n,1,i,1);
		if(a[b[i]-1]<i&&a[b[i]+1]<i){
			updata(1,1,n,1,min(a[b[i]-1],a[b[i]+1]),-1);
			updata(1,1,n,1,max(a[b[i]-1],a[b[i]+1]),-1);
		}
		else if(a[b[i]-1]<i)updata(1,1,n,1,a[b[i]-1],-1);
		else if(a[b[i]+1]<i)updata(1,1,n,1,a[b[i]+1],-1);
		if(i==1)continue;
		node res=query(1,1,n,1,i-1);
		if(res.mn<=2)ans+=res.cnt;
		if(res.se<=2)ans+=res.num;
		// cout<<i<<" "<<ans<<" "<<res.mn<<" "<<res.cnt<<" "<<res.se<<" "<<res.num<<"\n";
	}
	printf("%lld\n",ans);
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