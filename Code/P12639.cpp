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
const int maxn=3010;
const int inf=1e9;

int n,a[maxn],ans;
int head[maxn],tot;
struct nd{
    int nxt,to;
}e[maxn];
void add(int u,int v){e[++tot]={head[u],v};head[u]=tot;}
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
int dp[maxn][maxn],f[maxn];
int siz[maxn];
int C(int m,int n){return fac[m]*inv[n]%mod*inv[m-n]%mod;}
void dfs(int u){
    dp[u][1]=1;siz[u]=1;
    for(int i=head[u];i;i=e[i].nxt){
        int v=e[i].to;dfs(v);
        for(int j=1;j<=siz[u];j++){
            for(int k=1;k<=siz[v];k++){
                if(a[v])(f[j+k]+=dp[u][j]*dp[v][k]%mod*C(siz[u]+siz[v],siz[v]))%=mod;
                else{
                    (f[j+k]+=mod-dp[u][j]*dp[v][k]%mod*C(siz[u]+siz[v],siz[v])%mod)%=mod;
                    (f[j]+=dp[u][j]*dp[v][k]%mod*C(siz[u]+siz[v],siz[v]))%=mod;
                }
            }
        }
        siz[u]+=siz[v];
        for(int j=1;j<=siz[u];j++)dp[u][j]=f[j],f[j]=0;
    }
    for(int i=1;i<=siz[u];i++)dp[u][i]=dp[u][i]*ni[i]%mod;
    // cout<<u<<"\n";
    // for(int i=1;i<=siz[u];i++)cout<<dp[u][i]<<" ";cout<<"\n";
}
void work(){
    n=read();
    for(int i=2;i<=n;i++){
        add(read(),i);
        char ch=getchar();while(ch!='<'&&ch!='>')ch=getchar();
        a[i]=(ch=='<');
    }
    fac[0]=1;for(int i=1;i<=n;i++)fac[i]=fac[i-1]*i%mod;
    inv[n]=ksm(fac[n]);for(int i=n-1;~i;i--)inv[i]=inv[i+1]*(i+1)%mod;
    for(int i=1;i<=n;i++)ni[i]=fac[i-1]*inv[i]%mod;
    dfs(1);
    for(int i=1;i<=n;i++)(ans+=dp[1][i])%=mod;
    printf("%lld\n",ans);
}

int T;
signed main(){
    freopen("A.in","r",stdin);
    // freopen(".out","w",stdout);
    
    T=1;
    while(T--)work();
}