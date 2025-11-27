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
bool mbe;

int n,a[maxn][maxn];
inline int ksm(int a,int b=mod-2){
    int ans=1;
    while(b){
        if(b&1)ans=ans*a%mod;
        a=a*a%mod;
        b>>=1;
    }
    return ans;
}
int f[maxn][maxn];
void work(){
    n=read();
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++)a[i][j]=read();
    }
    for(int i=1;i<n;i++){
        int p=-1;for(int j=i+1;j<=n;j++)if(a[j][i])p=j;
        if(p==-1)continue;
        for(int j=1;j<=n;j++)swap(a[p][j],a[i+1][j]);
        for(int j=1;j<=n;j++)swap(a[j][p],a[j][i+1]);
        for(int j=i+2;j<=n;j++){
            int val=a[j][i]*ksm(a[i+1][i])%mod;
            for(int k=1;k<=n;k++)(a[j][k]+=mod-val*a[i+1][k]%mod)%=mod;
            for(int k=1;k<=n;k++)(a[k][i+1]+=val*a[k][j])%=mod;
        }
    }
    // for(int i=1;i<=n;i++){
        // for(int j=1;j<=n;j++)cout<<a[i][j]<<" ";cout<<"\n";
    // }
    f[0][0]=1;
    for(int i=1;i<=n;i++){
        for(int k=0;k<i;k++)(f[i][k+1]+=f[i-1][k])%=mod,(f[i][k]+=mod-a[i][i]*f[i-1][k]%mod)%=mod;
        for(int j=1;j<i;j++){
            int val=a[j][i];for(int k=j+1;k<=i;k++)val=val*a[k][k-1]%mod;
            for(int k=0;k<=j-1;k++)(f[i][k]+=mod-val*f[j-1][k]%mod)%=mod;
        }
    }
    for(int i=0;i<=n;i++)printf("%lld ",f[n][i]);
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