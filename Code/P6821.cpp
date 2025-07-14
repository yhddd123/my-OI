#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int maxn=1000010;
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch-48);ch=getchar();}
	return x*f;
}
bool Mbe;

int n,k;
ll a[maxn];
namespace sgt{
#define mid (l+r>>1)
#define ls nd<<1
#define rs nd<<1|1
	struct node{
		ll sum;
		ll lmx,rmx,mx;
		int lx,rx,llx,rrx;
		ll lmn,rmn,mn;
		int ln,rn,lln,rrn;
	}tree[2100000];
	int tag[2100000];
	node merge(node u,node v){
		node res;
		res.sum=u.sum+v.sum;
		
		if(u.lmx>u.sum+v.lmx)res.lmx=u.lmx,res.llx=u.llx;
		else res.lmx=u.sum+v.lmx,res.llx=v.llx;
		if(v.rmx>v.sum+u.rmx)res.rmx=v.rmx,res.rrx=v.rrx;
		else res.rmx=v.sum+u.rmx,res.rrx=u.rrx;
		if(u.mx==max({u.mx,v.mx,u.rmx+v.lmx}))res.mx=u.mx,res.lx=u.lx,res.rx=u.rx;
		else if(v.mx>u.rmx+v.lmx)res.mx=v.mx,res.lx=v.lx,res.rx=v.rx;
		else res.mx=u.rmx+v.lmx,res.lx=u.rrx,res.rx=v.llx;
		
		if(u.lmn<u.sum+v.lmn)res.lmn=u.lmn,res.lln=u.lln;
		else res.lmn=u.sum+v.lmn,res.lln=v.lln;
		if(v.rmn<v.sum+u.rmn)res.rmn=v.rmn,res.rrn=v.rrn;
		else res.rmn=v.sum+u.rmn,res.rrn=u.rrn;
		if(u.mn==min({u.mn,v.mn,u.rmn+v.lmn}))res.mn=u.mn,res.ln=u.ln,res.rn=u.rn;
		else if(v.mn<u.rmn+v.lmn)res.mn=v.mn,res.ln=v.ln,res.rn=v.rn;
		else res.mn=u.rmn+v.lmn,res.ln=u.rrn,res.rn=v.lln;
		
		return res;
	}
	void build(int nd,int l,int r){
		if(l==r){
			tree[nd]={a[l],a[l],a[l],a[l],l,l,l,l,a[l],a[l],a[l],l,l,l,l};
			return ;
		}
		build(ls,l,mid);build(rs,mid+1,r);
		tree[nd]=merge(tree[ls],tree[rs]);
//		cout<<tree[nd].mx<<" "<<tree[nd].rrx<<" "<<tree[nd].lx<<" "<<tree[nd].rx<<" "<<l<<" "<<r<<"\n";
	}
	void change(int nd){
		tag[nd]^=1;
		tree[nd].sum*=-1;
		swap(tree[nd].mx,tree[nd].mn);
		swap(tree[nd].lmx,tree[nd].lmn);
		swap(tree[nd].rmx,tree[nd].rmn);
		tree[nd].mx*=-1;tree[nd].mn*=-1;
		tree[nd].lmx*=-1;tree[nd].lmn*=-1;
		tree[nd].rmx*=-1;tree[nd].rmn*=-1;
		swap(tree[nd].lx,tree[nd].ln);
		swap(tree[nd].rx,tree[nd].rn);
		swap(tree[nd].llx,tree[nd].lln);
		swap(tree[nd].rrx,tree[nd].rrn);
	}
	void down(int nd){
		change(ls);
		change(rs);
		tag[nd]=0;
	}
	void rev(int nd,int l,int r,int ql,int qr){
		if(l>=ql&&r<=qr){
			change(nd);
			return ;
		}
		if(tag[nd])down(nd);
		if(ql<=mid)rev(ls,l,mid,ql,qr);
		if(qr>mid)rev(rs,mid+1,r,ql,qr);
		tree[nd]=merge(tree[ls],tree[rs]);
	}
	node query(int nd,int l,int r,int ql,int qr){
		if(l>=ql&&r<=qr)return tree[nd];
		if(tag[nd])down(nd);
		if(qr<=mid)return query(ls,l,mid,ql,qr);
		if(ql>mid)return query(rs,mid+1,r,ql,qr);
		return merge(query(ls,l,mid,ql,qr),query(rs,mid+1,r,ql,qr));
	}
}
void work(){
	n=read();k=read();
	for(int i=1;i<=n;i++)a[i]=read();
	sgt::build(1,1,n);
	ll ans=0,sum=0;
	while(k--){
		sgt::node res=sgt::query(1,1,n,1,n);
		sum+=res.mx;ans=max(ans,sum);
		sgt::rev(1,1,n,res.lx,res.rx);
	}
	printf("%lld\n",ans);
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
