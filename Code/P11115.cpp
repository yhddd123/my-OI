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
const int maxn=400010;
const int inf=1e9;
bool mbe;

int n;
struct nd{
	int l1,r1,l2,r2;
}a[maxn];
int lshx[maxn],lenx,lshy[maxn],leny;
vector<pii> add[maxn],del[maxn];
#define mid ((l+r)>>1)
#define ls nd<<1
#define rs nd<<1|1
struct node{
	int mn,num,vmn,vmx;
	int len,pre,suf,ans,pl,pr,lens;
}tree[maxn<<2];
node operator+(node u,node v){
	node res;res.mn=min(u.mn,v.mn);
	res.num=(u.mn==res.mn?u.num:0)+(v.mn==res.mn?v.num:0);
	res.vmn=min(u.mn==res.mn?u.vmn:inf,v.mn==res.mn?v.vmn:inf);
	res.vmx=max(u.mn==res.mn?u.vmx:0,v.mn==res.mn?v.vmx:0);
	res.len=u.len+v.len;
	if(u.mn<v.mn)res.pre=u.pre,res.suf=0,res.ans=u.ans,res.pl=u.pl,res.pr=u.pr,res.lens=u.lens;
	else if(v.mn<u.mn)res.pre=0,res.suf=v.suf,res.ans=v.ans,res.pl=v.pl,res.pr=v.pr,res.lens=v.lens;
	else{
		res.pre=(u.num==u.len?u.num+v.pre:u.pre),res.suf=(v.num==v.len?v.num+u.suf:v.suf);
		res.ans=max({u.ans,v.ans,u.suf+v.pre});
		res.pl=u.pl,res.pr=v.pr;res.lens=((v.lens==v.num&&v.lens==v.pre)?v.lens+u.suf:v.lens);
	}
	return res;
}
int tag[maxn<<2],tmn[maxn<<2],cov[maxn<<2];
void build(int nd,int l,int r){
	tree[nd]={0,lshy[r+1]-lshy[l],0,0,lshy[r+1]-lshy[l],lshy[r+1]-lshy[l],lshy[r+1]-lshy[l],lshy[r+1]-lshy[l],lshy[l],lshy[r+1]-1,lshy[r+1]-lshy[l]};tag[nd]=tmn[nd]=cov[nd]=0;
	if(l==r)return ;
	build(ls,l,mid),build(rs,mid+1,r);
}
void updt(int nd,int w,int mn,int c){
	if(tree[nd].mn==-mn)tree[nd].vmn=tree[nd].vmx=c,cov[nd]=c;
	tmn[nd]=min(tmn[nd],tag[nd]+mn);
	tree[nd].mn+=w;tag[nd]+=w;}
void down(int nd){
	updt(ls,tag[nd],tmn[nd],cov[nd]),updt(rs,tag[nd],tmn[nd],cov[nd]),tag[nd]=tmn[nd]=cov[nd]=0;
}
void updata(int nd,int l,int r,int ql,int qr,int w,int c){
	if(l>=ql&&r<=qr)return updt(nd,w,min(w,0),c);
	down(nd);
	if(ql<=mid)updata(ls,l,mid,ql,qr,w,c);
	if(qr>mid)updata(rs,mid+1,r,ql,qr,w,c);
	tree[nd]=tree[ls]+tree[rs];
	// cout<<l<<" "<<r<<" "<<tree[nd].mn<<" "<<tree[nd].vmn<<"\n";
}
int tim[maxn],suf[maxn],ed[maxn],mx[maxn];
bool vis[maxn];
int st[maxn],tp;
void query(int nd,int l,int r,int ql,int qr){
	if(tree[nd].mn>1)return ;
	if(l>=ql&&r<=qr){
		// cout<<nd<<" "<<l<<" "<<r<<" "<<tree[nd].mn<<" "<<tree[nd].num<<" "<<tree[nd].vmn<<" "<<tree[nd].vmx<<"\n";
		if(tree[nd].vmn==tree[nd].vmx){
			int c=tree[nd].vmn;
			if(!vis[c])st[++tp]=c,vis[c]=1;
			tim[c]+=tree[nd].num;
			int res=tree[nd].ans;
			if(ed[c]+1==tree[nd].pl)res=max(res,suf[c]+tree[nd].pre);
			else suf[c]=0;
			// cout<<lshx[c]<<" "<<l<<" "<<r<<" "<<ql<<" "<<qr<<" "<<tree[nd].num<<" "<<tree[nd].pl<<" "<<tree[nd].pr<<" "<<suf[c]<<" "<<res<<"\n";
			mx[c]=max(mx[c],res);
			if(tree[nd].lens){
				suf[c]=tree[nd].lens+((tree[nd].lens==tree[nd].num&&tree[nd].lens==tree[nd].pre)?suf[c]:0);
				ed[c]=tree[nd].pr;
			}
			return ;
		}
	}
	down(nd);
	if(ql<=mid)query(ls,l,mid,ql,qr);
	if(qr>mid)query(rs,mid+1,r,ql,qr);
}
vector<tuple<int,int,int,int>> ans;
int TT;
void work(){
	n=read();ans.clear();
	lenx=leny=0;for(int i=1;i<=n;i++){
		int l1=read(),l2=read(),r1=read(),r2=read();
		lshx[++lenx]=l1,lshx[++lenx]=r1+1;lshy[++leny]=l2,lshy[++leny]=r2+1;
		a[i]={l1,r1,l2,r2};
	}
	sort(lshx+1,lshx+lenx+1),lenx=unique(lshx+1,lshx+lenx+1)-lshx-1;
	sort(lshy+1,lshy+leny+1),leny=unique(lshy+1,lshy+leny+1)-lshy-1;
	for(int i=1;i<=lenx;i++)add[i].clear(),del[i].clear();
	for(int i=1;i<=n;i++){
		auto[l1,r1,l2,r2]=a[i];
		l1=lower_bound(lshx+1,lshx+lenx+1,l1)-lshx,r1=lower_bound(lshx+1,lshx+lenx+1,r1+1)-lshx-1;
		l2=lower_bound(lshy+1,lshy+leny+1,l2)-lshy,r2=lower_bound(lshy+1,lshy+leny+1,r2+1)-lshy-1;
		add[l1].pb({l2,r2}),del[r1+1].pb({l2,r2});
	}
	build(1,1,leny-1);
	for(int i=1;i<=lenx;i++){
		// cout<<lshx[i]-1<<"\n";
		for(auto[l,r]:add[i])updata(1,1,leny-1,l,r,1,i);
		sort(del[i].begin(),del[i].end(),[&](pii u,pii v){return u.se<v.se;});
		for(auto[l,r]:del[i]){
			query(1,1,leny-1,l,r);
			updata(1,1,leny-1,l,r,-1,0);
		}
		for(int j=1;j<=tp;j++){
			int p=st[j];
			ans.pb({lshx[p],lshx[i]-1,tim[p],mx[p]});
			tim[p]=mx[p]=suf[p]=ed[p]=vis[p]=0;
		}tp=0;
	}
	sort(ans.begin(),ans.end());
	write(ans.size());puts("");
	for(auto[l,r,t,k]:ans)write(l),putchar(' '),write(r),putchar(' '),write(t),putchar(' '),write(k),puts("");
}

bool med;
int T;
signed main(){
	// freopen(".in","r",stdin);
	// freopen(".out","w",stdout);
	
	// cerr<<(&mbe-&med)/1024.0/1024.0<<"\n";
	
	T=read();
	while(T--)work();
}