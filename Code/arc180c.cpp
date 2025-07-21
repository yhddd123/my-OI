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
const int maxn=110;
const int inf=1e9;

int n,a[maxn],ans;
int dp[maxn][maxn*22],f[maxn*22],B=maxn*11;
int t[22];
void work(){
    n=read();
    for(int i=1;i<=n;i++)a[i]=read();
    dp[0][B]=1;
    for(int i=1;i<=n;i++){
        for(int j=-i*10;j<=i*10;j++){
            (dp[i][j+B]+=dp[i-1][j+B])%=mod;
            if(j)(dp[i][j+a[i]+B]+=dp[i-1][j+B]+f[j+B])%=mod;
        }
        f[a[i]+B]=dp[i-1][B];
    }
    // for(int i=1;i<=n;i++){
    //     for(int j=-i*10;j<=i*10;j++)if(dp[i][j+B])cout<<i<<" "<<j<<" "<<dp[i][j+B]<<"\n";
    // }
    for(int v=-n*10;v<=n*10;v++)(ans+=dp[n][v+B])%=mod;
    printf("%lld\n",ans);
}

int T;
signed main(){
    // freopen("A.in","r",stdin);
    // freopen(".out","w",stdout);
    
    T=1;
    while(T--)work();
}