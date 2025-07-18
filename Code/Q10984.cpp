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

int n,m;
char s[maxn];
pii a[maxn];
int len[maxn],dp[maxn];
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
int C(int m,int n){return fac[m]*inv[n]%mod*inv[m-n]%mod;}void inc(int &u,int v){((u+=v)>=mod)&&(u-=mod);}
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
    vector<int> add(vector<int> a,vector<int> b){
        int n=a.size()-1,m=b.size()-1;
        a.resize(max(n,m)+1);
        for(int i=0;i<=m;i++)inc(a[i],b[i]);
        return a;
    }
    vector<int> del(vector<int> a,vector<int> b){
        int n=a.size()-1,m=b.size()-1;
        a.resize(max(n,m)+1);
        for(int i=0;i<=m;i++)inc(a[i],mod-b[i]);
        return a;
    }
}
void sovle(int l,int r){
    if(l==r)return ;
    int mid=l+r>>1;
    sovle(l,mid);
    vector<int> f(mid-l+1),g(r-l+1);
    for(int i=l;i<=mid;i++)f[i-l]=dp[i];
    for(int i=1;i<=r-l;i++)g[i]=inv[i]*((i&1)?1:mod-1)%mod;
    f=poly::mul(f,g);
    for(int i=mid+1;i<=r;i++)(dp[i]+=f[i-l])%=mod;
    sovle(mid+1,r);
}
void cdq(int l,int r){
    if(l==r){
        // cout<<l<<"\n";
        // for(int i=len[l-1]+1;i<=len[l];i++)cout<<dp[i]<<" ";cout<<"\n";
        if(a[l].se)sovle(len[l-1]+1,len[l]);
        // for(int i=len[l-1]+1;i<=len[l];i++)cout<<dp[i]<<" ";cout<<"\n";
        return ;
    }
    int mid=l+r>>1;
    cdq(l,mid);
    vector<int> f(len[mid]-len[l-1]),g(len[r]-len[l-1]);
    for(int i=mid,mul=1;i>=l;i--){
        int res=1;
        for(int j=len[i];j>len[i-1];j--){
            if(a[i].se==1||a[i].se==2)f[j-len[l-1]-1]=dp[j]*mul%mod*res%mod,res=res*(mod-1)%mod;
            else if(a[i].se==3)f[j-len[l-1]-1]=dp[j]*mul%mod*res%mod,res=(1+mod-res)%mod;
        }
        if(a[i].se==2)res=(a[i].fi&1)?0:1;
        mul=mul*res%mod;
    }
    for(int i=1;i<len[r]-len[l-1];i++)g[i]=inv[i];
    f=poly::mul(f,g);
    // cout<<l<<" "<<r<<"\n";
    // for(int v:f)cout<<v<<" ";cout<<"\n";
    for(int i=mid+1,mul=1;i<=r;i++){
        int res=1;
        for(int j=len[i-1]+1;j<=len[i];j++){
            if(a[i].se==1||a[i].se==3)(dp[j]+=f[j-len[l-1]-1]*mul%mod*res)%=mod,res=res*(mod-1)%mod;
            else if(a[i].se==2)(dp[j]+=f[j-len[l-1]-1]*mul%mod*res)%=mod,res=(1+mod-res)%mod;
        }
        if(a[i].se==3)res=(a[i].fi&1)?0:1;
        mul=mul*res%mod;
    }
    cdq(mid+1,r);
}
void work(){
    n=read()-1;scanf("%s",s+1);
    a[++m]={1,1};
    for(int i=2,j=1;i<=n;i=j+1){
        j=i;
        if(s[i-1]!=s[i]){
            while(j<n&&s[j+1]!=s[j])j++;
            if((j-(i-1)+1)&1)a[++m]={(j-(i-1)+1)/2,s[i]=='>'};
            else a[++m]={(j-(i-1)+1)/2,2+(s[i]=='>')};
        }
    }
    a[++m]={1,1};
    for(int i=1;i<=m;i++)len[i]=len[i-1]+a[i].fi;
    // for(int i=1;i<=m;i++)cout<<a[i].fi<<" "<<a[i].se<<"\n";
    // for(int i=1;i<=m;i++)cout<<len[i]<<" ";cout<<"\n";
    fac[0]=1;for(int i=1;i<=n;i++)fac[i]=fac[i-1]*i%mod;
    inv[n]=ksm(fac[n]);for(int i=n-1;~i;i--)inv[i]=inv[i+1]*(i+1)%mod;
    dp[1]=1;
    cdq(1,m);
    int ans=dp[len[m]]*fac[len[m]-1]%mod;
    printf("%lld\n",ans);
}

int T;
signed main(){
    // freopen("A.in","r",stdin);
    // freopen(".out","w",stdout);
    
    T=1;
    while(T--)work();
}