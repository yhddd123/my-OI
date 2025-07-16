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
    void cdqexp(int l,int r){
        if(l==r){g[l]=ni[l]*g[l]%mod;return ;}
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
        g[0]=1;cdqexp(0,n);
        return g;
    }
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