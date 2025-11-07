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
const int maxn=800010;
const int inf=2e9;
bool mbe;

int n,q,a[maxn],b[maxn];
int lshx[maxn],lenx,lshy[maxn],leny;
tuple<int,int,int> que[maxn];
#define mid ((l+r)>>1)
#define ls nd<<1
#define rs nd<<1|1
int mn[maxn<<2],pos[maxn<<2],ans[maxn<<2];
int query(int nd,int l,int r,int ql,int qr){
	if(ql>qr)return inf;
	if(l>=ql&&r<=qr)return mn[nd];
	if(qr<=mid)return query(ls,l,mid,ql,qr);
	if(ql>mid)return query(rs,mid+1,r,ql,qr);
	return min(query(ls,l,mid,ql,qr),query(rs,mid+1,r,ql,qr));
}
int query(int nd,int l,int r,int w){
	if(lshx[l]>=w)return l-1;
	if(lshx[r]<w)return r;
	if(l==r)return l-1;
	// cout<<l<<" "<<r<<" "<<w<<" "<<lshx[mid]<<" "<<lshx[mid+1]<<" "<<mn[rs]<<" "<<ans[ls]<<" q\n";
	if(w<=lshx[mid+1]){
		if(mn[rs]<=w)return ans[ls];
		else return query(ls,l,mid,w);
	}
	else{
		int res=query(rs,mid+1,r,w);
		if(res>mid)return res;
		return ans[ls];
	}
}
void up(int nd,int l,int r){
	mn[nd]=min(mn[ls],mn[rs]);
	// if(mn[rs]==16)cout<<l<<" "<<r<<" "<<lshx[l]<<" "<<lshx[mid]<<" up\n";
	ans[ls]=query(ls,l,mid,mn[rs]);
	// if(mn[rs]==16)cout<<l<<" "<<r<<" "<<ans[ls]<<" up\n";
	pos[nd]=pos[rs]>mid?pos[rs]:ans[ls];
}
void build(int nd,int l,int r){
	if(l==r){
		mn[nd]=inf;
		return ;
	}
	build(ls,l,mid),build(rs,mid+1,r);
	up(nd,l,r);
}
multiset<int> val[maxn];
void modif(int nd,int l,int r,int p,int w,int o){
	if(l==r){
		if(o==1)val[l].insert(w);
		else val[l].erase(val[l].find(w));
		mn[nd]=val[l].size()?(*val[l].begin()):inf;
		return ;
	}
	if(p<=mid)modif(ls,l,mid,p,w,o);
	else modif(rs,mid+1,r,p,w,o);
	up(nd,l,r);
}
namespace sgt{
	multiset<int> val[maxn];
	int mx[maxn<<2],num[maxn<<2];
	void modif(int nd,int l,int r,int p,int w,int o){
		if(l==r){
			if(o==1)val[l].insert(w);
			else val[l].erase(val[l].find(w));
			mx[nd]=val[l].size()?(*val[l].rbegin()):0;
			num[nd]+=o;
			return ;
		}
		if(p<=mid)modif(ls,l,mid,p,w,o);
		else modif(rs,mid+1,r,p,w,o);
		mx[nd]=max(mx[ls],mx[rs]);
		num[nd]=num[ls]+num[rs];
	}
	int quemx(int nd,int l,int r,int ql,int qr){
		if(ql>qr)return 0;
		if(l>=ql&&r<=qr)return mx[nd];
		if(qr<=mid)return quemx(ls,l,mid,ql,qr);
		if(ql>mid)return quemx(rs,mid+1,r,ql,qr);
		return max(quemx(ls,l,mid,ql,qr),quemx(rs,mid+1,r,ql,qr));
	}
	int query(int nd,int l,int r,int ql,int qr){
		if(ql>qr)return 0;
		if(l>=ql&&r<=qr)return num[nd];
		if(qr<=mid)return query(ls,l,mid,ql,qr);
		if(ql>mid)return query(rs,mid+1,r,ql,qr);
		return query(ls,l,mid,ql,qr)+query(rs,mid+1,r,ql,qr);
	}
}
void work(){
	n=read();q=read();
	for(int i=1;i<=n;i++)a[i]=read(),b[i]=read();
	for(int i=1;i<=n;i++)lshx[++lenx]=a[i],lshy[++leny]=b[i];
	for(int i=1;i<=q;i++){
		int u=read(),x=read(),y=read();
		lshx[++lenx]=x,lshy[++leny]=y;
		que[i]={u,x,y};
	}
	sort(lshx+1,lshx+lenx+1),lenx=unique(lshx+1,lshx+lenx+1)-lshx-1;
	sort(lshy+1,lshy+leny+1),leny=unique(lshy+1,lshy+leny+1)-lshy-1;
	build(1,1,lenx);
	for(int i=1;i<=n;i++){
		a[i]=lower_bound(lshx+1,lshx+lenx+1,a[i])-lshx;
		b[i]=lower_bound(lshy+1,lshy+leny+1,b[i])-lshy;
		modif(1,1,lenx,a[i],lshy[b[i]],1);
	}
	for(int i=1;i<=n;i++)sgt::modif(1,1,leny,b[i],a[i],1);
	multiset<pii> s;
	for(int i=1;i<=n;i++)s.insert({a[i],b[i]});
	auto sovle=[&](){
		auto[amx,bmx]=*s.rbegin();
		int p=upper_bound(lshy+1,lshy+leny+1,lshx[amx])-lshy-1;
		int res=sgt::query(1,1,leny,1,p)-(lshx[amx]>=lshy[bmx]);
		int mxa=sgt::quemx(1,1,leny,p+1,leny);
		// cout<<lshy[p]<<" "<<res<<" "<<lshx[mxa]<<"\n";
		if(!mxa){
			printf("%lld\n",n-res);
			return ;
		}
		// cout<<amx<<" "<<lshx[amx]<<" "<<lshy[bmx]<<" a\n";
		int to=query(1,1,lenx,lshy[bmx]);
		// cout<<res<<" "<<to<<" "<<lshx[to]<<" "<<query(1,1,lenx,to,lenx)<<"\n";
		if(lshx[mxa]>=query(1,1,lenx,to+1,lenx))res++;
		printf("%lld\n",n-res);
	};
	sovle();
	for(int i=1;i<=q;i++){
		// cout<<i<<" q\n";
		auto[u,x,y]=que[i];
		s.erase(s.find({a[u],b[u]}));
		modif(1,1,lenx,a[u],lshy[b[u]],-1);
		sgt::modif(1,1,leny,b[u],a[u],-1);
		x=lower_bound(lshx+1,lshx+lenx+1,x)-lshx,y=lower_bound(lshy+1,lshy+leny+1,y)-lshy;
		a[u]=x,b[u]=y;
		s.insert({a[u],b[u]});
		modif(1,1,lenx,a[u],lshy[b[u]],1);
		sgt::modif(1,1,leny,b[u],a[u],1);
		sovle();
		// if(i==2){
		// for(int j=1;j<=n;j++)cout<<lshx[a[j]]<<" "<<lshy[b[j]]<<"\n";
		// }
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