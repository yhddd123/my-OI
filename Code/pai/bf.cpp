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
const int maxn=1000010;
const int maxm=2010;
const int inf=1e9;
bool mbe;

inline int ksm(int a,int b=mod-2){
    int ans=1;
    while(b){
        if(b&1)ans=ans*a%mod;
        a=a*a%mod;
        b>>=1;
    }
    return ans;
}
int fac[maxn],inv[maxn];
int C(int m,int n){
    if(n<0|m<0||m<n)return 0;
    return fac[m]*inv[n]%mod*inv[m-n]%mod;}
void init(int n){
    fac[0]=1;for(int i=1;i<=n;i++)fac[i]=fac[i-1]*i%mod;
    inv[n]=ksm(fac[n]);for(int i=n-1;~i;i--)inv[i]=inv[i+1]*(i+1)%mod;
}
int n,m;
int pl[maxm],pr[maxm];
int dp[maxm][maxm],sum[maxm];
void work(){
    n=read();m=read();
    for(int i=0;i<=n;i++)pl[i]=0,pr[i]=n;
    for(int i=1;i<=m;i++){
        int k=read(),l=read(),r=read();
        pr[l]=min(pr[l],k),pl[r+1]=max(pl[r+1],k+1);
    }
    if(!m){printf("%lld\n",fac[n]);return ;}
    for(int i=n-1;i;i--)pr[i]=min(pr[i],pr[i+1]);
    for(int i=1;i<=n;i++){
    	pl[i]=max(pl[i],pl[i-1]);
    	if(pl[i]>pr[i]){puts("0");return ;}
    }
    // for(int i=1;i<=n;i++)cout<<pl[i]<<" "<<pr[i]<<"\n";
    for(int i=1;i<=n;i++){
        for(int j=0;j<=n;j++)dp[i][j]=0;
    }
    dp[0][0]=1;
    for(int i=1;i<=n;i++){
        for(int j=pl[i];j<=pr[i]&&j<i;j++){
        	dp[i][j]=dp[i-1][j]*min(i,j+1)%mod;
            for(int k=pl[i-1];k<=pr[i-1]&&k<j;k++)(dp[i][j]+=dp[i-1][k])%=mod;
            // cout<<i<<" "<<j<<" "<<dp[i][j]<<"\n";
        }
    }
    int ans=0;for(int i=0;i<n;i++)(ans+=dp[n][i])%=mod;
    printf("%lld\n",ans);
}

bool med;
int T;
signed main(){
    // freopen(".in","r",stdin);
    // freopen(".out","w",stdout);
    
    // cerr<<(&mbe-&med)/1024.0/1024.0<<"\n";
    
    init(maxn-10);
    T=read();
    while(T--)work();
}