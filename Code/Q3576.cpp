#include<bits/stdc++.h>
#define ll long long
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
const int maxn=200010;
const int inf=1e9;
bool mbe;

int n,q,a[maxn];
#define mid ((l+r)>>1)
#define ls lc[nd]
#define rs rc[nd]
int num[maxn<<6];ll sum[maxn<<6];
int lc[maxn<<6],rc[maxn<<6],idx,rt[maxn];
void updata(int &nd,int l,int r,int p){
	int lst=nd;nd=++idx;ls=lc[lst],rs=rc[lst];
	num[nd]=num[lst]+1,sum[nd]=sum[lst]+p;
	if(l==r)return ;
	if(p<=mid)updata(ls,l,mid,p);
	else updata(rs,mid+1,r,p);
}
#define all rt[l-1],rt[r],1,inf
ll quesum(int ndl,int ndr,int l,int r,int ql,int qr){
	if(ql>qr)return 0;
	if(l>=ql&&r<=qr)return sum[ndr]-sum[ndl];
	if(qr<=mid)return quesum(lc[ndl],lc[ndr],l,mid,ql,qr);
	if(ql>mid)return quesum(rc[ndl],rc[ndr],mid+1,r,ql,qr);
	return quesum(lc[ndl],lc[ndr],l,mid,ql,qr)+quesum(rc[ndl],rc[ndr],mid+1,r,ql,qr);
}
int quenum(int ndl,int ndr,int l,int r,int ql,int qr){
	if(ql>qr)return 0;
	if(l>=ql&&r<=qr)return num[ndr]-num[ndl];
	if(qr<=mid)return quenum(lc[ndl],lc[ndr],l,mid,ql,qr);
	if(ql>mid)return quenum(rc[ndl],rc[ndr],mid+1,r,ql,qr);
	return quenum(lc[ndl],lc[ndr],l,mid,ql,qr)+quenum(rc[ndl],rc[ndr],mid+1,r,ql,qr);
}
int findr(int ndl,int ndr,int l,int r,int p){
	if(num[ndl]==num[ndr])return inf+1;	
	if(l==r)return l;
	if(p<=mid){
		int res=findr(lc[ndl],lc[ndr],l,mid,p);
		if(res==inf+1)return findr(rc[ndl],rc[ndr],mid+1,r,p);
		return res;
	}
	return findr(rc[ndl],rc[ndr],mid+1,r,p);
}
// int findp(int ndl,int ndr,int l,int r,int s){
	// if(sum[ndr]-sum[ndl]<s)return r;
	// if(l==r)return l-1;
	// if(sum[lc[ndr]]-sum[lc[ndl]]>=s)return findp(lc[ndl],lc[ndr],l,mid,s);
	// return findp(rc[ndl],rc[ndr],mid+1,r,s-(sum[lc[ndr]]-sum[lc[ndl]]));	
// }
int findp(int ndl,int ndr,int l,int r,int s){
	if(sum[ndr]-sum[ndl]<s)return r;
	while(l<r){
		if(sum[lc[ndr]]-sum[lc[ndl]]>=s){
			ndl=lc[ndl],ndr=lc[ndr];
			r=mid;
		}else{
			s-=sum[lc[ndr]]-sum[lc[ndl]];
			ndl=rc[ndl],ndr=rc[ndr];
			l=mid+1;
		}
	}
	return l-1;
}
void work(){
	n=read();q=read();
	for(int i=1;i<=n;i++)a[i]=read();
	for(int i=1;i<=n;i++)updata(rt[i]=rt[i-1],1,inf,a[i]);
	while(q--){
		int l=read(),r=read(),k=read(),lim=k;
		if(l==r){puts("1");continue;}
		int p=findp(all,k);ll s=quesum(all,1,p)-k;
		if(s<0){
			int nxt=findr(all,p+1);
			if(nxt<=inf){
				int num=quenum(all,nxt,nxt);
				if(num>1)lim=max(lim,nxt+1);
				else lim=max(lim,nxt);
				s+=quesum(all,p+1,nxt),p=nxt;
			}
		}
		// cout<<p<<" "<<s<<"\n";
		while(s<=inf){
			int lst=s;ll val=quesum(all,p+1,lst);
			if(!val){
				int nxt=findr(all,p+1);
				if(nxt==inf+1)break;
				lim=max(lim,nxt);
				s+=quesum(all,p+1,nxt),p=nxt;
			}
			else s+=val,p=lst;
		}
		int tmp=lim;
		p=findp(all,1),s=quesum(all,1,p);
		lim=max(lim,p+k);
		while(s<=inf){
			int lst=s;ll val=quesum(all,p+1,lst);
			if(!val){
				int nxt=findr(all,p+1);
				if(nxt>=tmp)break;
				lim=max(lim,nxt-(int)s+k);
				s+=quesum(all,p+1,nxt),p=nxt;
			}
			else s+=val,p=lst;
		}
		write(quenum(all,lim,inf));puts("");
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