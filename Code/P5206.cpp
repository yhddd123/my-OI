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

int n,m,op;
inline int ksm(int a,int b=mod-2){
    int ans=1;
    while(b){
        if(b&1)ans=ans*a%mod;
        a=a*a%mod;
        b>>=1;
    }
    return ans;
}
namespace sub0{
    void sovle(){
        map<pii,bool> mp;
        for(int i=1;i<n;i++){
            int u=read(),v=read();
            mp[{u,v}]=mp[{v,u}]=1;
        }
        int cnt=0;
        for(int i=1;i<n;i++){
            int u=read(),v=read();
            cnt+=mp[{u,v}];
        }
        printf("%lld\n",ksm(m,n-cnt));
    }
}
namespace sub1{
    int head[maxn],tot;
    struct nd{
        int nxt,to;
    }e[maxn<<1];
    void add(int u,int v){e[++tot]={head[u],v};head[u]=tot;}
    int f[maxn][2],g[2];
    void dfs(int u,int fa){
        f[u][0]=1,f[u][1]=n;
        for(int i=head[u];i;i=e[i].nxt){
            int v=e[i].to;if(v==fa)continue;
            dfs(v,u);
            for(int j:{0,1}){
                (g[j]+=f[u][j]*f[v][1])%=mod;
                for(int k:{0,1})if(!(j&&k))(g[j|k]+=(ksm(m)-1)*f[u][j]%mod*f[v][k])%=mod;
            }
            f[u][0]=g[0],f[u][1]=g[1],g[0]=g[1]=0;
        }
    }
    void sovle(){
        for(int i=1;i<n;i++){
            int u=read(),v=read();
            add(u,v),add(v,u);
        }
        dfs(1,0);
        printf("%lld\n",f[1][1]*ksm(m,n)%mod*ksm(n*n%mod)%mod);
    }
}
int fac[maxn],inv[maxn],ni[maxn];
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
    void cdqexp(int l,int r){
        if(l==r){g[l]=::ni[l]*g[l]%mod;return ;}
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
        for(int i=0;i<=n;i++)f[i]=a[i]*i%mod,g[i]=0;
        f[0]=0,g[0]=1;cdqexp(0,n);
        return g;
    }
}
namespace sub2{
    void sovle(){
        fac[0]=1;for(int i=1;i<=n;i++)fac[i]=fac[i-1]*i%mod;
        inv[n]=ksm(fac[n]);for(int i=n-1;~i;i--)inv[i]=inv[i+1]*(i+1)%mod;
        ni[0]=1;for(int i=1;i<=n;i++)ni[i]=fac[i-1]*inv[i]%mod;
        vector<int> f(n+1);
        for(int i=1;i<=n;i++)f[i]=ksm(ksm(m)-1)*n%mod*n%mod*ksm(i,i)%mod*inv[i]%mod;
        f=poly::exp(f);
        printf("%lld\n",ksm(m,n)*fac[n]%mod*ksm(n*n%mod*n%mod*n%mod)%mod*ksm(ksm(m)-1,n)%mod*f[n]%mod);
    }
}
void work(){
    n=read();m=read();op=read();
    if(m==1){
        if(op==0)puts("1");
        if(op==1)printf("%lld\n",ksm(n,n-2));
        if(op==2)printf("%lld\n",ksm(n,2*(n-2)));
        return ;
    }
    if(op==0)return sub0::sovle();
    if(op==1)return sub1::sovle();
    if(op==2)return sub2::sovle();
}

int T;
signed main(){
    // freopen("A.in","r",stdin);
    // freopen(".out","w",stdout);
    
    T=1;
    while(T--)work();
}