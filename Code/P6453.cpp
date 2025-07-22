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
const int maxn=510;
const int maxm=1000010;
const int inf=1e9;

int n,k,a[maxn];
int dp[maxn][maxn],f[maxn];
inline int ksm(int a,int b=mod-2){
    int ans=1;
    while(b){
        if(b&1)ans=ans*a%mod;
        a=a*a%mod;
        b>>=1;
    }
    return ans;
}
int fac[maxm],inv[maxm];
int C(int m,int n){
    if(m<n||m<0||n<0)return 0;
    return fac[m]*inv[n]%mod*inv[m-n]%mod;}
int ls[maxn],rs[maxn];
int dfs(int fa,int l,int r){
    if(l>r)return 0;
    int u=l;for(int i=l+1;i<=r;i++)if(a[i]<a[u])u=i;
    ls[u]=dfs(u,l,u-1),rs[u]=dfs(u,u+1,r);
    for(int i=0;i<=k;i++){
        f[i]=0;for(int j=0;j<=i;j++)(f[i]+=dp[ls[u]][j]*dp[rs[u]][i-j])%=mod;
    }
    for(int i=0;i<=k;i++){
        for(int j=0;j<=i;j++)(dp[u][i]+=C(a[u]-a[fa],i-j)*C(r-l+1-j,i-j)%mod*fac[i-j]%mod*f[j])%=mod;
    }
    // cout<<u<<" "<<dp[u][0]<<" "<<dp[u][1]<<" "<<dp[u][2]<<"\n";
    return u;
}
void work(){
    n=read();k=read();
    for(int i=1;i<=n;i++)a[i]=read();
    fac[0]=1;for(int i=1;i<=maxm-10;i++)fac[i]=fac[i-1]*i%mod;
    inv[maxm-10]=ksm(fac[maxm-10]);for(int i=maxm-11;~i;i--)inv[i]=inv[i+1]*(i+1)%mod;
    dp[0][0]=1;int rt=dfs(0,1,n);
    printf("%lld\n",dp[rt][k]);
}

int T;
signed main(){
    // freopen("A.in","r",stdin);
    // freopen(".out","w",stdout);
    
    T=1;
    while(T--)work();
}