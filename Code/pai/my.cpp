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
const int maxn=2000100;
const int inf=1e9;
bool mbe;

int n,q,a[maxn],ans;
int num;
int nxt[maxn],val[maxn];
#define pl(x) (x<<1)
#define pr(x) (((x+1)<<1)-1)
#define bel(x) (x>>1)
void init(int id){
	int l=pl(id),r=pr(id);
	val[id]=a[l];for(int i=l+1;i<=r;i++)val[id]=max(val[id],a[i]);
	for(int i=l;i<=r;i++)nxt[i]=0;
	for(int i=l,mx=l;i<=r;i++){
		mx=max(mx,a[i]);
		if(mx==i)nxt[i]=i;
	}
	if(!nxt[r])nxt[r]=r+1;
	for(int i=r-1;i>=l;i--)if(!nxt[i])nxt[i]=nxt[i+1];
}
#define mid ((l+r)>>1)
#define ls nd<<1
#define rs nd<<1|1
int mx[maxn<<2],to[maxn<<2];
int query(int nd,int l,int r,int w){
	// cout<<l<<" "<<r<<" "<<w<<endl;
	if(l==r){
		if(w<pl(l))return pl(l)-1;
		if(w>pr(l))return pr(l)+1;
		return nxt[w];		
	}
	if(w<=mx[ls]){
		int res=query(ls,l,mid,w);
		if(res==pr(mid)+1)return to[ls];
		else return res;
	}
	else{
		return query(rs,mid+1,r,w);
	}
}
void up(int nd,int l,int r){
	mx[nd]=max(mx[ls],mx[rs]);
	to[ls]=query(rs,mid+1,r,mx[ls]);
}
void build(int nd,int l,int r){
	if(l==r){mx[nd]=val[l];return ;}
	build(ls,l,mid),build(rs,mid+1,r);
	up(nd,l,r);
}
void modif(int nd,int l,int r,int p){
	if(l==r){mx[nd]=val[l];return ;}
	if(p<=mid)modif(ls,l,mid,p);
	else modif(rs,mid+1,r,p);
	up(nd,l,r);
}
int query(int nd,int l,int r,int p,int &w){
	if(l>=p){
		if(w<=mx[nd]){
			int res=query(nd,l,r,w);w=max(w,mx[nd]);
			return res;
		}
		else{
			return r+1;
		}
	}
	if(p<=mid){
		int res=query(ls,l,mid,p,w);
		if(res<=mid)return res;
		return query(rs,mid+1,r,p,w);
	}
	else return query(rs,mid+1,r,p,w);
}
void work(){
	read();n=read();q=read();
	for(int i=1;i<=n;i++)a[i]=max(read(),i);
	num=n>>1;
	for(int i=0;i<=num;i++)init(i);
	build(1,0,num);
	while(q--){
		int o=read();
		if(o==1){
			int u=read()^ans,v=max(read()^ans,u);
			a[u]=v;init(bel(u));
			modif(1,0,num,bel(u));
		}
		else{
			int p=read()^ans,w=a[p];
			int id=bel(p),r=pr(id);
			while(p<=r){
				w=max(w,a[p]);
				if(w==p)break;
				p++;
			}
			if(bel(p)==id)write(ans=p),puts("");
			else write(ans=query(1,0,num,id+1,w)),puts("");
			ans=0;
		}
	}
}

bool med;
signed main(){
	// freopen("ds.in","r",stdin);
	// freopen("ds.out","w",stdout);
	
	cerr<<(&mbe-&med)/1024.0/1024.0<<"\n";
	
	int T=1;
	while(T--)work();
}