#include<bits/stdc++.h>
// #define int long long
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
const int maxn=15010;
const int inf=1e9;

int n,a[maxn];
int dp[maxn][maxn];
int pos[maxn];
void work(){
    n=read();
    for(int i=1;i<=n;i++)a[i]=read();
    for(int i=n;i;i--){
        dp[i][i]=a[i];
        for(int j=1;j<=n;j++)pos[j]=0;
        for(int j=i+1;j<=n;j++){
            if(!pos[a[j]]&&dp[i][j-1]>=a[j]-1)pos[a[j]]=j;
            if(a[j]<a[i])dp[i][j]=dp[i][j-1];
            else if(a[j]==a[i])dp[i][j]=dp[i][j-1]+1;
            else dp[i][j]=max(dp[i][j-1],dp[pos[a[j]]][j]);
        }
    }
    int ans=0;for(int i=1;i<=n;i++)if(a[i]==1)ans=max(ans,dp[i][n]);
    printf("%d\n",ans);
}

int T;
signed main(){
    // freopen("A.in","r",stdin);
    // freopen(".out","w",stdout);
    
    T=read();
    while(T--)work();
}