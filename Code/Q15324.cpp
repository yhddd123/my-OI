#include<bits/stdc++.h>
#define ll long long
#define ull unsigned long long
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
inline void write(ull x){static char buf[40];static int len=-1;if(x<0)putchar('-'),x=-x;do buf[++len]=x%10,x/=10;while(x);while(len>=0)putchar(buf[len--]+48);}
const int maxn=200010;
const int B=1000;
const ll inf=1e18;
bool mbe;

int n,q;
int pl[maxn],pr[maxn],bel[maxn],num;
ll a[maxn],mn[maxn],mx[maxn],tag[maxn],cov[maxn];
bool fl[maxn];
ull smn[maxn],smx[maxn],smul[maxn];
void down(int id){
	int l=pl[id],r=pr[id];
	if(fl[id]){
		fl[id]=0;
		for(int i=l;i<=r;i++)a[i]=cov[id];cov[id]=0;
	}
	else{
		for(int i=l;i<=r;i++)a[i]+=tag[id];tag[id]=0;
	}
}
void init(int id){
	int l=pl[id],r=pr[id];
	for(int i=l;i<=r;i++){
		mn[i]=min(i==l?inf:mn[i-1],a[i]);
		mx[i]=max(i==l?-inf:mx[i-1],a[i]);
		smn[i]=(i==l?0:smn[i-1])+mn[i];
		smx[i]=(i==l?0:smx[i-1])+mx[i];
		smul[i]=(i==l?0:smul[i-1])+1ull*mn[i]*mx[i];
	}
}
void updata(int l,int r,int v){
	if(bel[l]==bel[r]){
		down(bel[l]);
		for(int i=l;i<=r;i++)a[i]+=v;
		init(bel[l]);
	}
	else{
		down(bel[l]);
		for(int i=l;i<=pr[bel[l]];i++)a[i]+=v;
		init(bel[l]);
		for(int i=bel[l]+1;i<bel[r];i++){
			if(fl[i])cov[i]+=v;
			else tag[i]+=v;
		}
		down(bel[r]);
		for(int i=pl[bel[r]];i<=r;i++)a[i]+=v;
		init(bel[r]);
	}
}
void cover(int l,int r,int v){
	if(bel[l]==bel[r]){
		down(bel[l]);
		for(int i=l;i<=r;i++)a[i]=v;
		init(bel[l]);
	}
	else{
		down(bel[l]);
		for(int i=l;i<=pr[bel[l]];i++)a[i]=v;
		init(bel[l]);
		for(int i=bel[l]+1;i<bel[r];i++)cov[i]=v,tag[i]=0,fl[i]=1;
		down(bel[r]);
		for(int i=pl[bel[r]];i<=r;i++)a[i]=v;
		init(bel[r]);
	}
}
ull calc(int id,ll &vmn,ll &vmx){
	int l=pl[id],r=pr[id];
	if(fl[id]){
		vmn=min(vmn,cov[id]);
		vmx=max(vmx,cov[id]);
		return 1ull*(r-l+1)*vmn*vmx;
	}
	int p1=lower_bound(mx+l,mx+r+1,vmx-tag[id])-mx,p2=lower_bound(mn+l,mn+r+1,vmn-tag[id],[&](ll u,ll v){return u>v;})-mn;
	ull res=0;
	if(p1<p2){
		res+=1ull*(p1-l)*vmn*vmx;
		res+=1ull*((p2==l?0:smx[p2-1])-(p1==l?0:smx[p1-1])+1ull*tag[id]*(p2-p1))*vmn;
		res+=1ull*(smul[r]-(p2==l?0:smul[p2-1]))+1ull*tag[id]*(1ull*(r-p2+1)*tag[id]+smn[r]-(p2==l?0:smn[p2-1])+smx[r]-(p2==l?0:smx[p2-1]));
	}
	else{
		res+=1ull*(p2-l)*vmn*vmx;
		res+=1ull*((p1==l?0:smn[p1-1])-(p2==l?0:smn[p2-1])+1ull*tag[id]*(p1-p2))*vmx;
		res+=1ull*(smul[r]-(p1==l?0:smul[p1-1]))+1ull*tag[id]*(1ull*(r-p1+1)*tag[id]+smn[r]-(p1==l?0:smn[p1-1])+smx[r]-(p1==l?0:smx[p1-1]));
	}
	vmn=min(vmn,mn[r]+tag[id]);
	vmx=max(vmx,mx[r]+tag[id]);
	return res;
}
ull que(int l,int r){
	if(bel[l]==bel[r]){
		down(bel[l]);
		ll vmn=inf,vmx=-inf;ull res=0;
		for(int i=l;i<=r;i++){
			vmn=min(vmn,a[i]);
			vmx=max(vmx,a[i]);
			res+=1ull*vmn*vmx;
		}
		init(bel[l]);
		return res;
	}
	else{
		ll vmn=inf,vmx=-inf;ull res=0;
		down(bel[l]);
		for(int i=l;i<=pr[bel[l]];i++){
			vmn=min(vmn,a[i]);
			vmx=max(vmx,a[i]);
			res+=1ull*vmn*vmx;
		}
		init(bel[l]);
		for(int i=bel[l]+1;i<bel[r];i++)res+=calc(i,vmn,vmx);
		// cout<<vmn<<" "<<vmx<<" "<<res<<"\n";
		down(bel[r]);
		for(int i=pl[bel[r]];i<=r;i++){
			vmn=min(vmn,a[i]);
			vmx=max(vmx,a[i]);
			res+=1ull*vmn*vmx;		
		}
		init(bel[r]);
		return res;
	}
}
void work(){
	n=read();q=read();
	for(int i=1;i<=n;i++)a[i]=read();
	for(int l=1,r;l<=n;l=r+1){
		r=min(l+B-1,n);++num;pl[num]=l,pr[num]=r;
		for(int j=l;j<=r;j++)bel[j]=num;
		init(num);
	}
	while(q--){
		int op=read(),l=read(),r=read();
		if(op==1){
			int v=read();
			updata(l,r,v);
		}
		if(op==2){
			int v=read();
			cover(l,r,v);
		}
		if(op==3){
			write(que(l,r)),puts("");
		}
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