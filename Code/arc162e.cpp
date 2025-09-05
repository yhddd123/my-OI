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
const int maxn=510;
const int inf=1e9;

int n,a[maxn],sum[maxn];
int c[maxn][maxn];
int dp[maxn][maxn][maxn];
void work(){
    n=read();
    for(int i=1;i<=n;i++)a[i]=read(),sum[a[i]]++;
    for(int i=n;i;i--)sum[i]+=sum[i+1];
    for(int i=0;i<=n;i++){
        c[i][0]=1;for(int j=1;j<=i;j++)c[i][j]=(c[i-1][j]+c[i-1][j-1])%mod;
    }
    dp[n+1][0][0]=1;
    for(int i=n;i;i--){
        for(int j=0;(i+1)*j<=sum[i+1];j++){
            for(int k=(i+1)*j;k<=sum[i+1];k++)if(dp[i+1][j][k]){
            	// cout<<i+1<<" "<<j<<" "<<k<<" "<<dp[i+1][j][k]<<"\n";
                for(int l=0,mul=1;k+i*l<=sum[i];mul=mul*c[sum[i]-k-l*i][i]%mod,l++){
                	(dp[i][j+l][k+i*l]+=c[sum[i]-j][l]*mul%mod*dp[i+1][j][k])%=mod;
                }
            }
        }
    }
    int ans=0;for(int j=1;j<=sum[1];j++)(ans+=dp[1][j][n])%=mod;
    printf("%lld\n",ans);
}

int T;
signed main(){
    // freopen(".in","r",stdin);
    // freopen(".out","w",stdout);
    
    T=1;
    while(T--)work();
}