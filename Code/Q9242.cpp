#include<bits/stdc++.h>
#define int long long
#define ull unsigned long long
#define mod 998244353ll
#define pii pair<int,int>
#define fi first
#define se second
#define mems(x,y) memset(x,y,sizeof(x))
#define pb push_back
using namespace std;
const int maxn=200010;
const int inf=1e18;
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch-48);ch=getchar();}
	return x*f;
}
bool Mbe;

int n,q,k,b,a[maxn],c[maxn];
ull bas,pw[maxn];
#define mid (l+r>>1)
#define ls nd<<1
#define rs nd<<1|1
ull h1[maxn<<2],h2[maxn<<2];
void build(int nd,int l,int r){
	if(l==r){
		h1[nd]=c[l];
		h2[nd]=k-c[l];
		return ;
	}
	build(ls,l,mid),build(rs,mid+1,r);
	h1[nd]=h1[ls]*pw[r-mid]+h1[rs];
	h2[nd]=h2[ls]+h2[rs]*pw[mid-l+1];
}
void updata(int nd,int l,int r,int p){
	if(l==r){
		h1[nd]=c[l];
		h2[nd]=k-c[l];
		return ;
	}
	if(p<=mid)updata(ls,l,mid,p);
	else updata(rs,mid+1,r,p);
	h1[nd]=h1[ls]*pw[r-mid]+h1[rs];
	h2[nd]=h2[ls]+h2[rs]*pw[mid-l+1];
}
ull query(int nd,int l,int r,int ql,int qr,bool fl){
	if(l>=ql&&r<=qr){
		if(!fl)return h1[nd];
		else return h2[nd];
	}
	if(qr<=mid)return query(ls,l,mid,ql,qr,fl);
	if(ql>mid)return query(rs,mid+1,r,ql,qr,fl);
	ull val=0;
	if(!fl)val=query(ls,l,mid,ql,qr,fl)*pw[min(r,qr)-mid]+query(rs,mid+1,r,ql,qr,fl);
	else val=query(ls,l,mid,ql,qr,fl)+query(rs,mid+1,r,ql,qr,fl)*pw[mid-max(l,ql)+1];
	// cout<<l<<" "<<r<<" "<<fl<<" "<<val<<"\n";
	return val;
}
#undef mid
mt19937 rnd(1);
bool check(int p,int x){
	// cout<<p<<" "<<x<<" "<<p+2<<" "<<p+x<<" "<<p-x+1<<" "<<p-1<<"\n";
	// cout<<query(1,1,n,p+2,p+x,0)<<" "<<query(1,1,n,p-x+1,p-1,1)<<"\n";
	return query(1,1,n,p+2,p+x,0)==query(1,1,n,p-x+1,p-1,1);
}
void work(){
	n=read();q=read();k=read();b=read();
	for(int i=1;i<=n;i++)a[i]=read(),c[i]=a[i]-a[i-1];
	bas=rnd();pw[0]=1;for(int i=1;i<=n;i++)pw[i]=pw[i-1]*bas;
	// cout<<bas<<"\n";
	build(1,1,n);
	while(q--){
		int op=read();
		if(op==1){
			int l=read(),r=read(),w=read();
			c[l]+=w,updata(1,1,n,l);
			if(r<n)c[r+1]-=w,updata(1,1,n,r+1);
		}
		else{
			int p=read();
			if(c[p]+c[p+1]!=k+b)puts("0");
			else{
				int l=2,r=min(p-1,n-p),res=1;
				while(l<=r){
					int mid=l+r>>1;
					if(check(p,mid))l=mid+1,res=mid;
					else r=mid-1;
				}
				printf("%lld\n",res);
			}
		}
	}
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
