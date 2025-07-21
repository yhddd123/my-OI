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
const int maxn=10000010;
const int inf=1e9;

int n,a,b,q;
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
    if(m<n||m<0||n<0)return 0;
    return fac[m]*inv[n]%mod*inv[m-n]%mod;
}
int f[maxn],g[maxn];
void work(){
    n=read();a=read(),b=read();q=read();
    fac[0]=1;for(int i=1;i<=n;i++)fac[i]=fac[i-1]*i%mod;
    inv[n]=ksm(fac[n]);for(int i=n-1;~i;i--)inv[i]=inv[i+1]*(i+1)%mod;
    for(int i=b-n+2;i<b;i++)(f[n]+=C(n-n,i-1))%=mod;
    for(int k=n-1;k>2;k--)f[k]=(f[k+1]*2+mod-C(n-k-1,b-2)+mod-C(n-k-1,b-k))%mod;
    for(int i=a-n+2;i<a;i++)(g[n]+=C(n-n,i-1))%=mod;
    for(int k=n-1;k>2;k--)g[k]=(g[k+1]*2+mod-C(n-k-1,a-2)+mod-C(n-k-1,a-k-1+2-1))%mod;
    while(q--){
        int k=read();
        if(k==1){
            printf("%lld\n",C(n-k,a-1)*C(n-k,b-1)%mod);
            continue;
        }
        int ans=(C(n-k,a-1)*C(n-k,b-1)+C(n-k,n-a)*C(n-k,b-1)+C(n-k,a-1)*C(n-k,n-b)+C(n-k,n-a)*C(n-k,n-b))%mod*3*ksm(4,k-2)%mod;
        (ans+=(C(n-k,a-1)*f[k]+C(n-k,n-a)*f[k]+C(n-k,b-1)*g[k]+C(n-k,n-b)*g[k])%mod*2*ksm(4,k-2))%=mod;
        printf("%lld\n",ans);
    }
}

int T;
signed main(){
    // freopen("A.in","r",stdin);
    // freopen(".out","w",stdout);
    
    T=1;
    while(T--)work();
}