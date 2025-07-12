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
const int maxn=20;
const int inf=1e9;

int n,a[maxn],ans;
int f[1<<maxn],h[1<<maxn],g[1<<maxn],sum[1<<maxn];
void work(){
    n=read();
    for(int i=0;i<n;i++)a[i]=read();
    for(int s=1;s<(1<<n);s++)sum[s]=sum[s^(s&(-s))]+a[__lg(s&(-s))];
    f[0]=1;for(int s=1;s<(1<<n);s++)if(sum[s]>=0){
        for(int i=0;i<n;i++)if(s&(1<<i))(f[s]+=f[s^(1<<i)])%=mod;
    }
    for(int s=(1<<n)-1;~s;s--){
        for(int i=0;i<n;i++)if(s&(1<<i))(h[s]+=f[s^(1<<i)])%=mod;
    }
    g[0]=1;for(int s=1;s<(1<<n);s++)if(sum[s]<0){
        for(int i=0;i<n;i++)if(s&(1<<i))(g[s]+=g[s^(1<<i)])%=mod;
    }
    for(int s=0;s<(1<<n);s++)(ans+=h[s]*g[((1<<n)-1)^s]%mod*(sum[s]%mod+mod))%=mod;
    printf("%lld\n",ans);
}

int T;
signed main(){
    // freopen("A.in","r",stdin);
    // freopen(".out","w",stdout);
    
    T=1;
    while(T--)work();
}