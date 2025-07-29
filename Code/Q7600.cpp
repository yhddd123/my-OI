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
const int maxn=18;
const int maxm=110;
const int inf=1e9;
bool mbe;

int n,m,s,ans[maxn];
int sum[1<<maxn];
pii val[maxn+1];
int dp[maxn+1][maxm],num[maxn+1];
void work(){
    n=read();m=read();s=read();
    for(int i=1;i<=m;i++){
        int u=read()-1,v=read()-1;
        sum[(1<<u)|(1<<v)]++;
    }
    for(int i=0;i<n;i++){
        for(int s=0;s<(1<<n);s++)if(s&(1<<i))sum[s]+=sum[s^(1<<i)];
    }
    for(int s=0;s<(1<<n);s++)val[__builtin_popcount(s)]=max(val[__builtin_popcount(s)],{sum[s],s});
    for(int i=1;i<=n;i++){
        for(int j=0;j<=s;j++)dp[i][j]=dp[i-1][j];
        for(int j=i;j<=s;j++)dp[i][j]=max(dp[i][j],dp[i][j-i]+val[i].fi);
    }
    for(int i=n,j=s;i;i--){
        while(j&&dp[i][j-i]+val[i].fi==dp[i][j]){
            num[i]++;
            j-=i;
        }
    }
    for(int i=1;i<=n;i++){
        // cout<<num[i]<<" "<<val[i].fi<<" "<<val[i].se<<"\n";
        for(int j=0;j<n;j++)if(val[i].se&(1<<j))(ans[j]+=num[i])%=mod;
    }
    for(int i=0;i<n;i++)printf("%lld ",ans[i]);
}

bool med;
int T;
signed main(){
    // freopen("A.in","r",stdin);
    // freopen("A.out","w",stdout);
    
    // cerr<<(&mbe-&med)/1024.0/1024.0<<"\n";
    
    T=1;
    while(T--)work();
}