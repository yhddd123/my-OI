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
const int maxn=150010;
const int inf=1e9;
bool mbe;

inline int ksm(int a,int b=mod-2){
    int ans=1;
    while(b){
        if(b&1)ans=ans*a%mod;
        a=a*a%mod;
        b>>=1;
    }
    return ans;
}
int fac[maxn],inv[maxn];
int C(int m,int n){
    if(n<0|m<0||m<n)return 0;
    return fac[m]*inv[n]%mod*inv[m-n]%mod;}
void init(int n){
    fac[0]=1;for(int i=1;i<=n;i++)fac[i]=fac[i-1]*i%mod;
    inv[n]=ksm(fac[n]);for(int i=n-1;~i;i--)inv[i]=inv[i+1]*(i+1)%mod;
}
int n,a[maxn],p,ans;
int t[maxn];
inline void inc(int &u,int v){((u+=v)>=mod)&&(u-=mod);}
namespace poly{
    int gen=3,invg=ksm(3);
    int to[maxn<<3];
    void ntt(vector<int> &a,int fl){
        int n=a.size();
        for(int i=0;i<n;i++)if(i<to[i])swap(a[i],a[to[i]]);
        for(int l=2;l<=n;l<<=1){
            int bas=ksm(fl==1?gen:invg,(mod-1)/l),k=l>>1;
            for(int i=0;i<n;i+=l){
                int mul=1;
                for(int j=i;j<i+k;j++){
                    int val=a[j+k]*mul%mod;
                    inc(a[j+k]=a[j],mod-val);
                    inc(a[j],val);
                    mul=mul*bas%mod;
                }
            }
        }
        if(fl==-1){
            int inv=ksm(n);
            for(int i=0;i<n;i++)a[i]=a[i]*inv%mod;
        }
    }
    vector<int> mul(vector<int> a,vector<int> b){
        int n=a.size()-1,m=b.size()-1,k=1;
        while(k<n+m+1)k<<=1;
        a.resize(k);b.resize(k);
        for(int i=0;i<k;i++)to[i]=to[i>>1]>>1|((i&1)?(k>>1):0);
        poly::ntt(a,1);poly::ntt(b,1);
        for(int i=0;i<k;i++)a[i]=a[i]*b[i]%mod;
        poly::ntt(a,-1);a.resize(n+m+1);
        return a;
    }
}
namespace multipoint{
typedef std::vector <int> Poly;
const int N=maxn<<3;
const int p = 998244353;
inline int pls(int a,int b) { return a + b >= p ? a + b - p : a + b; }
inline int mus(int a,int b) { return a - b < 0 ? a - b + p : a - b; }
inline int prd(int a,int b) { return 1ll * a * b % p; }
inline int fastpow(int a,int b) {
    int r = 1;
    while(b) {
        if(b & 1) r = 1ll * r * a % p;
        a = 1ll * a * a % p;
        b >>= 1;
    }
    return r;
}

int rev[N];
void NTT(Poly &a) {
    int N = a.size();
    for(int i = 0;i < N;i++) rev[i] = (rev[i >> 1] >> 1) | ((i & 1) * N / 2);
    for(int i = 0;i < N;i++) if(i > rev[i]) std::swap(a[i],a[rev[i]]);
    for(int n = 2, m = 1;n <= N;m = n, n <<= 1) {
        int g1 = fastpow(3,(p - 1) / n), t1, t2;
        for(int l = 0;l < N;l += n) {
            int g = 1;
            for(int i = l;i < l + m;i++) {
                t1 = a[i], t2 = prd(a[i + m],g);
                a[i] = pls(t1,t2), a[i + m] = mus(t1,t2);
                g = prd(g,g1);
            }
        }
    }
    return;
}

void INTT(Poly &a) {
    NTT(a), std::reverse(a.begin() + 1,a.end()); 
    int invN = fastpow(a.size(),p - 2);
    for(int i = 0;i < (int)a.size();i++) a[i] = prd(a[i],invN);
}

Poly Mul(Poly a,Poly b) {
    int n = a.size() + b.size() - 1, N = 1;
    while(N < (int)(a.size() + b.size())) N <<= 1;
    a.resize(N), b.resize(N), NTT(a), NTT(b);
    for(int i = 0;i < N;i++) a[i] = prd(a[i],b[i]);
    INTT(a), a.resize(n);
    return a;
}

Poly MulT(Poly a,Poly b) {
    int n = a.size(), m = b.size(); 
    std::reverse(b.begin(),b.end()), b = Mul(a,b);
    for(int i = 0;i < n;i++) a[i] = b[i + m - 1];
    return a;
}

Poly tmp;
Poly Inv(Poly a,int n) {
    if(n == 1) return Poly(1,fastpow(a[0],p - 2));
    Poly b = Inv(a,(n + 1) / 2);
    int N = 1; while(N <= 2 * n) N <<= 1;
    tmp.resize(N), b.resize(N);
    for(int i = 0;i < n;i++) tmp[i] = a[i];
    for(int i = n;i < N;i++) tmp[i] = 0;
    NTT(tmp), NTT(b);
    for(int i = 0;i < N;i++) b[i] = mus(prd(2,b[i]),prd(prd(b[i],b[i]),tmp[i]));
    INTT(b), b.resize(n); return b;
}

int n,m; Poly a,f,v;

#define lc(k) k << 1
#define rc(k) k << 1 | 1
const int NODE = N * 4;
Poly Q[NODE];

void Init(Poly &a,int k,int l,int r) {
    if(l == r) {
        Q[k].resize(2);
        Q[k][0] = 1, Q[k][1] = mus(0,a[l]);
        return;
    }
    int m = (l + r) / 2;
    Init(a,lc(k),l,m), Init(a,rc(k),m + 1,r);
    Q[k] = Mul(Q[lc(k)],Q[rc(k)]);
    return;
}

void Multipoints(int k,int l,int r,Poly F,Poly &g) {
    F.resize(r - l + 1);
    if(l == r) return void(g[l] = F[0]);
    int m = (l + r) / 2;
    Multipoints(lc(k),l,m,MulT(F,Q[rc(k)]),g);
    Multipoints(rc(k),m + 1,r,MulT(F,Q[lc(k)]),g);
    return;
}

void Multipoint(Poly f,Poly a,Poly &v,int n) {
    f.resize(n + 1), a.resize(n);
    Init(a,1,0,n - 1), v.resize(n);
    Multipoints(1,0,n - 1,MulT(f,Inv(Q[1],n + 1)),v);
    return;
}
}
vector<int> cdq(int l,int r){
    if(l==r){return {a[l],-1};}
    int mid=l+r>>1;
    vector<int> f=cdq(l,mid),g=cdq(mid+1,r);
    return poly::mul(f,g);
}
void sovle(){
	vector<int> f=cdq(1,p);
	vector<int> g(a[p+1]+1);
	for(int i=0;i<=a[p+1];i++)g[i]=i;
	// for(int v:f)cout<<v<<" ";cout<<"\n";
	// for(int v:g)cout<<v<<" ";cout<<"\n";
	vector<int> res;
	multipoint::Multipoint(f,g,res,max(f.size(),g.size()));
	for(int i=0;i<=a[p+1];i++)(ans+=((i&1)?mod-1:1)*C(a[p+1],i)%mod*res[i])%=mod;
}
void work(){
	n=read();init(n);
	for(int i=1;i<=n;i++)a[i]=read();
	sort(a+1,a+n+1,greater<int>());
	for(int i=1;i<=n;i++){
		if(a[i+1]<=i){p=i;break;}
	}
	sovle();
	for(int i=1;i<=n;i++)t[a[i]]++;
	for(int i=n;i;i--)t[i]+=t[i+1];
	for(int i=1;i<=n;i++)a[i]=t[i];
	sovle();
	int fac=1;for(int i=1;i<=p;i++)fac=fac*i%mod;
	ans-=fac,ans%=mod,ans+=mod,ans%=mod;
	printf("%lld %lld\n",p,ans);
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