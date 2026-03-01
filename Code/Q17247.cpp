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
const int maxn=510;
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

mint fac[maxn<<1],inv[maxn<<1];
mint C(int m,int n){
    if(n<0||m<0||m<n)return 0;
    return fac[m]*inv[n]*inv[m-n];}
void init(int n){
    fac[0]=1;for(int i=1;i<=n;i++)fac[i]=fac[i-1]*i;
    inv[n]=fac[n].inv();for(int i=n-1;~i;i--)inv[i]=inv[i+1]*(i+1);
}
mint calc(int x,int y,int xx,int yy){return C(xx-x+yy-y,xx-x);}
mint go(int b,int x,int y,int xx,int yy){//y=x+b
	if(y>x+b||yy>xx+b)return 0;
	return calc(x,y,xx,yy)-calc(y-b,x+b,xx,yy);
}
int n,m,a[maxn],b[maxn];
pii c[maxn];
vector<int> e[maxn];
mint f[maxn][maxn],g[maxn],tmp[maxn];
int st[maxn],tp;
void dfs(int u){
	for(int v:e[u])dfs(v);
	for(int d=1;d<=n+1;d++){
		int lim=b[u]-d-a[u]+1;
		if(!e[u].size()){
			f[u][d]=go(lim,a[u],b[u]-d,a[u]+d-1,b[u]-1);
			continue;
		}
		int lm=d;
		for(int j=1;j<=lm;j++){
			g[j]=go(lim,a[u],b[u]-d,a[e[u][0]]-1,b[e[u][0]]-j)*f[e[u][0]][j];
		}
		for(int i=1;i<e[u].size();i++){
			int v1=e[u][i-1],v2=e[u][i];
			lm=min(lm,a[v2]-a[v1]);
			for(int j=1;j<=lm;j++){
				for(int k=1;k<=b[v2]-b[v1];k++){
					tmp[k]+=g[j]*go(lim,a[v1]+j-1,b[v1],a[v2]-1,b[v2]-k)*f[v2][k];
				}
			}
			lm=b[v2]-b[v1];
			for(int j=1;j<=lm;j++)g[j]=tmp[j],tmp[j]=0;
		}
		for(int j=1;j<=lm;j++){
			f[u][d]+=g[j]*go(lim,a[e[u].back()]+j-1,b[e[u].back()],a[u]+d-1,b[u]-1);
		}
	}
	// for(int d=1;d<=n+1;d++)if(f[u][d])cout<<u<<" "<<d<<" "<<f[u][d]<<"\n";
}
void work(){
	n=read();m=read();init(2*n);
	for(int i=1;i<=m;i++)c[i]={read(),read()};sort(c+1,c+m+1);
	a[0]=0,b[0]=n+1;for(int i=1;i<=m;i++)a[i]=c[i].fi,b[i]=c[i].se;
	for(int i=0;i<=m;i++){
		while(tp&&b[st[tp]]<b[i])tp--;
		if(tp)e[st[tp]].pb(i);
		st[++tp]=i;
	}
	dfs(0);
	printf("%lld\n",f[0][n+1]);
}

bool med;
signed main(){
	// freopen(".in","r",stdin);
	// freopen(".out","w",stdout);
	
	cerr<<(&mbe-&med)/1024.0/1024.0<<"\n";
	
	int T=1;
	while(T--)work();
}