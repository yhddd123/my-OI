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

int n,k,ans;
int pre[maxn],cnt;
bool vis[maxn];
int pw[maxn];
inline int ksm(int a,int b=mod-2){
    int ans=1;
    while(b){
        if(b&1)ans=ans*a%mod;
        a=a*a%mod;
        b>>=1;
    }
    return ans;
}
void init(int n){
    pw[0]=pw[1]=1;
    for(int i=2;i<=n;i++){
        if(!vis[i])pre[++cnt]=i,pw[i]=ksm(i,n);
        for(int j=1;j<=cnt&&i*pre[j]<=n;j++){
            vis[i*pre[j]]=1,pw[i*pre[j]]=pw[i]*pw[pre[j]]%mod;
            if(i%pre[j]==0)break;
        }
    }
}
int fac[maxn],inv[maxn];
inline int C(int n,int m){
    if(m>n||!n||!m)return 0;
    return fac[n]*inv[m]%mod*inv[n-m]%mod;
}
void work(){
    n=read();k=read()-1;init(n);
    fac[0]=1;for(int i=1;i<=n+1;i++)fac[i]=fac[i-1]*i%mod;
    inv[n+1]=ksm(fac[n+1]);for(int i=n;i>=0;i--)inv[i]=inv[i+1]*(i+1)%mod;
    for(int i=1;i<=n;i++)(ans+=(((n-k-i)&1)?mod-1:1)*pw[i]%mod*C(n+1,i+k+1))%=mod;
    printf("%lld\n",ans);
}

int T;
signed main(){
    // freopen("AT_joisc2018_d.in","r",stdin);
    // freopen(".out","w",stdout);
    
    T=1;
    while(T--)work();
}   