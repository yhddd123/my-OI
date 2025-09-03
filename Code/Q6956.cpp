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
const int maxn=1000010;
const int inf=1e9;

int n,k,ans;
int fac[maxn];
inline int ksm(int a,int b=mod-2){
    int ans=1;
    while(b){
        if(b&1)ans=ans*a%mod;
        a=a*a%mod;
        b>>=1;
    }
    return ans;
}
void work(){
    n=read();k=read();ans=fac[n]*(k==n?fac[n-1]:fac[k]*ksm(k,n-k-1)%mod)%mod;
    printf("%lld\n",ans);
}

int T;
signed main(){
    // freopen(".in","r",stdin);
    // freopen(".out","w",stdout);
    
    n=1000000;
    fac[0]=1;for(int i=1;i<=n;i++)fac[i]=fac[i-1]*i%mod;

    T=read();
    while(T--)work();
}