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
const int maxn=400010;
const int inf=1e9;
bool mbe;

int a,b,c,ans;
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
int calc(int x,int y){
    if(y+4<x)return 0;
    return (C(x+y,x)+mod-C(x+y,y+5))%mod;
}
void work(){
    a=read(),b=read(),c=read();ans=0;
    for(int i=0;i<=min(a,c);i++)(ans+=calc(i+4,i)*C(i+5,i)%mod*C(a-i+c-i,a-i))%=mod;
    if(a<c)(ans+=calc(a+5,c)*C(a+5,5))%=mod;
    ans=ans*ksm(fac[a+c+5]*inv[a]%mod*inv[c]%mod*inv[5]%mod)%mod;
    printf("%lld\n",ans);
}

bool med;
int T;
signed main(){
    // freopen(".in","r",stdin);
    // freopen(".out","w",stdout);
    
    // cerr<<(&mbe-&med)/1024.0/1024.0<<"\n";
    
    T=read();init(maxn-1);
    while(T--)work();
}