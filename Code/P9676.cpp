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
const int maxn=1010;
const int maxm=210;
const int inf=1e9;

int n,a[maxn][3],ans;
int dp[2][3][maxm][maxm],cur;
void chkmx(int &u,int v){(u<v)&&(u=v);}
void work(){
    n=read();ans=0;
    for(int i=1;i<=n;i++){
        for(int j:{0,1,2})a[i][j]=read();
    }
    cur=0;
    for(int j=0;j<=2;j++){
        for(int k=0;k+1<maxm;k++){
            for(int l=0;l+1<maxm;l++)dp[0][j][k][l]=dp[1][j][k][l]=0;
        }
    }
    for(int i=1;i<=n;i++){
        for(int j=0;j<=2;j++){
            for(int k=0;k+1<maxm;k++){
                for(int l=0;l+1<maxm;l++)dp[i&1][j][k][l]=0;
            }
        }
        for(int j=0;j<=2;j++){
            for(int k=0;k+1<maxm;k++){
                for(int l=0;l+1<maxm;l++){
                    chkmx(dp[i&1][j][k==0?0:k+1][l==0?0:l+1],dp[cur][j][k][l]+a[i][j]-(k==0?0:k+1)-(l==0?0:l+1));
                    chkmx(dp[i&1][(j+1)%3][l==0?0:l+1][1],dp[cur][j][k][l]+a[i][(j+1)%3]-1-(l==0?0:l+1));
                    chkmx(dp[i&1][(j+2)%3][1][k==0?0:k+1],dp[cur][j][k][l]+a[i][(j+2)%3]-1-(k==0?0:k+1));
                }
            }
        }
        cur^=1;
    }
    for(int j=0;j<=2;j++){
        for(int k=0;k+1<maxm;k++){
            for(int l=0;l+1<maxm;l++)ans=max(ans,dp[n&1][j][k][l]);
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