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
const int maxn=2010;
const int inf=1e9;

int n,a[maxn],ans;
int dp[maxn][maxn][3],sum[maxn];
void work(){
    for(int i=1;i<=n;i++)a[i]=read();
    for(int i=1;i<=n;i++){
        dp[1][i][0]=a[i];
        dp[1][i][1]=(i-1)*a[i]%mod;
        dp[1][i][2]=(i-1)*(i-1)*a[i]%mod;
    }
    for(int i=2;i<=n-2;i++){
        for(int j=1;j<=n;j++)for(int k:{0,1,2})dp[i][j][k]=0;
        for(int j=1;j<=n;j++){
            (dp[i][j][0]+=dp[i-1][j][1]*a[j])%=mod;
            (dp[i][j][1]+=dp[i-1][j][2]*a[j])%=mod;
        }
        for(int j=1;j<=n;j++){
            sum[j]=dp[i-1][j][2];
            (sum[j]+=j*dp[i-1][j][1])%=mod;
            (sum[j]+=j*j*dp[i-1][j][0])%=mod;
        }
        for(int j=1;j<=n;j++)(sum[j]+=sum[j-1])%=mod;
        for(int j=1;j<=n;j++)(dp[i][j][2]+=sum[j-1]*a[j])%=mod;
        for(int j=1;j<=n;j++)sum[j]=dp[i-1][j][0];
        for(int j=n-1;j;j--)(sum[j]+=sum[j+1])%=mod;
        for(int j=1;j<=n;j++){
            (dp[i][j][0]+=sum[j]*a[j])%=mod;
            (dp[i][j][1]+=(j-1)*sum[j]%mod*a[j])%=mod;
            (dp[i][j][2]+=(j-1)*(j-1)*sum[j]%mod*a[j])%=mod;
        }
    }
    ans=0;for(int j=1;j<=n;j++){
        (ans+=j*j*dp[n-2][j][0])%=mod;
        (ans+=j*dp[n-2][j][1])%=mod;
        (ans+=dp[n-2][j][2])%=mod;
    }
    printf("%lld\n",ans);
}

int T;
signed main(){
    // freopen("A.in","r",stdin);
    // freopen(".out","w",stdout);
    
    T=1;
    while(~scanf("%lld",&n))work();
}