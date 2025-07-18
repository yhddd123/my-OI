#include<bits/stdc++.h>
#define ll long long
#define mod 998244353ll
#define pii pair<int,int>
#define fi first
#define se second
#define pb push_back
using namespace std;
static char buf[1000000],*p1=buf,*p2=buf;
#define getchar() p1==p2&&(p2=(p1=buf)+fread(buf,1,1000000,stdin),p1==p2)?EOF:*p1++
inline int read(){int x=0,f=1;char c=getchar();while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}while(c>='0'&&c<='9'){x=(x<<3)+(x<<1)+c-48;c=getchar();}return x*f;}
inline void write(int x){static char buf[20];static int len=-1;if(x<0)putchar('-'),x=-x;do buf[++len]=x%10,x/=10;while(x);while(len>=0)putchar(buf[len--]+48);}
const int maxn=1000010;
const int inf=1e9;

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
int ni[maxn];
void inc(int &u,int v){((u+=v)>=mod)&&(u-=mod);}
namespace poly{
    int gen=3,invg=ksm(3);
    int w[22],iw[22];
    int pww[22][1<<20],pwiw[22][1<<20];
    int to[22][1<<21];
    void init(){
        for(int i=1;i<=21;i++){
        	w[i]=ksm(gen,(mod-1)/(1<<i)),iw[i]=ksm(invg,(mod-1)/(1<<i));
        	pww[i][0]=1;for(int j=1;j<(1<<i-1);j++)pww[i][j]=1ll*pww[i][j-1]*w[i]%mod;
        	pwiw[i][0]=1;for(int j=1;j<(1<<i-1);j++)pwiw[i][j]=1ll*pwiw[i][j-1]*iw[i]%mod;
        }
        for(int k=2,t=1;k<=(1<<21);k<<=1,t++){
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
            int inv=ksm(n);
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
void work(){
	n=read()-1;f.resize(n+1);poly::init();
	for(int i=0;i<=n;i++)f[i]=read();
	ni[0]=ni[1]=1;for(int i=2;i<=n;i++)ni[i]=1ll*(mod-mod/i)*ni[mod%i]%mod;
    f=poly::exp(f);
    for(int i=0;i<=n;i++)write(1ll*f[i]),putchar(' ');
}

int T;
signed main(){
    // freopen("A.in","r",stdin);
    // freopen(".out","w",stdout);
    
    T=1;
    while(T--)work();
}