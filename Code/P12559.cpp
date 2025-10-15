#include<bits/stdc++.h>
using namespace std;
bool mbe;

#define ll long long
#define pb push_back
#define pii pair<ll,int>
#define fi first
#define se second
const int maxn=200010;
int n;ll a[maxn];
vector<int> pos[maxn];
ll lsh[maxn],len;
int b[maxn];
#define mid ((l+r)>>1)
#define ls nd<<1
#define rs nd<<1|1
namespace sgt1{
int val[maxn<<2];
set<int> pos[maxn];
void build(int nd,int l,int r){
	val[nd]=n;
	if(l==r){
		pos[l].clear();pos[l].insert(n);
		return ;
	}
	build(ls,l,mid),build(rs,mid+1,r);
}
void modif(int nd,int l,int r,int p,int w,int op){
	if(l==r){
		if(op==1)pos[l].insert(w);
		else pos[l].erase(w);
		
		val[nd]=*pos[l].begin();
		return ;
	}
	if(p<=mid)modif(ls,l,mid,p,w,op);
	else modif(rs,mid+1,r,p,w,op);
	val[nd]=min(val[ls],val[rs]);
}
int query(int nd,int l,int r,int ql,int qr){
	if(l>=ql&&r<=qr)return val[nd];
	if(qr<=mid)return query(ls,l,mid,ql,qr);
	if(ql>mid)return query(rs,mid+1,r,ql,qr);
	return min(query(ls,l,mid,ql,qr),query(rs,mid+1,r,ql,qr));
}
}
namespace sgt2{
pii mn[maxn<<2];ll tag[maxn<<2];
void build(int nd,int l,int r){
	mn[nd]={lsh[l],l};tag[nd]=0;
	if(l==r)return ;
	build(ls,l,mid),build(rs,mid+1,r);
}
void upd(int nd,ll w){mn[nd].fi+=w,tag[nd]+=w;}
void down(int nd){upd(ls,tag[nd]),upd(rs,tag[nd]),tag[nd]=0;}
void updata(int nd,int l,int r,int ql,int qr,ll w){
	if(l>=ql&&r<=qr)return upd(nd,w);
	if(tag[nd])down(nd);
	if(ql<=mid)updata(ls,l,mid,ql,qr,w);
	if(qr>mid)updata(rs,mid+1,r,ql,qr,w);
	mn[nd]=min(mn[ls],mn[rs]);
}
}
#undef ls
#undef rs
vector<tuple<int,int,int>> upd[maxn];
int rt[maxn];
#define ls lc[nd]
#define rs rc[nd]
namespace sgt3{
int tree[maxn<<6],lc[maxn<<6],rc[maxn<<6],idx;
void updata(int &nd,int l,int r,int ql,int qr,int w){
	int lst=nd;nd=++idx;tree[nd]=tree[lst],ls=lc[lst],rs=rc[lst];
	if(l>=ql&&r<=qr){tree[nd]+=w;return ;}
	if(ql<=mid)updata(ls,l,mid,ql,qr,w);
	if(qr>mid)updata(rs,mid+1,r,ql,qr,w);
}
int query(int nd,int l,int r,int p){
	if(l==r)return tree[nd];
	if(p<=mid)return query(ls,l,mid,p)+tree[nd];
	else return query(rs,mid+1,r,p)+tree[nd];
}
}
void init(int N, const vector<long long> &A){
	n=N;for(int i=1;i<=n;i++)a[i]=A[i-1];
	for(int i=1;i<=n;i++)pos[__lg(a[i])].pb(i);
	for(int j=0;j<60;j++)if(pos[j].size()){
		len=0;for(int i:pos[j])lsh[++len]=a[i]-(1ll<<j);
		sort(lsh+1,lsh+len+1),len=unique(lsh+1,lsh+len+1)-lsh-1;
		sgt1::build(1,1,len),sgt2::build(1,1,len);
		for(int i:pos[j])b[i]=lower_bound(lsh+1,lsh+len+1,a[i]-(1ll<<j))-lsh;
		// for(int i:pos[j])cout<<b[i]<<" ";cout<<"\n";
		for(int i:pos[j]){
			if(!lsh[b[i]]){continue;}
			sgt1::modif(1,1,len,b[i],i,1);
			sgt2::updata(1,1,len,b[i],len,-1);
			if(sgt2::mn[1].fi<0){
				int p=sgt2::mn[1].se;
				int lst=sgt1::query(1,1,len,1,p);
				// cout<<i<<" "<<b[i]<<" "<<p<<" "<<lst<<"\n";
				upd[i].pb({1,lst,-1});
				upd[i].pb({1,i,1});
				sgt1::modif(1,1,len,b[lst],lst,-1);
				sgt2::updata(1,1,len,b[lst],len,1);
			}
			else upd[i].pb({1,i,1});
		}
		// cout<<j<<endl;
		int lst=0;for(int i:pos[j]){
			rt[i]=rt[lst],lst=i;
			for(auto[l,r,w]:upd[i]){
				// cout<<l<<" "<<r<<" "<<w<<endl;
				sgt3::updata(rt[i],1,n,l,r,w);
			}
			// cout<<i<<" "<<upd[i].size()<<" "<<sgt3::idx<<endl;
		}
	}
}
long long ask(int l, int r){
	long long ans=r-l+1;
	int k=0;for(int i=0;i<60;i++){
		int pl=lower_bound(pos[i].begin(),pos[i].end(),l)-pos[i].begin();
		int pr=upper_bound(pos[i].begin(),pos[i].end(),r)-pos[i].begin()-1;
		if(pl<=pr)k=i;
	}
	int pl=lower_bound(pos[k].begin(),pos[k].end(),l)-pos[k].begin();
	int pr=upper_bound(pos[k].begin(),pos[k].end(),r)-pos[k].begin()-1;
	// cout<<l<<" "<<r<<" "<<sgt3::query(rt[pos[k][pr]],1,n,pos[k][pl])<<" "<<k<<"\n";
	return ans+sgt3::query(rt[pos[k][pr]],1,n,pos[k][pl])+(1ll<<k);
}
vector<long long> askAll(int q, const vector<int> &l, const vector<int> &r){
	vector<long long> ans(q);
	for(int i=0;i<q;i++)ans[i]=ask(l[i],r[i]);
	return ans;
}

bool med;
// signed main(){
	// cerr<<(&mbe-&med)/1024.0/1024.0<<"\n";
	// int n,q,t;cin>>n>>q>>t;
	// vector<long long> a(n);
	// for(int i=0;i<n;i++)cin>>a[i];
	// init(n,a);
	// vector<int> l(q),r(q);
	// for(int i=0;i<q;i++)cin>>l[i]>>r[i];
	// if(t==1){
		// vector<long long> ans=askAll(q,l,r);
		// for(long long v:ans)printf("%lld\n",v);
	// }
	// else{
		// vector<long long> ans(q);
		// for(int i=0;i<q;i++)ans[i]=ask(l[i],r[i]);
		// for(long long v:ans)printf("%lld\n",v);
	// }
// }