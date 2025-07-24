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
const int maxn=1000010;
const int inf=1e9;

int p,n,m,a[maxn],ans;
bool vis[maxn];
inline int ksm(int a,int b=mod-2,int p=mod){
    int ans=1;
    while(b){
        if(b&1)ans=ans*a%p;
        a=a*a%p;
        b>>=1;
    }
    return ans;
}
inline void inc(int &u,int v){((u+=v)>=mod)&&(u-=mod);}
bool check(int x,int p){
    int n=p-1;
    for(int i=2;i*i<=n;i++)if(n%i==0){
        if(ksm(x,i,p)==1||ksm(x,n/i,p)==1)return 0;
    }
    return 1;
}
int getgen(int p){
    if(p==2)return 1;
    for(int i=2;i<p;i++)if(__gcd(i,p)==1&&check(i,p))return i;
}
int rnk[maxn];
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
    vector<int> mul(vector<int> &a,vector<int> &b){
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
void work(){
    p=read();n=read();
    for(int i=1;i<=n;i++)a[i]=read();
    m=read();
    for(int i=1;i<=m;i++)vis[read()]=1;
    auto calc=[&](int a,int b){
        if((3*a+b)%p==0||(3*a+2*b)%p==0)return p+1;
        return (((2*a+3*b)*(2*a+3*b)+5*a*a)%p*ksm((3*a+b)*(3*a+b)%p,p-2,p)+((2*a+5*b)*(2*a+5*b)+3*b*b)%p*ksm((3*a+2*b)*(3*a+2*b)%p,p-2,p))%p;
    };
    if(a[1]==0){
        for(int i=2;i<=n;i++)a[i-1]=a[i];n--;
        for(int i=1;i<=n;i++)ans+=vis[calc(0,a[i])]+vis[calc(a[i],0)];
    }
    // cout<<ans<<"\n";
    int gen=getgen(p);
    for(int i=0,mul=1;i<p-1;i++,mul=mul*gen%p)rnk[mul]=i;
    vector<int> f(p),g(p);
    for(int i=1;i<=n;i++)f[rnk[a[i]]]++;
    for(int i=1;i<=n;i++)g[p-1-rnk[a[i]]]++;
    f=poly::mul(f,g);
    for(int i=1;i<p;i++)if(vis[calc(i,1)])ans+=f[rnk[i]]+f[rnk[i]+p-1];
    printf("%lld\n",ans);
    // vector<int> t(p-1);
    // int res=0;
    // for(int i=1;i<=n;i++){
    //     for(int j=1;j<=n;j++)if(vis[calc(a[i],a[j])]){
    //         t[(rnk[a[i]]-rnk[a[j]]+p-1)%(p-1)]++;
    //         ++res;
    //     }
    // }
    // for(int i=0;i<p-1;i++)if(t[i])cout<<t[i]<<" "<<f[i]+f[i+p-1]<<"\n";
    // cout<<res<<"\n";
}

int T;
signed main(){
    // freopen("A.in","r",stdin);
    // freopen("A.out","w",stdout);
    
    T=1;
    while(T--)work();
}