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
const int maxn=4100;
const int inf=1e9;

int n,m,q,k;
int t[maxn],a[maxn];
int dp[maxn][maxn];
void work(){
    n=read();q=read();
    while(q--){
        int l=read(),r=read();
        if(l>1)t[l-1]++;
        if(r<n)t[r]++;
    }
    for(int i=1;i<n;i++)if(t[i])a[++m]=t[i];
    for(k=0;(1<<k)-1<=m;k++);
    if(!k){printf("%d %d\n",k,m);return ;}
    memset(dp,0x3f,sizeof(dp));dp[0][0]=0;
    // cout<<k<<" "<<m<<"\n";
    for(int i=1;i<(1<<k);i++){
        dp[i][0]=dp[i-1][0];
        for(int j=1;j<=m;j++)dp[i][j]=min(dp[i-1][j],dp[i-1][j-1]+((i&1)?2*a[j]:0));
    }
    printf("%d %d\n",k,dp[(1<<k)-1][m]);
}

int T;
signed main(){
    // freopen("A.in","r",stdin);
    // freopen(".out","w",stdout);
    
    T=1;
    while(T--)work();
}