#include<bits/stdc++.h>
#define int long long
#define mod 998244353ll
#define pii pair<int,int>
#define fi first
#define se second
#define pb push_back
using namespace std;
inline int read(){
    int x=0,fl=1;char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')fl=-1;ch=getchar();}
    while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    return x*fl;
}
const int maxn=100010;
const int inf=1e9;
bool mbe;

int n,m;
inline int ksm(int a,int b=mod-2){
    int ans=1;
    while(b){
        if(b&1)ans=ans*a%mod;
        a=a*a%mod;
        b>>=1;
    }
    return ans;
}
inline void inc(int &u,int v){((u+=v)>=mod)&&(u-=mod);}
namespace poly{
    int gen=3,invg=ksm(3);
    int to[maxn<<2];
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
int fac[maxn],inv[maxn];
inline int C(int m,int n){return fac[m]*inv[n]%mod*inv[m-n]%mod;}
void work(){
    n=read();m=read();
    fac[0]=1;for(int i=1;i<=n+1;i++)fac[i]=fac[i-1]*i%mod;
    inv[n+1]=ksm(fac[n+1]);for(int i=n;~i;i--)inv[i]=inv[i+1]*(i+1)%mod;
    vector<int> f(n+1);
    for(int i=0;i<=n;i++)f[i]=read();
    vector<int> ff(n+1),gg(n+1);
    for(int i=0;i<=n;i++)ff[i]=f[i]*fac[i]%mod;
    reverse(ff.begin(),ff.end());
    for(int i=0;i<=n;i++)gg[i]=inv[i];
    ff=poly::mul(ff,gg);ff.resize(n+1);
    reverse(ff.begin(),ff.end());
    for(int i=0;i<=n;i++)f[i]=ff[i]*inv[i]%mod;
    for(int i=0;i<=n;i++)f[i]=f[i]*ksm(fac[i]*inv[i+1]%mod,m)%mod;
    for(int i=0;i<=n;i++)ff[i]=f[i]*fac[i]%mod;
    reverse(ff.begin(),ff.end());
    for(int i=0;i<=n;i++)gg[i]=((i&1)?mod-1:1)*inv[i]%mod;
    ff=poly::mul(ff,gg);ff.resize(n+1);
    reverse(ff.begin(),ff.end());
    for(int i=0;i<=n;i++)f[i]=ff[i]*inv[i]%mod;
    for(int i=0;i<=n;i++)printf("%lld ",f[i]);
}

bool med;
int T;
signed main(){
    // freopen("A.in","r",stdin);
    // freopen("A.out","w",stdout);
    
    // cerr<<(&mbe-&med)/1024.0/1024.0<<"\n";
    
    T=1;
    while(T--)work();
}