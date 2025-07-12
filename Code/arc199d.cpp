#include<bits/stdc++.h>
#include <cassert>
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

int n,m;
int fac[maxn],inv[maxn];
inline int ksm(int a,int b=mod-2){
    int ans=1;
    while(b){
        if(b&1)ans=ans*a%mod;
        a=a*a%mod;
        b>>=1;
    }
    return ans;
}
int C(int m,int n){
    if(m<0||n<0||m<n)return 0;
    return fac[m]*inv[n]%mod*inv[m-n]%mod;}
void work(){
    n=read();m=read();
    if(n<m)swap(n,m);
    vector<vector<int>> f(n+1,vector<int>(m+1)),g(n+1,vector<int>(m+1));
    vector<vector<int>> h(m+1,vector<int>(m+1));
    for(int i=1;i<=n;i++)f[i][0]=1,g[i][0]=0;
    for(int j=1;j<=m;j++)f[0][j]=1,g[0][j]=0;
    fac[0]=1;for(int i=1;i<=m;i++)fac[i]=fac[i-1]*i%mod;
    inv[m]=ksm(fac[m]);for(int i=m-1;~i;i--)inv[i]=inv[i+1]*(i+1)%mod;
    for(int j=1;j<=m;j++){
        h[j][0]=j*(j+1)/2;
        for(int k=1;k<j;k++){
           for(int p=1;p<=j-k;p++)(h[j][k]+=C(j-p,k)*(p-1))%=mod;
        }
    }
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            for(int k=0;k<j;k++){
                int val=(!k?j+1:C(j,k+1));
                (f[i][j]+=f[i-1][j-k]*val)%=mod;
                (g[i][j]+=g[i-1][j-k]*val+f[i-1][j-k]*(val*i*k%mod+h[j][k]))%=mod;
            }
            // cout<<i<<" "<<j<<" "<<f[i][j]<<" "<<g[i][j]<<"\n";
        }
    }
    printf("%lld\n",g[n][m]);
}

int T;
signed main(){
    // freopen("A.in","r",stdin);
    // freopen(".out","w",stdout);
    
    T=1;
    while(T--)work();
}