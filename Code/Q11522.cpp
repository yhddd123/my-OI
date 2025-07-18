#include<bits/stdc++.h>
#include <cstdio>
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
const int maxn=300010;
const int inf=1e9;

int n,mod,ans;
int d[maxn],dep[maxn];
int ni[maxn];
int f[maxn],g[maxn];
void work(){
    n=read();mod=read();
    ni[0]=ni[1]=1;for(int i=2;i<=n;i++)ni[i]=(mod-mod/i)*ni[mod%i]%mod;
    for(int i=1;i<=n;i++){
        for(int j=2*i;j<=n;j+=i)d[j]++;
    }
    for(int i=1;i<=n;i++){
        dep[i]=dep[i]*ni[d[i]]%mod;
        for(int j=2*i;j<=n;j+=i)(dep[j]+=1+dep[i])%=mod;
    }
    for(int i=1;i<=n;i++)(ans+=2*dep[i]*n)%=mod;
    for(int i=n;i;i--){
        for(int j=i;j<=n;j+=i)g[j]=0;
        g[i]=1;for(int j=i;j<=n;j+=i){
            for(int k=2*j;k<=n;k+=j)(g[k]+=g[j]*ni[d[k]])%=mod;
        }
        for(int j=i;j<=n;j+=i)(f[i]+=g[j])%=mod;f[i]=f[i]*f[i]%mod;
        for(int j=2*i;j<=n;j+=i)(f[i]+=mod-f[j]*g[j]%mod*g[j]%mod)%=mod;
        // cout<<i<<" "<<f[i]<<"\n";
    }
    for(int i=1;i<=n;i++)(ans+=mod-2*dep[i]*f[i]%mod)%=mod;
    printf("%lld\n",ans);
}

int T;
signed main(){
    // freopen("A.in","r",stdin);
    // freopen(".out","w",stdout);
    
    T=1;
    while(T--)work();
}