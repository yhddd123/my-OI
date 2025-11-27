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
const int maxn=500010;
const int inf=2e9;
bool mbe;

int n,q,a[maxn];
#define lb(x) (x&(-x))
struct bit{
	int tree[maxn];
	void upd(int x,int w){
		while(x)tree[x]+=w,x-=lb(x);
	}
	int que(int x){
		int res=0;
		while(x<=n)res+=tree[x],x+=lb(x);
		return res;
	}
}t1,t2;
void upd(int l,int w){
	t1.upd(l,w),t2.upd(l,l*w);
}
int que(int k){
	return t2.que(k)-t1.que(k)*(k-1);
}
#define mid ((l+r)>>1)
#define ls (nd<<1)
#define rs (nd<<1|1)
int mn[maxn<<2];
int pl[maxn<<2],pr[maxn<<2],pos[maxn];
void build(int nd,int l,int r){
	pl[nd]=l,pr[nd]=r;
	if(l==r){mn[nd]=a[l];pos[l]=nd;return ;}
	build(ls,l,mid),build(rs,mid+1,r);
	mn[nd]=min(mn[ls],mn[rs]);
}
void modif(int nd,int l,int r,int p){
	if(l==r){mn[nd]--;return ;}
	if(p<=mid)modif(ls,l,mid,p);
	else modif(rs,mid+1,r,p);
	mn[nd]=min(mn[ls],mn[rs]);
}
int findl(int p,int w){
	int nd=pos[p];
	while(nd){
		int lst=nd;nd>>=1;
		if(lst==rs){
			if(mn[ls]<w){nd=ls;break;}
		}
	}
	if(!nd)return 0;
	int l=pl[nd],r=pr[nd];
	while(l<r){
		if(mn[rs]<w)nd=rs,l=mid+1;
		else nd=ls,r=mid;
	}
	return l;
}
int findr(int p,int w){
	int nd=pos[p];
	while(nd){
		int lst=nd;nd>>=1;
		if(lst==ls){
			if(mn[rs]<w){nd=rs;break;}
		}
	}
	if(!nd)return n+1;
	int l=pl[nd],r=pr[nd];
	while(l<r){
		if(mn[ls]<w)nd=ls,r=mid;
		else nd=rs,l=mid+1;
	}
	return l;
}
pii st[19][maxn];
pii que(int l,int r){
	int k=__lg(r-l+1);
	return min(st[k][l],st[k][r-(1<<k)+1]);
}
void sovle(int l,int r,int lst){
	if(l>r)return ;
	pii mn=que(l,r);
	upd(r-l+1,mn.fi-lst);
	int p=l;
	while(p<=r){
		pii nw=que(p,r);
		if(nw.fi!=mn.fi){
			sovle(p,r,mn.fi);
			break;
		}
		if(p<nw.se)sovle(p,nw.se-1,mn.fi);
		p=nw.se+1;
	}
}
void work(){
	n=read();q=read();
	for(int i=1;i<=n;i++)a[i]=inf-read(),st[0][i]={a[i],i};
	for(int j=1;j<=18;j++){
		for(int i=1;i+(1<<j)-1<=n;i++)st[j][i]=min(st[j-1][i],st[j-1][i+(1<<j-1)]);
	}
	sovle(1,n,0);
	build(1,1,n);
	while(q--){
		char ch;ch=getchar();
		while(ch!='+'&&ch!='?')ch=getchar();
		int k=read();
		if(ch=='+'){
			int pl=findl(k,a[k])+1,pr=findr(k,a[k])-1;
			// cout<<k<<" "<<pl<<" "<<pr<<endl;
			upd(pr-pl+1,-1),upd(k-pl,1),upd(pr-k,1);
			a[k]--;modif(1,1,n,k);
		}
		else{
			printf("%lld\n",-que(k)+(n-k+1)*inf);
		}
	}
}

bool med;
int T;
signed main(){
	// freopen("ds.in","r",stdin);
	// freopen("ds.out","w",stdout);
	
	// cerr<<(&mbe-&med)/1024.0/1024.0<<"\n";
	
	T=1;
	while(T--)work();
}