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
const int maxn=100010;
const int inf=1e9;

int n,m,B,ans;
vector<int> a[maxn];
vector<pii> pos[maxn];
vector<int> dp[maxn];
int f[maxn];
inline int ksm(int a,int b){
    int ans=1;
    while(b){
        if(b&1)ans=ans*a%mod;
        a=a*a%mod;
        b>>=1;
    }
    return ans;
}
int fac[maxn<<1],inv[maxn<<1];
int C(int n,int m){
    return fac[n]*inv[m]%mod*inv[n-m]%mod;
}
void work(){
    n=read();m=read();B=sqrt(n*m);ans=0;
    fac[0]=1;for(int i=1;i<=n+m;i++)fac[i]=fac[i-1]*i%mod;
    inv[n+m]=ksm(fac[n+m],mod-2);for(int i=n+m-1;i>=0;i--)inv[i]=inv[i+1]*(i+1)%mod;
    for(int i=1;i<=n;i++){
        a[i].resize(m+2),dp[i].resize(m+2);
        for(int j=1;j<=m;j++)a[i][j]=read();
    }
    for(int i=1;i<=n*m;i++)pos[i].clear();
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            pos[a[i][j]].pb({i,j});
        }
    }
    for(int c=1;c<=n*m;c++)if(pos[c].size()){
        if(pos[c].size()<=B){
            // cout<<c<<" "<<pos[c].size()<<" "<<B<<"\n";
            for(int i=0;i<pos[c].size();i++){
                auto[x,y]=pos[c][i];
                f[i]=C(x-1+y-1,x-1);
                for(int j=0;j<i;j++){
                    auto[u,v]=pos[c][j];
                    if(u<=x&&v<=y)(f[i]+=mod-f[j]*C(x-u+y-v,x-u)%mod)%=mod;
                }
                (ans+=f[i]*C(n-x+m-y,n-x))%=mod;
                // cout<<i<<" "<<x<<" "<<y<<" "<<f[i]<<" "<<f[i]*C(n-x+m-y,n-x)%mod<<"\n";
            }
        }
        else{
            for(int i=1;i<=n;i++){
                for(int j=1;j<=m;j++){
                	dp[i][j]=(i==1&&j==1);
                    if(i>1)(dp[i][j]+=dp[i-1][j])%=mod;
                    if(j>1)(dp[i][j]+=dp[i][j-1])%=mod;
                    if(a[i][j]==c)(ans+=dp[i][j]*C(n-i+m-j,n-i))%=mod,dp[i][j]=0;
                }
            }
        }
    }
    printf("%lld\n",ans);
}

int T;
signed main(){
    // freopen("A.in","r",stdin);
    // freopen(".out","w",stdout);
    
    T=read();
    while(T--)work();
}