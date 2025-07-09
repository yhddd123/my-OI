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
const int maxn=100010;

int n,d,dd;
char s[maxn];
int dp[maxn][2];
int a[maxn];
int pre[maxn],pw[maxn];
int val[maxn],ni[maxn];
int v[maxn];
void exgcd(int a,int b,int &x,int &y){
    if(!b){x=1,y=0;return ;}
    exgcd(b,a%b,y,x);
    y-=a/b*x;
}
int inv(int v,int p){
    int x=0,y=0;exgcd(v,p,x,y);
    return (x%p+p)%p;
}
void work(){
    scanf("%s",s+1);n=strlen(s+1);d=dd=read();
    while(dd%2==0)dd/=2;
    while(dd%5==0)dd/=5;
    for(int i=1;i<=n;i++)a[i]=s[i]-'0',pre[i]=(pre[i-1]*10+a[i])%d,val[i]=(val[i-1]*10+a[i])%dd,v[i]=(v[i-1]*10+a[i])%(d/dd);
    pw[0]=1;for(int i=1;i<=n;i++)pw[i]=pw[i-1]*10%d;
    ni[0]=1,ni[1]=inv(10,dd);for(int i=2;i<=n;i++)ni[i]=ni[i-1]*ni[1]%dd;
    unordered_map<int,int> f[2];
    dp[0][0]=dp[0][1]=1;
    for(int i=1,sum=1;i<=n;i++){
        dp[i][0]=dp[i][1]=0;
        dp[i][0]=sum;
        for(int j=max(0ll,i-20);j<i;j++)if((pre[i]-pre[j]*pw[i-j]%d+d)%d==0)(dp[i][1]+=dp[j][0])%=mod;
        if(v[i]==0)(dp[i][1]+=f[0][val[i]*ni[i]%dd])%=mod;
        for(int j=max(0ll,i-20);j<i;j++)if((pre[i]-pre[j]*pw[i-j]%d+d)%d==0)(dp[i][0]+=dp[j][0]+mod-dp[j][1])%=mod;
        if(v[i]==0)(dp[i][0]+=f[1][val[i]*ni[i]%dd])%=mod;
        if(i-20>=0)(f[0][val[i-20]*ni[i-20]%dd]+=dp[i-20][0])%=mod,(f[1][val[i-20]*ni[i-20]%dd]+=dp[i-20][0]+mod-dp[i-20][1])%=mod;
        (sum+=dp[i][1])%=mod;
        // cout<<dp[i][0]<<" "<<dp[i][1]<<"\n";
    }
    printf("%lld\n",dp[n][0]);
}

int T;
signed main(){
    // freopen("A.in","r",stdin);
    // freopen(".out","w",stdout);
    
    T=read();
    for(int t=1;t<=T;t++){
        cout<<"Case #"<<t<<": ";
        work();
    }
}