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
const int maxn=600010;
const int inf=1e9;
bool mbe;

int n,m,ans,res;
#define mid ((l+r)>>1)
#define ls nd<<1
#define rs nd<<1|1
#define all 1,1,2*n
namespace sgt{
	int mx[maxn<<2],tag[maxn<<2];
	void upd(int nd,int w){mx[nd]+=w,tag[nd]+=w;}
	void down(int nd){upd(ls,tag[nd]),upd(rs,tag[nd]),tag[nd]=0;}
	void updata(int nd,int l,int r,int ql,int qr,int w){
		if(l>=ql&&r<=qr)return upd(nd,w);
		if(tag[nd])down(nd);
		if(ql<=mid)updata(ls,l,mid,ql,qr,w);
		if(qr>mid)updata(rs,mid+1,r,ql,qr,w);
		mx[nd]=max(mx[ls],mx[rs]);
	}
	int findl(int nd,int l,int r,int k){
		if(mx[nd]<k)return 2*n+1;
		if(l==r)return l;
		if(tag[nd])down(nd);
		if(mx[ls]>=k)return findl(ls,l,mid,k);
		else return findl(rs,mid+1,r,k);
	}
	int findr(int nd,int l,int r,int k){
		if(mx[nd]<k)return 2*n+1;
		if(l==r)return l;
		if(tag[nd])down(nd);
		if(mx[rs]>=k)return findr(rs,mid+1,r,k);
		else return findr(ls,l,mid,k);
	}
}
struct sgt1{
	pii mx[maxn<<2];
	void build(int nd,int l,int r){
		mx[nd]={-inf,0};
		if(l==r)return ;
		build(ls,l,mid),build(rs,mid+1,r);
	}
	void modif(int nd,int l,int r,int p,pii w){
		if(l==r){mx[nd]=w;return ;}
		if(p<=mid)modif(ls,l,mid,p,w);
		else modif(rs,mid+1,r,p,w);
		mx[nd]=max(mx[ls],mx[rs]);
	}
	pii query(int nd,int l,int r,int ql,int qr){
		if(ql>qr)return {-inf,0};
		if(l>=ql&&r<=qr)return mx[nd];
		if(qr<=mid)return query(ls,l,mid,ql,qr);
		if(ql>mid)return query(rs,mid+1,r,ql,qr);
		return max(query(ls,l,mid,ql,qr),query(rs,mid+1,r,ql,qr));
	}
}t1,t2;
struct node{
	int l,r,w;
}a[maxn];
int pos[maxn];
void upd(int id,int w){
	sgt::updata(all,a[id].l,a[id].r-1,w);
}
bool vis[maxn];
void add(int id,int w){
	if(w==1){
		vis[id]=1;t1.modif(all,a[id].r,{-a[id].w,id});t2.modif(all,a[id].r,{-inf,0});
		upd(id,1),res+=a[id].w;
	}
	else{
		vis[id]=0;t1.modif(all,a[id].r,{-inf,0});t2.modif(all,a[id].r,{a[id].w,id});
		upd(id,-1),res-=a[id].w;
	}
}
void mdf(){
	int p=sgt::findl(all,m);
	int id=t2.query(all,1,p).se;
	if(id)add(id,1);
}
void ins(int id){
	add(id,1);
	if(sgt::mx[1]>m){
		int p=sgt::findr(all,m+1);
		int id=t1.query(all,p+1,2*n).se;
		add(id,-1);
	}
}
void del(int id){
	if(vis[id]){
		add(id,-1);t2.modif(all,a[id].r,{-inf,0});
		mdf();
	}
	else t2.modif(all,a[id].r,{-inf,0});
}
void work(){
	n=read();m=read();
	for(int i=1;i<=n;i++)a[i]={read(),read(),read()},pos[a[i].l]=-i,pos[a[i].r]=i;
	t1.build(all),t2.build(all);
	for(int l=1,r=1;l<=2*n;){
		while(r<2*n){
			if(pos[r]<0&&r>l){
				upd(-pos[r],1);
				if(sgt::mx[1]>m){
					upd(-pos[r],-1);
					break;
				}
			}
			r++;
			if(pos[r]>0){
				if(a[pos[r]].l<=l)ins(pos[r]);
				else res+=a[pos[r]].w;
			}
		}
		ans=max(ans,res);
		if(pos[l]>0)del(pos[l]);
		l++;
		if(pos[l]<0&&l<r){
			upd(-pos[l],-1);mdf();
			if(a[-pos[l]].r<=r)res-=a[-pos[l]].w,ins(-pos[l]);
		}
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