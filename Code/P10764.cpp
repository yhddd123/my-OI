#include<bits/stdc++.h>
#define int long long
#define mod 1000000007ll
#define pii pair<int,int>
#define fi first
#define se second
#define pb push_back
#define db long double
#define mems(a,x) memset((a),(x),sizeof(a))
#define mkp make_pair
using namespace std;
static char buf[1000000],*p1=buf,*p2=buf;
#define getchar() p1==p2&&(p2=(p1=buf)+fread(buf,1,1000000,stdin),p1==p2)?EOF:*p1++
inline int read(){int x=0,f=1;char c=getchar();while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}while(c>='0'&&c<='9'){x=(x<<3)+(x<<1)+c-48;c=getchar();}return x*f;}
inline void write(int x){static char buf[20];static int len=-1;if(x<0)putchar('-'),x=-x;do buf[++len]=x%10,x/=10;while(x);while(len>=0)putchar(buf[len--]+48);}
const int maxn=500010;
const int inf=1e9;
bool mbe;

int n,a[maxn],b[maxn],ans;
int lsh[maxn<<1],len;
int f[maxn][2],g[maxn][2],pw[maxn];
#define lb(x) (x&(-x))
struct bit{
	int tree[maxn<<1];
	void upd(int x,int w){
		while(x<=len)tree[x]+=w,x+=lb(x);
	}
	int que(int x){
		int res=0;while(x)res+=tree[x],x-=lb(x);
		return res;
	}
	void clr(){
		for(int i=1;i<=len;i++)tree[i]=0;
	}
}t;
pii operator+(pii u,pii v){return {(u.fi+v.fi)%mod,(u.se+v.se)%mod};}
pii operator*(pii u,pii v){return {u.fi*v.fi%mod,(u.fi*v.se+u.se*v.fi)%mod};}
#define mid ((l+r)>>1)
#define ls nd<<1
#define rs nd<<1|1
pii tree[maxn<<2],tag[maxn<<2];int laz[maxn<<2];
void build(int nd,int l,int r){
	tree[nd]={0,0},tag[nd]={1,0},laz[nd]=1;
	if(l==r)return ;
	build(ls,l,mid),build(rs,mid+1,r);
}
void upd(int nd,pii w){tree[nd]=tree[nd]*w,tag[nd]=tag[nd]*w;}
void down(int nd){if(tag[nd].fi!=1||tag[nd].se)upd(ls,tag[nd]),upd(rs,tag[nd]),tag[nd]={1,0};}
void updata(int nd,int l,int r,int ql,int qr,pii w){
	if(ql>qr)return ;
	if(l>=ql&&r<=qr)return upd(nd,w);
	down(nd);
	if(ql<=mid)updata(ls,l,mid,ql,qr,w);
	if(qr>mid)updata(rs,mid+1,r,ql,qr,w);
	tree[nd]=tree[ls]+tree[rs];
}
void modif(int nd,int l,int r,int p,pii w){
	if(l==r){tree[nd]=tree[nd]+w;return ;}
	down(nd);
	if(p<=mid)modif(ls,l,mid,p,w);
	else modif(rs,mid+1,r,p,w);
	tree[nd]=tree[ls]+tree[rs];
}
pii operator*(pii u,int v){return {u.fi*v%mod,u.se*v%mod};}
void upd1(int nd,int w){tree[nd]=tree[nd]*w,laz[nd]=laz[nd]*w%mod;}
void down1(int nd){if(laz[nd]!=1)upd1(ls,laz[nd]),upd1(rs,laz[nd]),laz[nd]=1;}
void updata1(int nd,int l,int r,int ql,int qr,int w){
	if(ql>qr)return ;
	if(l>=ql&&r<=qr)return upd1(nd,w);
	down1(nd);
	if(ql<=mid)updata1(ls,l,mid,ql,qr,w);
	if(qr>mid)updata1(rs,mid+1,r,ql,qr,w);
	tree[nd]=tree[ls]+tree[rs];
}
void modif1(int nd,int l,int r,int p,pii w){
	if(l==r){tree[nd]=tree[nd]+w;return ;}
	down1(nd);
	if(p<=mid)modif1(ls,l,mid,p,w);
	else modif1(rs,mid+1,r,p,w);
	tree[nd]=tree[ls]+tree[rs];
}
pii query(int nd,int l,int r,int ql,int qr){
	if(ql>qr)return {0,0};
	if(l>=ql&&r<=qr)return tree[nd];
	down(nd);down1(nd);
	if(qr<=mid)return query(ls,l,mid,ql,qr);
	if(ql>mid)return query(rs,mid+1,r,ql,qr);
	return query(ls,l,mid,ql,qr)+query(rs,mid+1,r,ql,qr);
}
void work(){
	n=read();
	for(int i=1;i<=n;i++)a[i]=read(),lsh[++len]=a[i];
	for(int i=1;i<=n;i++)b[i]=read(),lsh[++len]=b[i];
	sort(lsh+1,lsh+len+1),len=unique(lsh+1,lsh+len+1)-lsh-1;
	for(int i=1;i<=n;i++){
		a[i]=lower_bound(lsh+1,lsh+len+1,a[i])-lsh;
		b[i]=lower_bound(lsh+1,lsh+len+1,b[i])-lsh;
		if(a[i]>b[i])swap(a[i],b[i]);
	}
	pw[0]=1;for(int i=1;i<=n;i++)pw[i]=pw[i-1]*2%mod;
	for(int i=1;i<=n;i++){
		f[i][0]=t.que(a[i]),f[i][1]=t.que(b[i]);
		t.upd(1,-inf),t.upd(a[i]+1,inf);t.upd(b[i]+1,1);
	}
	t.clr();for(int i=n;i;i--){
		g[i][0]=t.que(a[i]),g[i][1]=t.que(b[i]);
		t.upd(1,-inf),t.upd(a[i]+1,inf);t.upd(b[i]+1,1);
	}
	for(int i=1;i<=n;i++){
		f[i][0]=f[i][0]<0?0:pw[f[i][0]];
		f[i][1]=f[i][1]<0?0:pw[f[i][1]];
		g[i][0]=g[i][0]<0?0:pw[g[i][0]];
		g[i][1]=g[i][1]<0?0:pw[g[i][1]];
	}
	build(1,1,len);
	for(int i=1;i<=n;i++){
		pii res1=query(1,1,len,1,a[i]-1),res2=query(1,1,len,1,b[i]-1);
		(ans+=pw[n-i]*(res1.fi*i%mod+res1.se+res2.fi*i%mod+res2.se))%=mod;
		updata1(1,1,len,1,a[i]-1,0);
		updata1(1,1,len,b[i],len,2);
		modif1(1,1,len,a[i],{f[i][0]*lsh[a[i]]%mod,f[i][0]*lsh[a[i]]%mod*(mod-i-1)%mod});
		modif1(1,1,len,b[i],{f[i][1]*lsh[b[i]]%mod,f[i][1]*lsh[b[i]]%mod*(mod-i-1)%mod});
	}
	build(1,1,len);
	for(int i=1;i<=n;i++){
		(ans+=pw[n-i]*(query(1,1,len,1,a[i]-1).se+query(1,1,len,1,b[i]-1).se))%=mod;
		updata(1,1,len,1,a[i]-1,{0,0});
		updata(1,1,len,a[i],b[i]-1,{1,mod-lsh[a[i]]});
		updata(1,1,len,b[i],len,{2,2*mod-lsh[a[i]]-lsh[b[i]]});
		modif(1,1,len,a[i],{f[i][0],0});
		modif(1,1,len,b[i],{f[i][1],0});
	}
	// for(int i=n;i;i--){
		// pii mul={1,0};
		// for(int j=i-1;j;j--){
			// if(i-1>j)(ans+=g[i][0]*pw[j-1]%mod*mul.se*((a[j]>a[i])+(b[j]>a[i])))%=mod;
			// if(a[j]>a[i])break;
			// if(b[j]>a[i])mul=mul*mkp(1ll,lsh[a[i]]-lsh[a[j]]);
			// else mul=mul*mkp(2ll,lsh[a[i]]*2-lsh[a[j]]-lsh[b[j]]);
		// }
		// mul={1,0};
		// for(int j=i-1;j;j--){
			// if(i-1>j)(ans+=g[i][1]*pw[j-1]%mod*mul.se*((a[j]>b[i])+(b[j]>b[i])))%=mod;
			// if(a[j]>b[i])break;
			// if(b[j]>b[i])mul=mul*mkp(1ll,lsh[b[i]]-lsh[a[j]]);
			// else mul=mul*mkp(2ll,lsh[b[i]]*2-lsh[a[j]]-lsh[b[j]]);
		// }
	// }
	build(1,1,len);
	for(int i=n;i;i--){
		pii res1=query(1,1,len,1,a[i]-1),res2=query(1,1,len,1,b[i]-1);
		(ans+=pw[i-1]*(res1.fi*(mod-i-1)%mod+res1.se+res2.fi*(mod-i-1)%mod+res2.se))%=mod;
		updata1(1,1,len,1,a[i]-1,0);
		updata1(1,1,len,b[i],len,2);
		modif1(1,1,len,a[i],{g[i][0]*lsh[a[i]]%mod,g[i][0]*lsh[a[i]]%mod*i%mod});
		modif1(1,1,len,b[i],{g[i][1]*lsh[b[i]]%mod,g[i][1]*lsh[b[i]]%mod*i%mod});
	}
	build(1,1,len);
	for(int i=n;i;i--){
		(ans+=pw[i-1]*(query(1,1,len,1,a[i]-1).se+query(1,1,len,1,b[i]-1).se))%=mod;
		updata(1,1,len,1,a[i]-1,{0,0});
		updata(1,1,len,a[i],b[i]-1,{1,mod-lsh[a[i]]});
		updata(1,1,len,b[i],len,{2,2*mod-lsh[a[i]]-lsh[b[i]]});
		modif(1,1,len,a[i],{g[i][0],0});
		modif(1,1,len,b[i],{g[i][1],0});
	}
	// for(int i=1;i<=n;i++)cout<<f[i][0]<<" "<<f[i][1]<<" "<<g[i][0]<<" "<<g[i][1]<<"\n";
	// for(int i=1;i<=n;i++){
		// pii mul={1,0};
		// for(int j=i+1;j<=n;j++){
			// if(i+1<j){
				// if(a[i]==a[j])(ans+=f[i][0]*g[j][0]%mod*mul.se)%=mod;
				// if(a[i]==b[j])(ans+=f[i][0]*g[j][1]%mod*mul.se)%=mod;
			// }
			// if(a[j]>a[i])break;
			// if(b[j]>a[i])mul=mul*mkp(1ll,lsh[a[i]]-lsh[a[j]]);
			// else mul=mul*mkp(2ll,lsh[a[i]]*2-lsh[a[j]]-lsh[b[j]]);
		// }
		// mul={1,0};
		// for(int j=i+1;j<=n;j++){
			// if(i+1<j){
				// if(b[i]==a[j])(ans+=f[i][1]*g[j][0]%mod*mul.se)%=mod;
				// if(b[i]==b[j])(ans+=f[i][1]*g[j][1]%mod*mul.se)%=mod;
			// }
			// if(a[j]>b[i])break;
			// if(b[j]>b[i])mul=mul*mkp(1ll,lsh[b[i]]-lsh[a[j]]);
			// else mul=mul*mkp(2ll,lsh[b[i]]*2-lsh[a[j]]-lsh[b[j]]);
		// }
	// }
	build(1,1,len);
	for(int i=1;i<=n;i++){
		pii res1=query(1,1,len,a[i],a[i]),res2=query(1,1,len,b[i],b[i]);
		(ans+=g[i][0]*(res1.fi*i%mod+res1.se))%=mod;
		(ans+=g[i][1]*(res2.fi*i%mod+res2.se))%=mod;
		updata1(1,1,len,1,a[i]-1,0);
		updata1(1,1,len,b[i],len,2);
		modif1(1,1,len,a[i],{f[i][0]*lsh[a[i]]%mod,f[i][0]*lsh[a[i]]%mod*(mod-i-1)%mod});
		modif1(1,1,len,b[i],{f[i][1]*lsh[b[i]]%mod,f[i][1]*lsh[b[i]]%mod*(mod-i-1)%mod});
	}
	build(1,1,len);
	for(int i=1;i<=n;i++){
		(ans+=g[i][0]*query(1,1,len,a[i],a[i]).se)%=mod;
		(ans+=g[i][1]*query(1,1,len,b[i],b[i]).se)%=mod;
		updata(1,1,len,1,a[i]-1,{0,0});
		updata(1,1,len,a[i],b[i]-1,{1,mod-lsh[a[i]]});
		updata(1,1,len,b[i],len,{2,2*mod-lsh[a[i]]-lsh[b[i]]});
		modif(1,1,len,a[i],{f[i][0],0});
		modif(1,1,len,b[i],{f[i][1],0});
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