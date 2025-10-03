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
const int maxn=300010;
const int inf=1e9;
bool mbe;

int n,m,a[maxn],ans;
int pl[maxn],pr[maxn],w[maxn],id[maxn];
#define mid ((l+r)>>1)
#define ls nd<<1
#define rs nd<<1|1
int mx[maxn<<2],mn[maxn<<2],tag[maxn<<2];
void build(int nd,int l,int r){
    tag[nd]=0;
    if(l==r){
    	mx[nd]=a[pl[l+1]-1],mn[nd]=a[pr[l]];
    	return ;
    }
    build(ls,l,mid),build(rs,mid+1,r);
    mx[nd]=max(mx[ls],mx[rs]);
    mn[nd]=min(mn[ls],mn[rs]);
}
void upd(int nd,int w){mx[nd]+=w,mn[nd]+=w,tag[nd]+=w;}
void down(int nd){upd(ls,tag[nd]),upd(rs,tag[nd]),tag[nd]=0;}
void updata(int nd,int l,int r,int ql,int qr,int w){
    if(ql>qr)return ;
    if(l>=ql&&r<=qr)return upd(nd,w);
    if(tag[nd])down(nd);
    if(ql<=mid)updata(ls,l,mid,ql,qr,w);
    if(qr>mid)updata(rs,mid+1,r,ql,qr,w);
    mx[nd]=max(mx[ls],mx[rs]);
    mn[nd]=min(mn[ls],mn[rs]);
}
int quemn(int nd,int l,int r,int ql,int qr){
    if(l>=ql&&r<=qr)return mn[nd];
    if(tag[nd])down(nd);
    if(qr<=mid)return quemn(ls,l,mid,ql,qr);
    if(ql>mid)return quemn(rs,mid+1,r,ql,qr);
    return min(quemn(ls,l,mid,ql,qr),quemn(rs,mid+1,r,ql,qr));
}
int quemx(int nd,int l,int r,int ql,int qr){
    if(l>=ql&&r<=qr)return mx[nd];
    if(tag[nd])down(nd);
    if(qr<=mid)return quemx(ls,l,mid,ql,qr);
    if(ql>mid)return quemx(rs,mid+1,r,ql,qr);
    return max(quemx(ls,l,mid,ql,qr),quemx(rs,mid+1,r,ql,qr));
}
void work(){
	n=read();m=read();
	for(int i=1;i<=m;i++)a[i]=a[i-1]+read();
	for(int i=1;i<=n;i++){
		pl[i]=read(),pr[i]=read(),w[i]=read(),id[i]=i;
	}
	build(1,1,n);
	sort(id+1,id+n+1,[&](int u,int v){return w[u]>w[v];});
	build(1,0,n);
	// for(int i=1;i<=n;i++){
		// cout<<quemx(1,0,n,0,i-1)<<" "<<quemn(1,0,n,i,n)<<"\n";
	// }
	for(int i=1;i<=n;i++){
		updata(1,0,n,id[i],n,-1);
		// cout<<quemn(1,0,n,id[i],n)<<" "<<quemx(1,0,n,0,id[i]-1)<<"\n";
		if(quemn(1,0,n,id[i],n)>=quemx(1,0,n,0,id[i]-1)){
			ans+=w[id[i]];
		}
		else{
			updata(1,0,n,id[i],n,1);
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