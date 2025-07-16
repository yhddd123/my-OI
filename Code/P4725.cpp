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
const int maxn=200010;
const int inf=1e9;

int n;
inline int ksm(int a,int b=mod-2){
    int res=1;
    while(b){
        if(b&1)res=res*a%mod;
        a=a*a%mod;
        b>>=1;
    }
    return res;
}
int fac[maxn],inv[maxn],ni[maxn];
int C(int m,int n){return fac[m]*inv[n]%mod*inv[m-n]%mod;}
void inc(int &u,int v){((u+=v)>=mod)&&(u-=mod);}
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
    vector<int> f,g;
    void cdqln(int l,int r){
        if(l==r){g[l]=ni[l]*(f[l]*l%mod-g[l]+mod)%mod;return ;}
        int mid=l+r>>1;
        cdqln(l,mid);
        vector<int> ff(mid-l+1),gg(r-l+1);
        for(int i=l;i<=mid;i++)ff[i-l]=g[i]*i%mod;
        for(int i=0;i<=r-l;i++)gg[i]=f[i];
        ff=mul(ff,gg);
        for(int i=mid+1;i<=r;i++)inc(g[i],ff[i-l]);
        cdqln(mid+1,r);
    }
    vector<int> ln(vector<int> a){
        int n=a.size()-1;
        f.resize(n+1);g.resize(n+1);
        for(int i=0;i<=n;i++)f[i]=a[i],g[i]=0;
        g[0]=0;cdqln(1,n);
        return g;
    }
}
void work(){
    n=read()-1;
    fac[0]=1;for(int i=1;i<=n;i++)fac[i]=fac[i-1]*i%mod;
    inv[n]=ksm(fac[n]);for(int i=n-1;~i;i--)inv[i]=inv[i+1]*(i+1)%mod;
    ni[0]=1;for(int i=1;i<=n;i++)ni[i]=fac[i-1]*inv[i]%mod;
    vector<int> a(n+1);
    for(int i=0;i<=n;i++)a[i]=read();
    a=poly::ln(a);
    for(int i=0;i<=n;i++)printf("%lld ",a[i]);
}

int T;
signed main(){
    // freopen("A.in","r",stdin);
    // freopen(".out","w",stdout);
    
    T=1;
    while(T--)work();
}