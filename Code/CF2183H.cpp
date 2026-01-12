// Problem: CF2183H Minimise Cost
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/CF2183H
// Memory Limit: 500 MB
// Time Limit: 6000 ms
// Written by yhm.
// Start codeing:2026-01-12 15:41:24
// 
// Powered by CP Editor (https://cpeditor.org)

#include<bits/stdc++.h>
#define lll __int128
#define mod 998244353ll
#define pii pair<lll,int>
#define fi first
#define se second
#define pb push_back
#define db long double
#define mems(a,x) memset((a),(x),sizeof(a))
using namespace std;
static char buf[1000000],*p1=buf,*p2=buf;
#define getchar() p1==p2&&(p2=(p1=buf)+fread(buf,1,1000000,stdin),p1==p2)?EOF:*p1++
inline int read(){int x=0,f=1;char c=getchar();while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}while(c>='0'&&c<='9'){x=(x<<3)+(x<<1)+c-48;c=getchar();}return x*f;}
inline void write(lll x){static char buf[60];static int len=-1;if(x<0)putchar('-'),x=-x;do buf[++len]=x%10,x/=10;while(x);while(len>=0)putchar(buf[len--]+48);}
const int maxn=500010;
const lll inf=1e22;
bool mbe;

int n,k,p,a[maxn],b[maxn];
lll sum[maxn];
lll w(int l,int r){
	return (sum[r]-sum[l-1])*(b[r]-b[l-1]);
}
pii f[maxn];
struct node{
	int j,l,r;
}st[maxn];int h,t;
pii calc(int i,int j,lll lim){return {f[j].fi+w(j+1,i)-lim,f[j].se+1};}
pii calc(lll lim){
	f[0]={0,0};
	st[h=t=1]={0,1,n};
	// cout<<lim<<"\n";
	for(int i=1;i<=n;i++){
		f[i]=calc(i,st[h].j,lim);
		st[h].l++;
		while(h<=t&&st[h].l>st[h].r)h++;
		while(h<=t&&calc(st[t].l,st[t].j,lim)>=calc(st[t].l,i,lim))t--;
		if(h>t)st[++t]={i,i+1,n};
		else{
			int l=st[t].l,r=st[t].r,res=l;
			while(l<=r){
				int mid=l+r>>1;
				if(calc(mid,st[t].j,lim)<calc(mid,i,lim))res=mid,l=mid+1;
				else r=mid-1;
			}
			st[t].r=res;
			if(res+1<=n)st[++t]={i,res+1,n};
		}
		// write(f[i].fi),cout<<" "<<f[i].se<<"\n";
	}
	// for(int i=1;i<=n;i++){
		// f[i]={1e30,0};
		// for(int j=0;j<i;j++)f[i]=min(f[i],calc(i,j,lim));
		// // write(f[i].fi),cout<<" "<<f[i].se<<"\n";
	// }
	return f[n];
}
void work(){
	n=read();k=read();
	for(int i=1;i<=n;i++)a[i]=read();
	sort(a+1,a+n+1,greater<int>());
	for(int i=1;i<=n;i++)sum[i]=sum[i-1]+a[i];
	p=0;for(int i=1;i<=n;i++)if(a[i]>=0)p=i;
	if(p<k){
		write(sum[k-1]+(lll)(sum[n]-sum[k-1])*(n-k+1));puts("");
		return ;
	}
	reverse(a+1,a+n+1);
	int nn=0;
	for(int i=1;i<=n;i++){
		if(a[i]<0){
			if(i==1)sum[++nn]=a[i],b[nn]=1;
			else sum[nn]+=a[i],b[nn]++;
		}
		else sum[++nn]=a[i],b[nn]=1;
	}
	n=nn;
	for(int i=1;i<=n;i++)sum[i]=sum[i-1]+sum[i],b[i]+=b[i-1];
	lll l=-inf,r=inf,res=-inf;
	while(l<=r){
		lll mid=l+r>>1;
		if(calc(mid).se<=k)res=mid,l=mid+1;
		else r=mid-1;
	}
	// cout<<res<<"\n";
	pii dp=calc(res);
	write(dp.fi+k*res);puts("");
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