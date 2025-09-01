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
const int maxn=510;
const int inf=1e9;

int n;
char s[maxn];
inline int ksm(int a,int b){
    int ans=1;
    while(b){
        if(b&1)ans=ans*a%mod;
        a=a*a%mod;
        b>>=1;
    }
    return ans;
}
int fac[maxn],inv[maxn];
int C(int n,int m){
    if(n<m)return 0;
    return fac[n]*inv[m]%mod*inv[n-m]%mod;
}
int dp[maxn][maxn];
void work(){
    n=read();scanf("%s",s+1);
    fac[0]=1;for(int i=1;i<=n;i++)fac[i]=fac[i-1]*i%mod;
    inv[n]=ksm(fac[n],mod-2);for(int i=n-1;i>=0;i--)inv[i]=inv[i+1]*(i+1)%mod;
    dp[0][0]=1;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=i;j++){
            int p=j-1;while(p+1<=i&&s[p+1]=='R')p++;
            int vl=p-j+1;
            p=i+1;while(p-1>=j&&s[p-1]=='L')p--;
            int vr=i-p+1;
            if(vl+vr!=i-j+1)continue;
            int val=0;
            if(!vl){
                if(j==1)val=vr;
                else val=vr-1;
            }
            else if(!vr){
                if(i==n)val=vl;
                else val=vl-1;
            }
            else val=(C(vl+vr-1,vl)+C(vl+vr-1,vr))*(vl+vr-1)%mod;
            // cout<<i<<" "<<j<<" "<<vl<<" "<<vr<<" "<<val<<endl;
            for(int k=0;k<j;k++)(dp[i][k+1]+=dp[j-1][k]*C(n-j+1,i-j+1)%mod*val)%=mod;
        }
    }
    for(int i=1;i<=n;i++)printf("%lld ",dp[n][i]);
}

int T;
signed main(){
    // freopen("A.in","r",stdin);
    // freopen(".out","w",stdout);
    
    T=1;
    while(T--)work();
}