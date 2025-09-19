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

int n,a[maxn];
int calc1(int n){return n*(n+1)/2%mod;}
int calc2(int n){return n*(n+1)*(2*n+1)/6%mod;}
int dp[maxn][2];
int calc(int op,int w){
    dp[1][0]=dp[1][1]=0,dp[1][op]=1;
    for(int i=1;i<=n;i++){
        dp[i+1][0]=(dp[i][0]*calc1(a[i]-w)+dp[i][1]*(a[i]+1-w))%mod;
        dp[i+1][1]=(dp[i][0]*(a[i]*calc1(a[i])%mod+mod-calc2(a[i]))+dp[i][1]*calc1(a[i]))%mod;
        // cout<<dp[i+1][0]<<" "<<dp[i+1][1]<<"\n";
    }
    // cout<<dp[n+1][op]<<"\n";
    return dp[n+1][op]-1;
}
void work(){
    n=read();
    for(int i=1;i<=n;i++)a[i]=read();a[n+1]=a[1];
    printf("%lld\n",(calc(0,0)+calc(1,0)-calc(0,1)-calc(1,1)+2*mod)%mod);
}

bool med;
int T;
signed main(){
    // freopen("A.in","r",stdin);
    // freopen(".out","w",stdout);
    
    // cerr<<(&mbe-&med)/1024.0/1024.0<<"\n";
    
    T=1;
    while(T--)work();
}