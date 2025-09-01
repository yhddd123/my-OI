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
const int maxn=200010;
const int inf=1e9;

int n,m,k,ans,f[maxn];
vector<pii> pos;
int fac[maxn<<1],inv[maxn<<1];
inline int ksm(int a,int b){
    int ans=1;
    while(b){
        if(b&1)ans=ans*a%mod;
        a=a*a%mod;
        b>>=1;
    }
    return ans;
}
int C(int n,int m){
    return fac[n]*inv[m]%mod*inv[n-m]%mod;
}
void work(){
    n=read();m=read();k=read();
    for(int i=1;i<=k;i++)pos.pb({read(),read()});
    fac[0]=1;for(int i=1;i<=n+m;i++)fac[i]=fac[i-1]*i%mod;
    inv[n+m]=ksm(fac[n+m],mod-2);for(int i=n+m-1;i>=0;i--)inv[i]=inv[i+1]*(i+1)%mod;
    ans=C(n-1+m-1,n-1);
    sort(pos.begin(),pos.end());
    for(int i=0;i<pos.size();i++){
        auto[x,y]=pos[i];
        f[i]=C(x-1+y-1,x-1);
        for(int j=0;j<i;j++){
            auto[u,v]=pos[j];
            if(u<=x&&v<=y)(f[i]+=mod-f[j]*C(x-u+y-v,x-u)%mod)%=mod;
        }
        (ans+=mod-f[i]*C(n-x+m-y,n-x)%mod)%=mod;
        // cout<<i<<" "<<x<<" "<<y<<" "<<f[i]<<" "<<f[i]*C(n-x+m-y,n-x)%mod<<"\n";
    }
    printf("%lld\n",ans);
}

int T;
signed main(){
    // freopen("A.in","r",stdin);
    // freopen(".out","w",stdout);
    
    T=1;
    while(T--)work();
}