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

int n,m,ans;
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
    if(m<0||n<0||m<n)return 0;
    return fac[m]*inv[n]%mod*inv[m-n]%mod;
}
int calc(int n,int m,int l,int r){
    int res=0;
    for(int i=-m/(r-l)-1;i<=(n+r)/(r-l)+1;i++)(res+=C(n+m,n-i*(r-l))+mod-C(n+m,n-i*(r-l)+r))%=mod;
    return res;
}
void work(){
    n=read();m=read();
    if(m>n){puts("0");return ;}
    fac[0]=1;for(int i=1;i<=2*n;i++)fac[i]=fac[i-1]*i%mod;
    inv[2*n]=ksm(fac[2*n]);for(int i=2*n-1;~i;i--)inv[i]=inv[i+1]*(i+1)%mod;
    printf("%lld\n",calc(n,n,-1,m+1));
}

int T;
signed main(){
    // freopen("A.in","r",stdin);
    // freopen(".out","w",stdout);
    
    T=1;
    while(T--)work();
}