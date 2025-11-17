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
const int maxn=400010;
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
int fac[maxn],inv[maxn],ni[maxn];
int C(int m,int n){
    if(n<0|m<0||m<n)return 0;
    return fac[m]*inv[n]%mod*inv[m-n]%mod;}
void init(int n){
    fac[0]=1;for(int i=1;i<=n;i++)fac[i]=fac[i-1]*i%mod;
    inv[n]=ksm(fac[n]);for(int i=n-1;~i;i--)inv[i]=inv[i+1]*(i+1)%mod;
    ni[0]=ni[1]=1;for(int i=2;i<=n;i++)ni[i]=(mod-mod/i)*ni[mod%i]%mod;
}
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
        ntt(a,1);ntt(b,1);
        for(int i=0;i<k;i++)a[i]=a[i]*b[i]%mod;
        ntt(a,-1);a.resize(n+m+1);
        return a;
    }
}
int n;
int x[maxn],y[maxn];
void work(){
	n=read();init(n);
	// for(int i=0;i<n;i++)x[i]=read(),y[i]=read();
	for(int i=0;i<n;i++)x[i]=(read()%mod+mod)%mod,y[i]=(read()%mod+mod)%mod;
	vector<int> ff(2*n),gg(n);
	vector<int> f(n+1),g(n+1);
	for(int i=0;i<2*n;i++)ff[i]=x[i%n];
	for(int i=0;i<n;i++)gg[i]=y[n-i-1];
	ff=poly::mul(ff,gg);
	for(int i=1;i<=n;i++)(g[i]+=ff[n-1+i])%=mod;
	for(int i=0;i<2*n;i++)ff[i]=y[i%n];
	for(int i=0;i<n;i++)gg[i]=x[n-i-1];
	ff=poly::mul(ff,gg);
	for(int i=1;i<=n;i++)(g[i]+=mod-ff[n-1+i])%=mod;
	reverse(g.begin(),g.end());
	// for(int i=0;i<=n;i++){
		// for(int j=0;j<n;j++)(g[i]+=x[j]*y[(j+i)%n]+mod-x[(j+i)%n]*y[j]%mod)%=mod;
	// }
	// for(int i=0;i<=n;i++)cout<<g[i]<<" ";cout<<"\n";
	for(int i=1;i<=n;i++)f[i]=(n-i-1)*g[i]%mod;
	for(int i=1;i<=n;i++)(g[i]+=g[i-1])%=mod;
	for(int i=1;i<=n;i++)(f[i]+=2*g[n-i-1])%=mod;
	vector<int> ans(n+1);
	ff.clear(),gg.clear();
	ff.resize(n+1),gg.resize(n+1);
	for(int i=0;i<=n-2;i++)ff[i]=f[i]*fac[n-i-2]%mod;
	for(int i=0;i<=n;i++)gg[i]=inv[i];
	ff=poly::mul(ff,gg);
	for(int i=3;i<=n;i++)ans[i]=inv[i-3]*ff[n-i+1]%mod;
	for(int i=3;i<=n;i++)printf("%lld\n",ans[i]*ksm(i)%mod);
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