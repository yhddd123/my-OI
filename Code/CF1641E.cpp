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
const int maxn=300010;
const int inf=1e9;
bool Mbe;

int n,m,ans;
int a[maxn],s[maxn],pw[maxn],ip[maxn];
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
int f[maxn];
void cdq(int l,int r){
    if(l==r){
        if(n+1<=l&&l<=2*n)f[l]=(pw[m]*f[l]+mod-min(l,3*n-l+1))%mod;
        return ;
    }
    int mid=l+r>>1;
    vector<int> ff(mid-l+1),gg(r-mid);
    for(int i=l;i<=mid;i++)ff[i-l]=pw[s[i]];
    for(int i=mid+1;i<=r;i++)gg[i-mid-1]=ip[s[i]];
    ff=poly::mul(ff,gg);
    for(int i=l+mid+1;i<=mid+r;i++)if(i&1)(f[(i+1)/2]+=ff[i-l-mid-1])%=mod;
    cdq(l,mid),cdq(mid+1,r);
}
void work(){
    n=read();m=read();
    for(int i=1;i<=n;i++)a[i+n]=read();
    for(int i=1;i<=m;i++)s[read()+n]++;
    for(int i=1;i<=3*n;i++)s[i]+=s[i-1];
    pw[0]=1;for(int i=1;i<=m;i++)pw[i]=pw[i-1]*2%mod;
    ip[0]=1;for(int i=1;i<=m;i++)ip[i]=ip[i-1]*(mod+1)/2%mod;
    cdq(0,3*n);
    for(int i=n+1;i<=2*n;i++)(ans+=a[i]*f[i])%=mod;
    printf("%lld\n",ans*ksm(pw[m]-1)%mod);
}

bool Med;
int T;
signed main(){
    // freopen("A.in","r",stdin);
    // freopen(".out","w",stdout);
    
    // cerr<<(&Mbe-&Med)/1024.0/1024.0<<"\n";
    
    T=1;
    while(T--)work();
}