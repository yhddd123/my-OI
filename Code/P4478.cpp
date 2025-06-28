#include<bits/stdc++.h>
#define int long long
// #define mod 998244353ll
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
const int maxm=210;

// 1019663265 = 3 × 5 × 6793 × 10007

int n,m,k,p;
pii a[maxm];
int dp[maxm];
int fac[maxn],inv[maxn];
inline int ksm(int a,int b,int mod){
    int res=1;
    while(b){
        if(b&1)res=res*a%mod;
        a=a*a%mod;
        b>>=1;
    }
    return res;
}
int C(int n,int m,int mod){
    if(m>n)return 0;
    return fac[n]*inv[m]%mod*inv[n-m]%mod;
}
int lucas(int n,int m,int mod){
    if(m==0)return 1;
    return C(n%mod,m%mod,mod)*lucas(n/mod,m/mod,mod)%mod;
}
void work(){
    n=read();m=read();k=read();p=read();
    for(int i=1;i<=k;i++)a[i]={read(),read()};a[++k]={n,m};
    sort(a+1,a+k+1);
    auto in=[&](pii u,pii v){return u.fi<=v.fi&&u.se<=v.se;};
    auto sovle=[&](int mod){
        fac[0]=1;for(int i=1;i<mod;i++)fac[i]=fac[i-1]*i%mod;
        inv[mod-1]=ksm(fac[mod-1],mod-2,mod);
        for(int i=mod-2;i>=0;i--)inv[i]=inv[i+1]*(i+1)%mod;
        int ans=0;
        for(int i=1;i<=k;i++){
            dp[i]=lucas(a[i].fi+a[i].se,a[i].fi,mod);
            for(int j=1;j<i;j++)if(in(a[j],a[i])){
                dp[i]=(dp[i]-dp[j]*lucas(a[i].fi-a[j].fi+a[i].se-a[j].se,a[i].fi-a[j].fi,mod)%mod+mod)%mod;
            }
        }
        return dp[k];
    };
    if(p==1000003)printf("%lld\n",sovle(p));
    else{
        int mul=1,ans=0;
        for(auto mod:{3,5,6793,10007}){
            int res=sovle(mod);
            while(ans%mod!=res)(ans+=mul)%=p;
            mul=mul*mod;
        }
        printf("%lld\n",ans);
    }
}

int T;
signed main(){
    // freopen("P4478.in","r",stdin);
    // freopen(".out","w",stdout);
    
    T=1;
    while(T--)work();
}