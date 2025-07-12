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
const int maxn=300010;
const int inf=1e9;

int n,m,a[maxn];
int f[maxn];
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
    n=read();
    for(int i=1;i<=n;i++)a[i]=read(),m+=a[i];
    f[0]=f[1]=0;for(int i=1;i<m;i++)f[i+1]=((1-(m-i)*(n-2)%mod*ksm(m)%mod*ksm(n-1)%mod+mod)*f[i]%mod+mod-i*ksm(m)%mod*f[i-1]%mod+mod-i*ksm(m)%mod)*ksm((m-i)*ksm(m)%mod*ksm(n-1)%mod)%mod;
    int ans=0;for(int i=1;i<=n;i++)ans+=f[a[i]];
    (ans+=2*mod-(n-1)*f[0]%mod-f[m])%=mod;
    printf("%lld\n",ans);
}

int T;
signed main(){
    // freopen(".in","r",stdin);
    // freopen(".out","w",stdout);
    
    T=1;
    while(T--)work();
}