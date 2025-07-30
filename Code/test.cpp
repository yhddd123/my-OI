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
const int maxn=200010;
const int inf=1e9;
bool mbe;

int n,a[maxn],ans;
int dp[10][10];
void work(){
    n=read();
    for(int i=1;i<=n;i++)a[i]=read();
    memset(dp,-0x3f,sizeof(dp));dp[0][0]=0;
    for(int i=1;i<=n;i++){
        dp[i][0]=0;
        for(int j=1;j<=i;j++)dp[i][j]=max(dp[i-1][j],dp[i-1][j-1]+j*a[i]);
        for(int j=1;j<=i;j++)cout<<dp[i][j]<<" ";cout<<"\n";
        // for(int j=1;j<=i;j++)cout<<(dp[i][j]==dp[i-1][j]?1:0);cout<<"\n";
    }
    for(int i=1;i<=n;i++)ans=max(ans,dp[n][i]);
    printf("%lld\n",ans);
}

bool med;
int T;
signed main(){
    freopen("A.in","r",stdin);
    freopen("A.out","w",stdout);
    
    // cerr<<(&mbe-&med)/1024.0/1024.0<<"\n";
    
    T=1;
    while(T--)work();
}