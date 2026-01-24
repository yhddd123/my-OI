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
inline int read(){int x=0;char c=getchar();while(c<'0'||c>'9')c=getchar();while(c>='0'&&c<='9'){x=(x<<3)+(x<<1)+c-48;c=getchar();}return x;}
inline void write(int x){static char buf[20];static int len=-1;if(x<0)putchar('-'),x=-x;do buf[++len]=x%10,x/=10;while(x);while(len>=0)putchar(buf[len--]+48);}
const int maxn=500600;
const int B=700;
const int inf=1e9;
bool mbe;

int n,q,a[maxn];
struct ask{
	int l,r,id;
}que[maxn];
int ans[maxn];
alignas(64) int val[maxn];
alignas(64) int b[maxn>>3],c[maxn>>3];
alignas(64) int d[maxn>>5],e[maxn>>5];
alignas(64) int f[maxn>>7],g[maxn>>7];
#pragma GCC optimize("Ofast,unroll-loops")
inline void chkmx(int &u,int v){u=(u>v)?u:v;}
inline void upd(int p,int w){
	p++;
	int p1=p>>3,p2=p>>5,p3=p>>7;
	val[p]+=w,b[p1]+=w,d[p2]+=w,f[p3]+=w;
	int s=0;
	int &vd=c[p1]=-inf;p1<<=3;s=0;
	chkmx(vd,s+val[p1]),s+=val[p1];
	chkmx(vd,s+val[p1+1]),s+=val[p1+1];
	chkmx(vd,s+val[p1+2]),s+=val[p1+2];
	chkmx(vd,s+val[p1+3]),s+=val[p1+3];
	chkmx(vd,s+val[p1+4]),s+=val[p1+4];
	chkmx(vd,s+val[p1+5]),s+=val[p1+5];
	chkmx(vd,s+val[p1+6]),s+=val[p1+6];
	chkmx(vd,s+val[p1+7]),s+=val[p1+7];
	int &ve=e[p2]=-inf;p2<<=2;s=0;
	chkmx(ve,s+c[p2]),s+=b[p2];
	chkmx(ve,s+c[p2+1]),s+=b[p2+1];
	chkmx(ve,s+c[p2+2]),s+=b[p2+2];
	chkmx(ve,s+c[p2+3]),s+=b[p2+3];
	int &vg=g[p3]=-inf;p3<<=2;s=0;
	chkmx(vg,s+e[p3]),s+=d[p3];
	chkmx(vg,s+e[p3+1]),s+=d[p3+1];
	chkmx(vg,s+e[p3+2]),s+=d[p3+2];
	chkmx(vg,s+e[p3+3]),s+=d[p3+3];
}
inline int calc(){
	int p=-1,t=0;
	for(int i=0,s=0;i<=(n>>7);i++){
		if(s+g[i]>=0)p=i,t=s;
		s+=f[i];
	}
	if(p==-1)return -1;
	int x=-1;
	int s=t;p<<=7;
	for(int i=p;i<p+128;i+=8){
		s+=val[i];if(s>=0)x=i;
		s+=val[i+1];if(s>=0)x=i+1;
		s+=val[i+2];if(s>=0)x=i+2;
		s+=val[i+3];if(s>=0)x=i+3;
		s+=val[i+4];if(s>=0)x=i+4;
		s+=val[i+5];if(s>=0)x=i+5;
		s+=val[i+6];if(s>=0)x=i+6;
		s+=val[i+7];if(s>=0)x=i+7;
	}
	return x;
}
int t[maxn];
void work(){
	n=read();q=read();
	for(int i=1;i<=n;i++)a[i]=read();
	reverse(a+1,a+n+1);
	for(int i=1;i<=q;i++){
		int l=read(),r=read();
		que[i]={n-r+1,n-l+1,i};
	}
	sort(que+1,que+q+1,[&](ask u,ask v){
		if(u.l/B==v.l/B)return ((u.l/B)&1)?u.r>v.r:u.r<v.r;
		return u.l<v.l;
	});
	for(int i=0;i<=n+1;i++)upd(i,-1);
	for(int i=1,l=1,r=0;i<=q;i++){
		while(r<que[i].r)upd(a[++r],1);
		while(l>que[i].l)upd(a[--l],1);
		while(r>que[i].r)upd(a[r--],-1);
		while(l<que[i].l)upd(a[l++],-1);
		ans[que[i].id]=calc();
		// cout<<i<<" "<<que[i].l<<" "<<que[i].r<<" "<<que[i].id<<" "<<ans[que[i].id]<<"\n";
	}
	for(int i=1;i<=q;i++)write(ans[i]),puts("");
}

bool med;
int T;
signed main(){
	// freopen("sequence.in","r",stdin);
	// freopen("sequence.out","w",stdout);
	
	// cerr<<(&mbe-&med)/1024.0/1024.0<<"\n";
	
	T=1;
	while(T--)work();
}