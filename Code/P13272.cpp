#include<bits/stdc++.h>
#include <cstdio>
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
const int maxn=5010;
const int inf=1e9;

int n,a[maxn],b[maxn],c[maxn];
int sum[2][maxn];
int pl[maxn],pr[maxn];
inline int ksm(int a,int b=mod-2){
    int ans=1;
    while(b){
        if(b&1)ans=ans*a%mod;
        a=a*a%mod;
        b>>=1;
    }
    return ans;
}
int preb[maxn],prec[maxn],preni[maxn];
int ni[maxn];
int mn[maxn][maxn],mul[maxn][maxn];
int f[maxn],g[maxn];
void work(){
    n=read();
    for(int i=1;i<=n;i++)a[i]=read();
    for(int i=1;i<=n;i++)b[i]=read();
    for(int i=1;i<=n;i++)c[i]=read();
    for(int i=1;i<=n;i++)ni[i]=ksm(c[i]);
    for(int i=1;i<=n;i++)sum[0][i]=sum[0][i-1],sum[1][i]=sum[1][i-1],sum[i&1][i]+=a[i];
    for(int i=1;i<=n;i++)preb[i]=preb[i-1]+b[i];
    prec[0]=1;for(int i=1;i<=n;i++)prec[i]=prec[i-1]*c[i]%mod;
    preni[0]=1;for(int i=1;i<=n;i++)preni[i]=preni[i-1]*ni[i]%mod;
    for(int i=1;i<=n;i++){
        pl[i]=1;for(int j=i,v=a[i];j>1;j--){
            v=a[j-1]-v;
            if(v<=0){pl[i]=j-1;break;}
        }
        pr[i]=n;for(int j=i,v=a[i];j<n;j++){
            v=a[j+1]-v;
            if(v<=0){pr[i]=j;break;}
        }
    }
    // for(int i=1;i<=n;i++)cout<<pl[i]<<" "<<pr[i]<<"\n";
    for(int i=1;i<=n;i++){
        mn[i][i]=b[i],mul[i][i]=ni[i];
        for(int j=i+2;j<=n;j+=2)mn[i][j]=min(mn[i][j-2],b[j]),mul[i][j]=(mul[i][j-2]+ni[j])%mod;
    }
    g[0]=1;for(int i=1;i<=n;i++){
        f[i]=-inf,g[i]=0;
        for(int j=1;j<=i;j++){
            int s0=sum[0][i]-sum[0][j-1],s1=sum[1][i]-sum[1][j-1];
            int op=s0<s1,l=max(j,pl[i]),r=min(i,pr[j]);
            // cout<<j<<" "<<i<<" "<<l<<" "<<r<<"\n";
            if(l>r)continue;
            if(s0==s1){
                f[i]=max(f[i],f[j-1]+preb[i]-preb[j-1]);
                (g[i]+=g[j-1]*prec[i]%mod*preni[j-1])%=mod;
            }
            else{
                if((l&1)!=op)l++;
                if((r&1)!=op)r--;
                if(l>r)continue;
                f[i]=max(f[i],f[j-1]+preb[i]-preb[j-1]-mn[l][r]);
                (g[i]+=g[j-1]*prec[i]%mod*preni[j-1]%mod*mul[l][r])%=mod;
            }
        }
        // cout<<i<<" "<<f[i]<<" "<<g[i]<<"\n";
    }
    printf("%lld %lld\n",f[n],g[n]);
}

int T;
signed main(){
    // freopen("A.in","r",stdin);
    // freopen("A.out","w",stdout);
    
    read();T=read();
    while(T--)work();
}