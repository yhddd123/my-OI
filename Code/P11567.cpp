// Problem: P11567 建造军营 II
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P11567
// Memory Limit: 512 MB
// Time Limit: 5000 ms
// Written by yhm.
// Start codeing:2026-03-04 20:24:23
// 
// Powered by CP Editor (https://cpeditor.org)

#include<bits/stdc++.h>
// #define int long long
// #define mod 998244353ll
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
const int maxn=16;
const int inf=1e9;
bool mbe;

template <unsigned M_> struct ModInt {
  static constexpr unsigned M = M_;
  unsigned x;
  constexpr ModInt() : x(0U) {}
  constexpr ModInt(unsigned x_) : x(x_ % M) {}
  constexpr ModInt(unsigned long long x_) : x(x_ % M) {}
  constexpr ModInt(int x_) : x(((x_ %= static_cast<int>(M)) < 0) ? (x_ + static_cast<int>(M)) : x_) {}
  constexpr ModInt(long long x_) : x(((x_ %= static_cast<long long>(M)) < 0) ? (x_ + static_cast<long long>(M)) : x_) {}
  ModInt &operator+=(const ModInt &a) { x = ((x += a.x) >= M) ? (x - M) : x; return *this; }
  ModInt &operator-=(const ModInt &a) { x = ((x -= a.x) >= M) ? (x + M) : x; return *this; }
  ModInt &operator*=(const ModInt &a) { x = (static_cast<unsigned long long>(x) * a.x) % M; return *this; }
  ModInt &operator/=(const ModInt &a) { return (*this *= a.inv()); }
  ModInt pow(long long e) const {
    if (e < 0) return inv().pow(-e);
    ModInt a = *this, b = 1U; for (; e; e >>= 1) { if (e & 1) b *= a; a *= a; } return b;
  }
  ModInt inv() const {
    unsigned a = M, b = x; int y = 0, z = 1;
    for (; b; ) { const unsigned q = a / b; const unsigned c = a - q * b; a = b; b = c; const int w = y - static_cast<int>(q) * z; y = z; z = w; }
    return ModInt(y);
  }
  ModInt operator+() const { return *this; }
  ModInt operator-() const { ModInt a; a.x = x ? (M - x) : 0U; return a; }
  ModInt operator+(const ModInt &a) const { return (ModInt(*this) += a); }
  ModInt operator-(const ModInt &a) const { return (ModInt(*this) -= a); }
  ModInt operator*(const ModInt &a) const { return (ModInt(*this) *= a); }
  ModInt operator/(const ModInt &a) const { return (ModInt(*this) /= a); }
  template <class T> friend ModInt operator+(T a, const ModInt &b) { return (ModInt(a) += b); }
  template <class T> friend ModInt operator-(T a, const ModInt &b) { return (ModInt(a) -= b); }
  template <class T> friend ModInt operator*(T a, const ModInt &b) { return (ModInt(a) *= b); }
  template <class T> friend ModInt operator/(T a, const ModInt &b) { return (ModInt(a) /= b); }
  explicit operator bool() const { return x; }
  bool operator==(const ModInt &a) const { return (x == a.x); }
  bool operator!=(const ModInt &a) const { return (x != a.x); }
  friend std::ostream &operator<<(std::ostream &os, const ModInt &a) { return os << a.x; }
};
using mint=ModInt<1000000007>;

mint ff[maxn+1][1<<maxn],gg[maxn+1][1<<maxn];
mint tf[maxn+1],tg[maxn+1],th[maxn+1];
void fwt1(mint *a,int n){
	for(int l=2;l<=n;l<<=1){
		int k=l>>1;
		for(int i=0;i<n;i+=l){
			for(int j=i;j<i+k;j++)a[j+k]+=a[j];
		}
	}
}
void fwt2(mint *a,int n){
	for(int l=2;l<=n;l<<=1){
		int k=l>>1;
		for(int i=0;i<n;i+=l){
			for(int j=i;j<i+k;j++)a[j+k]-=a[j];
		}
	}
}
void xormul(mint *a,mint *b,mint *c,int n){
	for(int i=0;i<=n;i++){
		for(int s=0;s<(1<<n);s++)ff[i][s]=gg[i][s]=0;
	}
	for(int s=0;s<(1<<n);s++)ff[__builtin_popcount(s)][s]=a[s];
	for(int s=0;s<(1<<n);s++)gg[__builtin_popcount(s)][s]=b[s];
	for(int i=0;i<=n;i++)fwt1(ff[i],1<<n);
	for(int i=0;i<=n;i++)fwt1(gg[i],1<<n);
	for(int s=0;s<(1<<n);s++){
		for(int i=0;i<=n;i++)tf[i]=ff[i][s],tg[i]=gg[i][s],th[i]=0;
		for(int i=0;i<=n;i++){
			for(int j=0;j<=i;j++)th[i]+=tf[j]*tg[i-j];
		}
		for(int i=0;i<=n;i++)ff[i][s]=th[i];
	}
	for(int i=0;i<=n;i++)fwt2(ff[i],1<<n);
	for(int s=0;s<(1<<n);s++)c[s]=ff[__builtin_popcount(s)][s];
}
void xormul1(mint *a,mint *b,mint *c,int n){
	for(int i=0;i<=n;i++){
		for(int s=0;s<(1<<n);s++)ff[i][s]=gg[i][s]=0;
	}
	for(int s=0;s<(1<<n);s++)ff[__builtin_popcount(s)][s]=a[s];
	for(int s=0;s<(1<<n);s++)gg[__builtin_popcount(s)][s]=b[s];
	for(int i=0;i<=n;i++)fwt1(ff[i],1<<n);
	for(int i=0;i<=n;i++)fwt1(gg[i],1<<n);
	for(int s=0;s<(1<<n);s++){
		for(int i=0;i<=n;i++)tf[i]=ff[i][s],tg[i]=gg[i][s],th[i]=0;
		for(int i=0;i<=n;i++){
			for(int j=0;j<=i;j++)th[i]+=tf[j]*tg[i-j];
		}
		for(int i=0;i<=n;i++)ff[i][s]=th[i];
	}
	for(int i=0;i<=n;i++)fwt2(ff[i],1<<n);
	for(int s=0;s<(1<<n);s++)c[s]+=ff[__builtin_popcount(s)][s];
}
mint tmp[1<<maxn];
void exp(mint *a,int n){
	for(int s=0;s<(1<<n);s++)tmp[s]=a[s],a[s]=0;
	a[0]=1;for(int i=0;i<n;i++)xormul1(tmp+(1<<i),a,a+(1<<i),i);
}
void mulself(mint *a,mint *b,int n){
	for(int i=0;i<=n;i++){
		for(int s=0;s<(1<<n);s++)ff[i][s]=gg[i][s]=0;
	}
	for(int s=0;s<(1<<n);s++)ff[__builtin_popcount(s)][s]=a[s];
	for(int s=0;s<(1<<n);s++)gg[__builtin_popcount(s)][s]=b[s];
	for(int i=0;i<=n;i++)fwt1(ff[i],1<<n);
	for(int i=0;i<=n;i++)fwt1(gg[i],1<<n);
	for(int i=0;i<=n;i++){
		fwt2(gg[i],1<<n);
		for(int s=0;s<(1<<n);s++)if(__builtin_popcount(s)==i)gg[i][s]=a[s|(1<<n)]-gg[i][s];
		fwt1(gg[i],1<<n);
		for(int j=i+1;j<=n;j++){
			for(int s=0;s<(1<<n);s++)gg[j][s]+=gg[i][s]*ff[j-i][s];
		}
	}
	for(int i=0;i<=n;i++)fwt2(gg[i],1<<n);
	for(int s=0;s<(1<<n);s++)b[s]=gg[__builtin_popcount(s)][s];
}
void ln(mint *a,int n){
	for(int s=0;s<(1<<n);s++)tmp[s]=a[s],a[s]=0;
	for(int i=0;i<n;i++)mulself(tmp,a+(1<<i),i);
}

int n,k;
int e[maxn],num[1<<maxn];
char s[maxn+5];
pii a[maxn*maxn];
mint val[1<<maxn],f[1<<maxn],g[1<<maxn];
mint pw2[maxn*maxn],pw3[maxn*maxn];

mint tmpg[1<<maxn],tmph[1<<maxn];
void trans(mint *f,int c){
	for(int i=n-1;i;i--){
		for(int s=0;s<(1<<i);s++){
			for(int t=0;t<(1<<n-i-1);t++){
				tmpg[s|(t<<i)]=f[s|(1<<i)|(t<<i+1)];
				int num=__builtin_popcount(s&e[i]);
				tmph[s|(t<<i)]=c*num*f[s|(t<<i+1)];
			}
		}
		exp(tmph,n-1);
		xormul(tmpg,tmph,tmpg,n-1);
		for(int s=0;s<(1<<i);s++){
			for(int t=0;t<(1<<n-i-1);t++){
				f[s|(1<<i)|(t<<i+1)]=tmpg[s|(t<<i)];
			}
		}
	}
}

void work(){
	n=read();k=read();
	for(int i=0;i<n;i++){
		scanf("%s",s);
		for(int j=0;j<n;j++)if(s[j]=='1')e[i]|=1<<j;
	}
	for(int i=1;i<=k;i++)a[i]={read()-1,read()-1};
	for(int s=1;s<(1<<n);s++){
		int u=__lg(s);
		num[s]=num[s^(1<<u)]+__builtin_popcount(e[u]&s);
	}
	pw2[0]=1;for(int i=1;i<=n*(n-1)/2;i++)pw2[i]=pw2[i-1]*2;
	pw3[0]=1;for(int i=1;i<=n*(n-1)/2;i++)pw3[i]=pw3[i-1]*3;
	for(int s=0;s<(1<<n);s++)val[s]=pw2[num[s]];
	ln(val,n);
	// for(int s=0;s<(1<<n);s++)cout<<val[s]<<" ";cout<<"\n";
	for(int s=0;s<(1<<n);s++){
		bool fl=1;for(int i=1;i<=k;i++)fl&=(((s>>a[i].fi)&1)+((s>>a[i].se)&1)!=1);
		if(fl)f[s]=val[s];
	}
	trans(f,-1);
	// for(int s=0;s<(1<<n);s++)cout<<f[s]<<" ";cout<<"\n";
	for(int s=0;s<(1<<n);s++)g[s]=pw3[num[s]];
	ln(g,n);
	trans(g,-2);
	for(int s=0;s<(1<<n);s++){
		bool fl=1;for(int i=1;i<=k;i++)fl&=(((s>>a[i].fi)&1)+((s>>a[i].se)&1)==0);
		if(fl)f[s]=g[s];
	}
	trans(f,2);
	printf("%d\n",f[(1<<n)-1]);
}

bool med;
signed main(){
	// freopen(".in","r",stdin);
	// freopen(".out","w",stdout);
	
	cerr<<(&mbe-&med)/1024.0/1024.0<<"\n";
	
	int T=1;
	while(T--)work();
}