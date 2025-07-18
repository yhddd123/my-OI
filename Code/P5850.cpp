#include<bits/stdc++.h>
#define ll long long
#define mod 998244353ll
#define pii pair<int,int>
#define fi first
#define se second
#define pb push_back
using namespace std;
inline void write(int x){static char buf[20];static int len=-1;if(x<0)putchar('-'),x=-x;do buf[++len]=x%10,x/=10;while(x);while(len>=0)putchar(buf[len--]+48);}
const int maxn=500010;

int n,k;
inline int ksm(int a,int b=mod-2){
    int ans=1;
    while(b){
        if(b&1)ans=1ll*ans*a%mod;
        a=1ll*a*a%mod;
        b>>=1;
    }
    return ans;
}
int fac[maxn],inv[maxn],ni[maxn];
inline void inc(int &u,int v){((u+=v)>=mod)&&(u-=mod);}
namespace poly{
    int gen=3,invg=ksm(3);
    int w[21],iw[21],iv[21];
    int pww[21][1<<19],pwiw[21][1<<19];
    int to[21][1<<20];
    void init(){
        for(int i=1;i<=20;i++){
        	w[i]=ksm(gen,(mod-1)/(1<<i)),iw[i]=ksm(invg,(mod-1)/(1<<i));iv[i]=ksm(1<<i);
        	pww[i][0]=1;for(int j=1;j<(1<<i-1);j++)pww[i][j]=1ll*pww[i][j-1]*w[i]%mod;
        	pwiw[i][0]=1;for(int j=1;j<(1<<i-1);j++)pwiw[i][j]=1ll*pwiw[i][j-1]*iw[i]%mod;
        }
        for(int k=2,t=1;k<=(1<<20);k<<=1,t++){
        	for(int i=0;i<k;i++)to[t][i]=to[t][i>>1]>>1|((i&1)?(k>>1):0);
        }
    }
    void ntt(vector<int> &a,int fl){
        int n=a.size(),k=__lg(n);
        for(int i=0;i<n;i++)if(i<to[k][i])swap(a[i],a[to[k][i]]);
        for(int l=2,t=1;l<=n;l<<=1,t++){
            int k=l>>1;
            for(int i=0;i<n;i+=l){
                for(int j=i;j<i+k;j++){
                    int val=1ll*a[j+k]*(fl==1?pww[t][j-i]:pwiw[t][j-i])%mod;
                    inc(a[j+k]=a[j],mod-val);
                    inc(a[j],val);
                }
            }
        }
        if(fl==-1){
            int inv=iv[k];
            for(int i=0;i<n;i++)a[i]=1ll*a[i]*inv%mod;
        }
    }
    vector<int> mul(vector<int> a,vector<int> b){
        int n=a.size()-1,m=b.size()-1,k=1;
        while(k<n+m+1)k<<=1;
        a.resize(k);b.resize(k);
        ntt(a,1);ntt(b,1);
        for(int i=0;i<k;i++)a[i]=1ll*a[i]*b[i]%mod;
        ntt(a,-1);a.resize(n+m+1);
        return a;
    }
    vector<int> f,g;
    void cdqexp(int l,int r){
        if(l==r){g[l]=1ll*ni[l]*g[l]%mod;return ;}
        int mid=l+r>>1;
        cdqexp(l,mid);
        vector<int> ff(mid-l+1),gg(r-l+1);
        for(int i=l;i<=mid;i++)ff[i-l]=g[i];
        for(int i=0;i<=r-l;i++)gg[i]=f[i];
        ff=mul(ff,gg);
        for(int i=mid+1;i<=r;i++)inc(g[i],ff[i-l]);
        cdqexp(mid+1,r);
    }
    vector<int> exp(vector<int> a){
        int n=a.size()-1;
        f.resize(n+1);g.resize(n+1);
        for(int i=0;i<=n;i++)f[i]=1ll*a[i]*i%mod,g[i]=0;
        f[0]=0,g[0]=1;cdqexp(0,n);
        return g;
    }
}
vector<int> f;
int pw[maxn];
void cdq(int l,int r){
    if(l==r){
        f[l]=1ll*ni[l+1]*(pw[l+1]+mod-1ll*fac[l+1]*f[l]%mod)%mod;
        return ;
    }
    int mid=l+r>>1;
    cdq(l,mid);
    vector<int> ff(mid-l+1),gg(r-l+1);
    for(int i=l;i<=mid;i++)ff[i-l]=1ll*f[i]*inv[i]%mod;
    for(int i=0;i<=r-l;i++)gg[i]=inv[i+1];
    ff=poly::mul(ff,gg);
    for(int i=mid+1;i<=r;i++)inc(f[i],ff[i-l]);
    cdq(mid+1,r);
}
void work(){
	cin>>k>>n;f.resize(n+1);poly::init();
    fac[0]=1;for(int i=1;i<=n+1;i++)fac[i]=1ll*fac[i-1]*i%mod;
    inv[n+1]=ksm(fac[n+1]);for(int i=n;~i;i--)inv[i]=1ll*inv[i+1]*(i+1)%mod;
    ni[0]=1;for(int i=1;i<=n+1;i++)ni[i]=1ll*fac[i-1]*inv[i]%mod;
    pw[0]=1;for(int i=1;i<=n+1;i++)pw[i]=1ll*pw[i-1]*(k+1)%mod;
    cdq(0,n);
    f[0]=0;for(int i=1;i<=n;i++)f[i]=1ll*(((i+1)&1)?mod-1:1)*ni[i]%mod*f[i]%mod;
    f=poly::exp(f);
    for(int i=1;i<=n;i++)write(1ll*f[i]*fac[i]%mod),puts("");
}

int T;
signed main(){
    // freopen("A.in","r",stdin);
    // freopen(".out","w",stdout);
    
    
    T=1;
    while(T--)work();
}