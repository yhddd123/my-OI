// Problem: CF2029H Message Spread
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/CF2029H
// Memory Limit: 1000 MB
// Time Limit: 12000 ms
// Written by yhm.
// Start codeing:2026-01-20 19:30:55
// 
// Powered by CP Editor (https://cpeditor.org)

#include<bits/stdc++.h>
// #define int long long
// #define mod 998244353
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
const int maxn=21;
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
using mint=ModInt<998244353>;

int n,m;mint ans;
mint e[maxn][maxn];
mint f[1<<maxn-1],g[1<<maxn-1],tf[1<<maxn-1];
mint val[1<<maxn],ival[1<<maxn];
inline mint ban(int s,int t){return val[s|t]*ival[s]*ival[t];}
mint ff[maxn][1<<maxn-1],gg[maxn][1<<maxn-1];
void fmt1(mint *a,int n){
	for(int l=2;l<=n;l<<=1){
		int k=l>>1;
		for(int i=0;i<n;i+=l){
			for(int j=i;j<i+k;j++)a[j+k]+=a[j];
		}
	}
}
void fmt2(mint *a,int n){
	for(int l=2;l<=n;l<<=1){
		int k=l>>1;
		for(int i=0;i<n;i+=l){
			for(int j=i;j<i+k;j++)a[j+k]-=a[j];
		}
	}
}
vector<int> id[maxn];
void work(){
	n=read();m=read();
	for(int i=1;i<=m;i++){
		int u=read()-1,v=read()-1;mint p=read(),q=read();
		e[u][v]=e[v][u]=p/q;
	}
	val[0]=ival[0]=1;for(int s=1;s<(1<<n);s++){
		int k=__lg(s);
		val[s]=val[s^(1<<k)];
		for(int j=0;j<k;j++)if(s&(1<<j))val[s]=val[s]*(1-e[j][k]);
		ival[s]=(val[s]).inv();
	}
	for(int s=0;s+1<(1<<n-1);s++){
		g[s]=(1-ban(s<<1|1,(1<<n)-1-(s<<1|1))).inv();
	}
	f[0]=1;
	for(int s=0;s<(1<<n-1);s++)id[__builtin_popcount(s)].pb(s);
	ff[0][0]=f[0]*g[0]*ival[1];fmt1(ff[0],1<<n-1);
	for(int s=0;s<(1<<n-1);s++)gg[__builtin_popcount(s)][s]=val[(1<<n)-1-(s<<1)];
	for(int i=0;i<n-1;i++)fmt1(gg[i],1<<n-1);
	for(int i=1;i<n-1;i++){
		for(int j=0;j<i;j++){
			for(int s=0;s<(1<<n-1);s++)ff[i][s]+=ff[j][s]*gg[i-j][s];
		}
		fmt2(ff[i],1<<n-1);
		for(int s:id[i])f[s]=ff[i][s]*ival[(1<<n)-1-(s<<1|1)];
		for(int j=0;j<i;j++){
			for(int s:id[j])tf[s]=f[s]*ban((s<<1|1),(1<<n)-1-(s<<1|1))*g[s]+(!!j)*f[s];
		}
		for(int s:id[i])tf[s]=0;
		fmt1(tf,1<<n-1);
		for(int s:id[i])f[s]-=tf[s];
		// for(int s:id[i])cout<<s<<" "<<f[s]<<"\n";
		for(int s:id[i])ff[i][s]=f[s]*g[s]*ival[s<<1|1];
		fmt1(ff[i],1<<n-1);
	}
	for(int s=0;s<(1<<n-1);s++)ans+=f[s]*g[s];
	printf("%d\n",ans.x);
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