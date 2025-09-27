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

int n,k,p[maxn],ans=1;
bool vis[maxn];
int m,a[maxn];
vector<int> sovle(int l,int r){
    if(l==r){
        vector<int> g(a[l]),h(a[l]);
        for(int i=0;i<a[l];i++)g[i]=C(a[l],i)*((i&1)?mod-1:1)%mod;
        for(int i=0;i<a[l];i++)h[i]=ksm(i+1,a[l]-1);
        vector<int> f=poly::mul(g,h);f.resize(a[l]);
		// cout<<l<<" "<<r<<" "<<f.size()<<"\n";
        return f;
    }
    int mid=l+r>>1;
    vector<int> f=poly::mul(sovle(l,mid),sovle(mid+1,r));
    return f;
}
void work(){
    n=read();k=read();init(n);
    for(int i=1;i<=n;i++)p[i]=read();
    for(int i=1;i<=n;i++)if(!vis[i]){
        a[++m]=0;
        for(int x=i;!vis[x];x=p[x])vis[x]=1,++a[m];
        ans=ans*inv[a[m]]%mod;
        if(a[m]==1)m--;
    }
    ans=ans*fac[n]%mod;
    for(int i=1;i<=m;i++)ans=ans*a[i]%mod;
    if(m){
    	if(k<m)ans=0;
    	else{
		    vector<int> f=sovle(1,m);
		    ans=ans*f[k-m]%mod;
    	}
    }
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