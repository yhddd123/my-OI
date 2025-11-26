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
static char buf[1000000],*p1=buf,*p2=buf;
#define getchar() p1==p2&&(p2=(p1=buf)+fread(buf,1,1000000,stdin),p1==p2)?EOF:*p1++
inline int read(){int x=0,f=1;char c=getchar();while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}while(c>='0'&&c<='9'){x=(x<<3)+(x<<1)+c-48;c=getchar();}return x*f;}
inline void write(int x){static char buf[20];static int len=-1;if(x<0)putchar('-'),x=-x;do buf[++len]=x%10,x/=10;while(x);while(len>=0)putchar(buf[len--]+48);}
const int maxn=19;
const int inf=1e9;
bool mbe;

int n;
inline void inc(int &u,int v){((u+=v)>=mod)&&(u-=mod);}
void fwtor1(int *a,int n,int fl=1){
	for(int l=2;l<=n;l<<=1){
		int k=l>>1;
		for(int i=0;i<n;i+=l){
			for(int j=i;j<i+k;j++)inc(a[j+k],a[j]);
		}
	}
}
void fwtor2(int *a,int n,int fl=1){
	for(int l=2;l<=n;l<<=1){
		int k=l>>1;
		for(int i=0;i<n;i+=l){
			for(int j=i;j<i+k;j++)inc(a[j+k],mod-a[j]);
		}
	}
}
int ff[maxn+1][1<<maxn],gg[maxn+1][1<<maxn],hh[maxn+1][1<<maxn],ni[maxn+1];
void xormul(int *a,int *b,int *c,int n){
	for(int i=0;i<=n;i++){
		for(int s=0;s<(1<<n);s++)ff[i][s]=gg[i][s]=0;
	}
	for(int s=0;s<(1<<n);s++)ff[__builtin_popcount(s)][s]=a[s];
	for(int s=0;s<(1<<n);s++)gg[__builtin_popcount(s)][s]=b[s];
	for(int i=0;i<=n;i++)fwtor1(ff[i],1<<n);
	for(int i=0;i<=n;i++)fwtor1(gg[i],1<<n);
	for(int i=0;i<=n;i++){
		for(int s=0;s<(1<<n);s++)hh[i][s]=0;
		for(int j=0;j<=i;j++){
			for(int s=0;s<(1<<n);s++)(hh[i][s]+=ff[j][s]*gg[i-j][s])%=mod;
		}
	}
	for(int i=0;i<=n;i++)fwtor2(hh[i],1<<n);
	for(int s=0;s<(1<<n);s++)c[s]=hh[__builtin_popcount(s)][s];
}
int f[1<<maxn],g[1<<maxn];
void work(){
	n=read();
	for(int s=0;s<(1<<n);s++)f[s]=read();
	for(int s=0;s<(1<<n);s++)g[s]=read();
	xormul(f,g,f,n);
	for(int s=0;s<(1<<n);s++)write(f[s]),putchar(' ');
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