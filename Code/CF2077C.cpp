#include<bits/stdc++.h>
// #define int long long
#define mod 998244353ll
using namespace std;
static char buf[1000000],*p1=buf,*p2=buf;
#define getchar() p1==p2&&(p2=(p1=buf)+fread(buf,1,1000000,stdin),p1==p2)?EOF:*p1++
inline int read(){int x=0,f=1;char c=getchar();while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}while(c>='0'&&c<='9'){x=(x<<3)+(x<<1)+c-48;c=getchar();}return x*f;}
inline void write(int x){static char buf[20];static int len=-1;if(x<0)putchar('-'),x=-x;do buf[++len]=x%10,x/=10;while(x);while(len>=0)putchar(buf[len--]+48);}
const int maxn=2500010;
const int inf=1e9;
bool mbe;

inline int ksm(int a,int b=mod-2){
    int ans=1;
    while(b){
        if(b&1)ans=1ll*ans*a%mod;
        a=1ll*a*a%mod;
        b>>=1;
    }
    return ans;
}
int fac[maxn],inv[maxn];
int C(int m,int n){
    if(n<0|m<0||m<n)return 0;
    return 1ll*fac[m]*inv[n]%mod*inv[m-n]%mod;}
void init(int n){
    fac[0]=1;for(int i=1;i<=n;i++)fac[i]=1ll*fac[i-1]*i%mod;
    inv[n]=ksm(fac[n]);for(int i=n-1;~i;i--)inv[i]=1ll*inv[i+1]*(i+1)%mod;
}
inline void inc(int &u,int v){((u+=v)>=mod)&&(u-=mod);}
inline void fix(int &u){u+=(u>>31)&mod;}
namespace poly{
    int gen=3,invg=ksm(3);
    int to[2<<23];
    void ntt(vector<int> &a,int fl){
        int n=a.size();
        for(int i=0;i<n;i++)if(i<to[i])swap(a[i],a[to[i]]);
        for(int l=2;l<=n;l<<=1){
            int bas=ksm(fl==1?gen:invg,(mod-1)/l),k=l>>1;
            for(int i=0;i<n;i+=l){
                int mul=1;
                for(int j=i;j<i+k;j++){
                    int val=1ll*a[j+k]*mul%mod;
                    fix(a[j+k]=a[j]-val);
                    fix(a[j]+=val-mod);
                    mul=1ll*mul*bas%mod;
                }
            }
        }
        if(fl==-1){
            int inv=ksm(n);
            for(int i=0;i<n;i++)a[i]=1ll*a[i]*inv%mod;
        }
    }
    vector<int> mul(vector<int> a,vector<int> b){
        int n=a.size()-1,m=b.size()-1,k=1;
        while(k<n+m+1)k<<=1;
        a.resize(k);b.resize(k);
        for(int i=0;i<k;i++)to[i]=to[i>>1]>>1|((i&1)?(k>>1):0);
        ntt(a,1);ntt(b,1);
        for(int i=0;i<k;i++)a[i]=1ll*a[i]*b[i]%mod;
        ntt(a,-1);a.resize(n+m+1);
        return a;
    }
}

int n,q;
int ans[maxn];
char s[maxn];
void work(){
	n=read();q=read();init(n);
	char ch=getchar();n=0;
	while(ch<'0'||ch>'1')ch=getchar();
	while(ch>='0'&&ch<='1'){
		s[++n]=ch;
		ch=getchar();
	}
	vector<int> f(n),g(n),val(n+1);
	if(n>=2)val[2]=1;
	for(int i=3,mul=1;i<=n;mul=1ll*mul*2%mod,i++)val[i]=(1ll*i*(i+1)/2-1)%mod*mul%mod;
	// for(int i=0;i<=n;i++)cout<<val[i]<<" ";cout<<"\n";
	for(int i=0;i<n;i++)f[i]=1ll*fac[n-i-1]*val[i]%mod;
	for(int i=0;i<n;i++)g[i]=inv[i];
	f=poly::mul(f,g);
	ans[0]=ans[n]=val[n];
	for(int i=1;i<n;i++)ans[i]=0;
	for(int i=1;i<n;i++){
		int res=1ll*f[i]*inv[n-i-1]%mod-mod;
		fix(ans[i]+=res),fix(ans[n-i]+=res);
	}
	// for(int i=0;i<=10;i++)cout<<f[i]<<" ";cout<<"\n";
	int s0=0;for(int i=1;i<=n;i++)s0+=s[i]=='0';
	while(q--){
		int p=read();
		s[p]=='0'?(s0--,s[p]='1'):(s0++,s[p]='0');
		write(ans[s0]),puts("");
	}
}

bool med;
int T;
signed main(){
	// freopen("hel.in","r",stdin);
	// freopen("hel.out","w",stdout);
	
	// cerr<<(&mbe-&med)/1024.0/1024.0<<"\n";
	
	T=read();
	while(T--)work();
}