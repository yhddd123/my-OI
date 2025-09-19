#include<bits/stdc++.h>
#define int long long
#define mod 1000000007ll
#define pii pair<int,int>
#define fi first
#define se second
#define pb push_back
#define db long double
using namespace std;
inline int read(){
    int x=0,fl=1;char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')fl=-1;ch=getchar();}
    while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    return x*fl;
}
const int maxn=30010;
const int inf=1e9;
bool mbe;

namespace mtt{
int _mod=mod;
struct cp{
	db a,b;
	cp(db u=0,db v=0){a=u,b=v;}
	cp operator+(const cp&tmp)const{return {a+tmp.a,b+tmp.b};}
	cp operator-(const cp&tmp)const{return {a-tmp.a,b-tmp.b};}
	cp operator*(const cp&tmp)const{return {a*tmp.a-b*tmp.b,a*tmp.b+b*tmp.a};}
};
const db pi=acos(-1);
int to[maxn<<3];
void fft(vector<cp> &a,int flag){
	int n=a.size();
	for(int i=0;i<n;i++)if(i<to[i])swap(a[i],a[to[i]]);
	for(int l=2;l<=n;l<<=1){
		cp bas=cp(cos(2*pi/l),flag*sin(2*pi/l));
		int k=l>>1;
		for(int i=0;i<n;i+=l){
			cp mul=cp(1,0);
			for(int j=i;j<i+k;j++){
				cp val=mul*a[j+k];
				a[j+k]=a[j]-val,a[j]=a[j]+val;
				mul=mul*bas;
			}
		}
	}
	if(flag==-1){
		for(int i=0;i<n;i++)a[i].a/=n,a[i].b/=n;
	}
}
const int B=(1<<15)-1;
int calc(db x){return (long long)(x+0.5)%_mod;}
vector<int> mul(vector<int> a,vector<int> b){
	int n=a.size()-1,m=b.size()-1,k=1;
	while(k<n+m+1)k<<=1;
	for(int i=0;i<k;i++)to[i]=(to[i>>1]>>1)|((i&1)?(k>>1):0);
	vector<cp> f(k),g(k),h(k);
	for(int i=0;i<=n;i++)f[i]=cp(a[i]&B,0),g[i]=cp(a[i]>>15,0);
	for(int i=0;i<=m;i++)h[i]=cp(b[i]&B,b[i]>>15);
	fft(f,1),fft(g,1),fft(h,1);
	for(int i=0;i<k;i++)f[i]=f[i]*h[i],g[i]=g[i]*h[i];
	fft(f,-1),fft(g,-1);
	vector<int> ans(n+m+1);
	for(int i=0;i<=n+m;i++)ans[i]=(1ll*calc(f[i].a)+(1ll*(calc(f[i].b)+calc(g[i].a))<<15ll)%_mod+(1ll*calc(g[i].b)<<30ll)%_mod)%_mod;
	return ans;
}
}
int n,k,ans;
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
int C(int m,int n){return fac[m]*inv[n]%mod*inv[m-n]%mod;}
vector<int> f[maxn];
vector<int> sovle(int n){
    if(f[n].size())return f[n];
    vector<int> g=sovle(n/2),h=sovle(n-n/2);
    for(int i=n/2;i<=k;i++)g[i]=g[i]*inv[i]%mod*ksm(2,(n-n/2)*i)%mod;
    for(int i=n-n/2;i<=k;i++)h[i]=h[i]*inv[i]%mod;
    // for(int v:g)cout<<v<<" ";cout<<"\n";
    // for(int v:h)cout<<v<<" ";cout<<"\n";
    f[n]=mtt::mul(g,h);f[n].resize(k+1);
    for(int i=n;i<=k;i++)f[n][i]=f[n][i]*fac[i]%mod;
    return f[n];
}
void work(){
    n=read();k=read();
    if(n>k){puts("0");return ;}
    fac[0]=1;for(int i=1;i<=k;i++)fac[i]=fac[i-1]*i%mod;
    inv[k]=ksm(fac[k]);for(int i=k-1;~i;i--)inv[i]=inv[i+1]*(i+1)%mod;
    f[1].resize(k+1);for(int i=1;i<=k;i++)f[1][i]=1;
    sovle(n);
    // for(int i=n;i<=k;i++)cout<<f[n][i]<<" ";cout<<"\n";
    for(int i=n;i<=k;i++)(ans+=f[n][i]*C(k,i))%=mod;
    printf("%lld\n",ans);
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