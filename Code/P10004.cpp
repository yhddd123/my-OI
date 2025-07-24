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
const int maxn=510;
const int inf=1e9;

int n,mod;
int f[maxn][maxn],g[maxn][maxn];
inline int ksm(int a,int b=mod-2){
    int ans=1;
    while(b){
        if(b&1)ans=ans*a%mod;
        a=a*a%mod;
        b>>=1;
    }
    return ans;
}
int fac[maxn*maxn],inv[maxn*maxn];
int C(int m,int n){return fac[m]*inv[n]%mod*inv[m-n]%mod;}
int c[maxn][maxn];
void work(){
    n=read();mod=read();
    fac[0]=1;for(int i=1;i<=n*(n+1);i++)fac[i]=fac[i-1]*i%mod;
    inv[n*(n+1)]=ksm(fac[n*(n+1)]);for(int i=n*(n+1)-1;~i;i--)inv[i]=inv[i+1]*(i+1)%mod;
    for(int i=0;i<=n;i++){
        c[i][0]=1;for(int j=1;j<=i;j++)c[i][j]=(c[i-1][j]+c[i-1][j-1])%mod;
        for(int j=0;j<=i;j++)c[i][j]=(((i-j)&1)?mod-1:1)*c[i][j]%mod;
    }
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++)f[i][j]=C(i*j+n-1,n);
    }
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            for(int k=1;k<=j;k++)(g[i][j]+=c[j][k]*f[i][k])%=mod;
        }
    }
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++)f[i][j]=g[i][j],g[i][j]=0;
    }
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            for(int k=1;k<=i;k++)(g[i][j]+=c[i][k]*f[k][j])%=mod;
        }
    }
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++)f[i][j]=g[i][j],g[i][j]=0;
    }
    // for(int i=1;i<=n;i++){
    //     for(int j=1;j<=n;j++)cout<<f[i][j]<<" ";cout<<"\n";
    // }
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++)g[n-i][n-j]=f[i][j];
    }
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++)f[i][j]=g[i][j],g[i][j]=0;
    }
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            for(int k=j;k<n;k++)(g[i][j]+=c[k][j]*f[i][k])%=mod;
        }
    }
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++)f[i][j]=g[i][j],g[i][j]=0;
    }
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            for(int k=i;k<n;k++)(g[i][j]+=c[k][i]*f[k][j])%=mod;
        }
    }
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++)f[i][j]=g[i][j],g[i][j]=0;
    }
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++)printf("%lld ",f[i][j]);puts("");
    }
}

int T;
signed main(){
    // freopen("A.in","r",stdin);
    // freopen("A.out","w",stdout);
    
    T=1;
    while(T--)work();
}