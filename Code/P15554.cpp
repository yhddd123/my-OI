// Problem: P15554 [CCPC 2025 哈尔滨站] Many Many Sequence Covering Problems
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P15554
// Memory Limit: 512 MB
// Time Limit: 4000 ms
// Written by yhm.
// Start codeing:2026-03-03 15:27:11
// 
// Powered by CP Editor (https://cpeditor.org)

#include<bits/stdc++.h>
// #define int long long
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
const int maxn=5010;
const int inf=1e9;
bool mbe;

template <unsigned M_> struct Int {
  static constexpr unsigned M = M_;
  unsigned x;
  constexpr Int() : x(0U) {}
  constexpr Int(unsigned x_) : x(x_ % M) {}
  constexpr Int(unsigned long long x_) : x(x_ % M) {}
  constexpr Int(int x_) : x(((x_ %= static_cast<int>(M)) < 0) ? (x_ + static_cast<int>(M)) : x_) {}
  constexpr Int(long long x_) : x(((x_ %= static_cast<long long>(M)) < 0) ? (x_ + static_cast<long long>(M)) : x_) {}
  Int &operator+=(const Int &a) { x = ((x += a.x) >= M) ? (x - M) : x; return *this; }
  Int &operator-=(const Int &a) { x = ((x -= a.x) >= M) ? (x + M) : x; return *this; }
  Int &operator*=(const Int &a) { x = (static_cast<unsigned long long>(x) * a.x) % M; return *this; }
  Int &operator/=(const Int &a) { return (*this *= a.inv()); }
  Int pow(long long e) const {
    if (e < 0) return inv().pow(-e);
    Int a = *this, b = 1U; for (; e; e >>= 1) { if (e & 1) b *= a; a *= a; } return b;
  }
  Int inv() const {
    unsigned a = M, b = x; int y = 0, z = 1;
    for (; b; ) { const unsigned q = a / b; const unsigned c = a - q * b; a = b; b = c; const int w = y - static_cast<int>(q) * z; y = z; z = w; }
    return Int(y);
  }
  Int operator+() const { return *this; }
  Int operator-() const { Int a; a.x = x ? (M - x) : 0U; return a; }
  Int operator+(const Int &a) const { return (Int(*this) += a); }
  Int operator-(const Int &a) const { return (Int(*this) -= a); }
  Int operator*(const Int &a) const { return (Int(*this) *= a); }
  Int operator/(const Int &a) const { return (Int(*this) /= a); }
  template <class T> friend Int operator+(T a, const Int &b) { return (Int(a) += b); }
  template <class T> friend Int operator-(T a, const Int &b) { return (Int(a) -= b); }
  template <class T> friend Int operator*(T a, const Int &b) { return (Int(a) *= b); }
  template <class T> friend Int operator/(T a, const Int &b) { return (Int(a) /= b); }
  explicit operator bool() const { return x; }
  bool operator==(const Int &a) const { return (x == a.x); }
  bool operator!=(const Int &a) const { return (x != a.x); }
  friend std::ostream &operator<<(std::ostream &os, const Int &a) { return os << a.x; }
};
using mint=Int<998244353>;

int n,m=5000,a[maxn],b[maxn],c[maxn],d[maxn],e[maxn];
mint f[maxn],g[maxn];
#define na(i) (a[i]<0?-a[i]+1:1)
#define nb(i) (b[i]<0?-b[i]+1:1)
#define nc(i) (c[i]<0?-c[i]+1:1)
#define nb2(i) (b[i]<0?(-b[i]+1)*(-b[i])/2:b[i])
#define nc2(i) (c[i]<0?(-c[i]+1)*(-c[i])/2:c[i])
#define nd(i) (d[i]<0?-d[i]+1:1)
#define ne(i) (e[i]<0?-e[i]+1:1)
mint sf[maxn],sfk[maxn],sfkk[maxn],sg[maxn],sgk[maxn];
#define que(a,l,r) ((a[r]+(l?-a[l-1]:0)))
void work(){
	n=read();
	for(int i=1;i<=n;i++)a[i]=read();
	for(int i=1;i<=n;i++)b[i]=read();
	for(int i=1;i<=n;i++)c[i]=read();
	for(int i=1;i<=n;i++)d[i]=read();
	for(int i=1;i<=n;i++)e[i]=read();
	f[0]=1;
	for(int i=1;i<=n+1;i++){
		sf[0]=f[0],sg[0]=g[0],sfk[0]=sfkk[0]=sgk[0]=0;
		f[0]=g[0]=0;
		for(int k=1;k<=m;k++){
			sf[k]=sf[k-1]+f[k];
			sfk[k]=sfk[k-1]+f[k]*k;
			sfkk[k]=sfkk[k-1]+f[k]*k*k;
			sg[k]=sg[k-1]+g[k];
			sgk[k]=sgk[k-1]+g[k]*k;
			f[k]=g[k]=0;
		}
		for(int j=(a[i]<0?0:a[i]);j<=abs(a[i]);j++){
			mint val=nc(i-1)*ne(i-1);int pl=max(0,j-abs(d[i])),pr=j;
			if(d[i]<0){
				f[j]+=que(sf,pl,pr)*nb(i)*(-d[i]+1-j)*val;
				f[j]+=que(sfk,pl,pr)*nb(i)*val;
				g[j]+=que(sf,pl,pr)*nb2(i)*j*(-d[i]+1-j)*val;
				g[j]+=que(sfk,pl,pr)*nb2(i)*(2*j+d[i]-1)*val;
				g[j]+=-que(sfkk,pl,pr)*nb2(i)*val;
				g[j]+=que(sg,pl,pr)*nb(i)*(-d[i]+1-j)*val;
				g[j]+=que(sgk,pl,pr)*nb(i)*val;
			}
			else{
				f[j]+=que(sf,pl,pr)*nb(i)*val;
				g[j]+=que(sf,pl,pr)*nb2(i)*j*val;
				g[j]+=-que(sfk,pl,pr)*nb2(i)*val;
				g[j]+=que(sg,pl,pr)*nb(i)*val;
			}
			val=nb(i)*nd(i);pl=j+1,pr=min(m,j+abs(e[i-1]));
			if(e[i-1]<0){
				f[j]+=que(sf,pl,pr)*nc(i-1)*(-e[i-1]+1+j)*val;
				f[j]+=-que(sfk,pl,pr)*nc(i-1)*val;
				g[j]+=-que(sf,pl,pr)*nc2(i-1)*j*(-e[i-1]+1+j)*val;
				g[j]+=que(sfk,pl,pr)*nc2(i-1)*(2*j-e[i-1]+1)*val;
				g[j]+=-que(sfkk,pl,pr)*nc2(i-1)*val;
				g[j]+=que(sg,pl,pr)*nc(i-1)*(-e[i-1]+1+j)*val;
				g[j]+=-que(sgk,pl,pr)*nc(i-1)*val;
			}
			else{
				f[j]+=que(sf,pl,pr)*nc(i-1)*val;
				g[j]+=-que(sf,pl,pr)*nc2(i-1)*j*val;
				g[j]+=que(sfk,pl,pr)*nc2(i-1)*val;
				g[j]+=que(sg,pl,pr)*nc(i-1)*val;
			}
		}
	}
	mint mul=1;for(int i=1;i<=n;i++)mul=mul*na(i)*nb(i)*nc(i)*nd(i)*ne(i);
	printf("%d %d\n",g[0],mul-f[0]);
}

bool med;
signed main(){
	// freopen(".in","r",stdin);
	// freopen(".out","w",stdout);
	
	cerr<<(&mbe-&med)/1024.0/1024.0<<"\n";
	
	int T=1;
	while(T--)work();
}