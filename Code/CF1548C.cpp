#include<bits/stdc++.h>
#define int long long
#define mod 1000000007ll
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
const int maxn=3000010;
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
int fac[maxn],inv[maxn],ni[maxn];
int C(int m,int n){
    if(n<0|m<0||m<n)return 0;
    return fac[m]*inv[n]%mod*inv[m-n]%mod;}
void init(int n){
    fac[0]=1;for(int i=1;i<=n;i++)fac[i]=fac[i-1]*i%mod;
    inv[n]=ksm(fac[n]);for(int i=n-1;~i;i--)inv[i]=inv[i+1]*(i+1)%mod;
}
int n,q;
int f[maxn],g[4],h[maxn];
void work(){
    n=read();q=read();init(3*n+3);
    for(int i=0;i<=3*n+3;i++)f[i]=C(3*n+3,i);
    for(int i=0;i<=3;i++)(f[i]+=mod-C(3,i))%=mod;
    for(int i=0;i<=3;i++)g[i]=C(3,i);g[0]--;
    for(int i=3*n;i;i--){
        int d=f[i+3];h[i]=d;
        for(int j=0;j<=3;j++)(f[i+j]+=mod-d*g[j]%mod)%=mod;
    }
    while(q--){
        int p=read();
        printf("%lld\n",h[p]);
    }
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