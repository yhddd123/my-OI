#include<bits/stdc++.h>
#define int long long
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
const int maxn=255;
const int inf=1e9;
bool mbe;

using u32 = unsigned int;
using u64 = unsigned long long;
using u128 = __uint128_t;
struct Barrett {
	u64 b, m;
	Barrett() : b(), m() {}
	Barrett(u64 _b) : b(_b), m(-1ULL / _b) {}
	u32 reduce(u64 x) {
		u64 q = (u64)((u128(m) * x) >> 64), r = x - q * b;
		return r - b * (r >= b);
	}
} BA;
u32 mult(u32 x, u32 y) {
	return BA.reduce((u64)x * y);
}

int n,mod,kk;
inline int ksm(int a,int b=mod-2){
    int ans=1;
    while(b){
        if(b&1)ans=mult(ans,a);
        a=mult(a,a);
        b>>=1;
    }
    return ans;
}
int fac[maxn*maxn],inv[maxn*maxn],ni[maxn*maxn];
int C(int m,int n){
    if(n<0||m<0||m<n)return 0;
    return mult(fac[m],mult(inv[n],inv[m-n]));}
void init(int n){
    fac[0]=1;for(int i=1;i<=n;i++)fac[i]=mult(fac[i-1],i);
    inv[n]=ksm(fac[n]);for(int i=n-1;~i;i--)inv[i]=mult(inv[i+1],i+1);
    ni[0]=ni[1]=1;for(int i=2;i<=n;i++)ni[i]=mult((mod-mod/i),ni[mod%i]);
}
inline void inc(int &u,int v){((u+=v)>=mod)&&(u-=mod);}
int f[maxn][maxn*maxn],tmp[maxn*maxn];
int pw1[maxn][maxn*maxn],pw2[maxn][maxn*maxn];
int to[maxn*maxn];
int gen,invg;
bool chk(int v){
    for(int i=2;i*i<=mod-1;i++)if((mod-1)%i==0){
        if(ksm(v,i)==1)return 0;
        if(i*i!=mod-1&&ksm(v,(mod-1)/i)==1)return 0;
    }
    return 1;
}
void dft(int *a,int fl=1){
	int n=kk;
    for(int i=0;i<n;i++)if(i<to[i])swap(a[i],a[to[i]]);
    for(int l=2;l<=n;l<<=1){
        int bas=ksm(fl==1?gen:invg,(mod-1)/l),k=l>>1;
        for(int i=0;i<n;i+=l){
            int mul=1;
            for(int j=i;j<i+k;j++){
                int val=mult(a[j+k],mul);
                inc(a[j+k]=a[j],mod-val);
                inc(a[j],val);
                mul=mult(mul,bas);
            }
        }
    }
    if(fl==-1){
        int inv=ksm(n);
        for(int i=0;i<n;i++)a[i]=mult(a[i],inv);
    }
}
void work(){
	n=read();mod=read();BA=Barrett(mod);init(n*n);
	kk=1;while(kk<=n*(n-1)/2)kk<<=1;
	gen=2;while(!chk(gen))gen++;invg=ksm(gen);
    for(int i=0;i<kk;i++)to[i]=to[i>>1]>>1|((i&1)?(kk>>1):0);
	f[1][0]=1;
	dft(f[1]);
	for(int i=0;i<=n;i++){
		for(int j=0;j<=i;j++)pw1[i][j]=mult(((j&1)?mod-1:1),C(i,j));
		dft(pw1[i]);
	}
	for(int i=0;i<=n;i++){
		for(int j=0;j<=i*n;j++)pw2[i][j]=mult(((j&1)?mod-1:1),C(i*n,j));
		dft(pw2[i]);
	}
	for(int i=2;i<=n;i++){
		for(int j=1;j<i;j++){
			for(int k=0;k<kk;k++)tmp[k]=mult(f[j][k],f[i-j][k]);
			// dft(tmp,-1);
			// for(int k=0;k<kk;k++)cout<<tmp[k]<<" ";cout<<"\n";
			// dft(tmp,1);
			int v1=(j*(i-j)-1)%n,v2=(j*(i-j)-1)/n;
			for(int k=0;k<kk;k++)tmp[k]=mult(tmp[k],pw1[v1][k]);
			for(int k=0;k<kk;k++)tmp[k]=mult(tmp[k],pw2[v2][k]);
			for(int k=0;k<kk;k++)inc(f[i][k],tmp[k]);
		}
		dft(f[i],-1);
		for(int k=i*(i-1)/2;~k;k--)f[i][k+1]=mult(f[i][k],ni[k+1]);f[i][0]=0;
		// for(int k=0;k<=i*(i-1)/2;k++)cout<<f[i][k]<<" ";cout<<"\n";
		int ans=0;for(int k=0;k<=n*n;k++)inc(ans,f[i][k]);
		ans=mult(ans,fac[i]);
		ans=mult(ans,(mod+1)/2);
		printf("%lld\n",ans);
		dft(f[i],1);
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