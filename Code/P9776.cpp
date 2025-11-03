#include<bits/stdc++.h>
// #define int long long
#define mod 998244353ll
#define pii pair<int,int>
#define fi first
#define se second
#define pb push_back
#define db long double
#define mems(a,x) memset((a),(x),sizeof(a))
using namespace std;
static char buf[1000000],*p1=buf,*p2=buf;
#define getchar() p1==p2&&(p2=(p1=buf)+fread(buf,1,1000000,stdin),p1==p2)?EOF:*p1++
inline int read(){int x=0,f=1;char c=getchar();while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}while(c>='0'&&c<='9'){x=(x<<3)+(x<<1)+c-48;c=getchar();}return x*f;}
inline void write(int x){static char buf[20];static int len=-1;if(x<0)putchar('-'),x=-x;do buf[++len]=x%10,x/=10;while(x);while(len>=0)putchar(buf[len--]+48);}
const int maxn=2000010;
const int inf=1e9;
bool mbe;

int n,q,m;
inline void inc(int &u,int v){((u+=v)>=mod)&&(u-=mod);}
#define ls lc[nd]
#define rs rc[nd]
#define mid ((l+r)>>1)
int lc[maxn],rc[maxn],ed[maxn],pl[maxn],pr[maxn];
int sum[maxn],tag[maxn],cnt[maxn],laz[maxn],len[maxn];
void build(int &nd,int l,int r){
	nd=++m;pl[nd]=l,pr[nd]=r;len[nd]=r-l+1;
	if(l!=r)build(ls,l,mid),build(rs,mid+1,r);
	ed[nd]=m;cnt[nd]=cnt[ls]+cnt[rs]+len[nd];
}
void updt(int nd,int w){inc(sum[nd],1ll*w*cnt[nd]%mod),inc(laz[nd],w),inc(tag[nd],w);}
void updl(int nd,int w){inc(sum[nd],1ll*w*len[nd]%mod),inc(laz[nd],w);}
void down(int nd){
	if(tag[nd])updt(ls,tag[nd]),updt(rs,tag[nd]),tag[nd]=0;
	if(laz[nd])updl(ls,laz[nd]),updl(rs,laz[nd]),laz[nd]=0;
}
void updata1(int nd,int l,int r,int ql,int qr,int w){
	// cout<<l<<" "<<r<<" "<<ql<<" "<<qr<<" "<<nd<<" "<<ed[nd]<<endl;
	if(ql<=nd&&ed[nd]<=qr)return updt(nd,w);
	if(ql<=nd&&nd<=qr)updl(nd,w);
	if(l==r)return ;
	down(nd);
	// cout<<ql<<" "<<qr<<" "<<nd<<" "<<ed[nd]<<"\n";
	// cout<<ls<<" "<<ed[ls]<<" "<<rs<<" "<<ed[rs]<<"\n";
	if(ql<=ed[ls])updata1(ls,l,mid,ql,qr,w);
	if(qr>=rs)updata1(rs,mid+1,r,ql,qr,w);
	inc(sum[nd]=sum[ls],sum[rs]);
}
void updata2(int nd,int l,int r,int ql,int qr,int w){
	if(l>=ql&&r<=qr)return updl(nd,w);
	down(nd);
	if(ql<=mid)updata2(ls,l,mid,ql,qr,w);
	if(qr>mid)updata2(rs,mid+1,r,ql,qr,w);
	inc(sum[nd]=sum[ls],sum[rs]);
}
int query(int nd,int l,int r,int ql,int qr){
	if(l>=ql&&r<=qr)return sum[nd];
	down(nd);
	if(qr<=mid)return query(ls,l,mid,ql,qr);
	if(ql>mid)return query(rs,mid+1,r,ql,qr);
	return (query(ls,l,mid,ql,qr)+query(rs,mid+1,r,ql,qr))%mod;
}
int mx[21][maxn];
int quemx(int l,int r){
	int k=__lg(r-l+1);
	return max(mx[k][l],mx[k][r-(1<<k)+1]);
}
void work(){
	n=read();
    for(int i=2;i<2*n;i++)read();
    q=read();
	int rt=0;build(rt,1,n);
	for(int i=1;i<2*n;i++)mx[0][i]=pr[i];
	for(int j=1;j<=20;j++){
		for(int i=1;i+(1<<j)-1<2*n;i++)mx[j][i]=max(mx[j-1][i],mx[j-1][i+(1<<j-1)]);
	}
	while(q--){
		int op=read();
		if(op==1){
			int l=read(),r=read(),w=read();
			updata1(1,1,n,l,r,w);
		}
		if(op==2){
			int l=read(),r=read(),w=read();
			r=quemx(l,r);l=pl[l];
			// cout<<l<<" "<<r<<"\n";
			updata2(1,1,n,l,r,w);
		}
		if(op==3){
			int l=read(),r=read();
			write(query(1,1,n,l,r)),puts("");
		}
	}
}

bool med;
int T;
signed main(){
	// freopen("tree.in","r",stdin);
	// freopen("tree.out","w",stdout);
	
	// cerr<<(&mbe-&med)/1024.0/1024.0<<"\n";
	
	T=1;
	while(T--)work();
}