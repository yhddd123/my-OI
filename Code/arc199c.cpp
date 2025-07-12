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

int n,m,a[maxn];
int to[maxn];
bool vis[maxn][maxn];
int f[maxn][maxn],g[maxn][maxn];
void work(){
    n=read();m=read();
    for(int i=1;i<=n;i++)a[i]=read();
    int d=n+1-a[1];for(int i=1;i<=n;i++)a[i]=(a[i]+d-1)%n+1;
    for(int i=1;i<=n;i++)to[a[i]]=i;
    for(int i=2;i<=n;i++)for(int j=i;j<=n;j++)vis[i][j]=1;
    m--;while(m--){
        for(int i=1;i<=n;i++)a[i]=read();
        int d=n+1-a[1];for(int i=1;i<=n;i++)a[i]=(a[i]+d-1)%n+1;
        for(int i=2;i<=n;i++){
            int mn=a[to[i]],mx=a[to[i]];
            for(int j=i+1;j<=n;j++){
                mn=min(mn,a[to[j]]),mx=max(mx,a[to[j]]);
                if(mx-mn+1!=j-i+1)vis[i][j]=0;
            }
        }
    }
    // for(int i=1;i<=n;i++){
    //     for(int j=i;j<=n;j++)cout<<vis[i][j];cout<<"\n";
    // }
    for(int i=2;i<=n+1;i++)g[i][i-1]=1;
    for(int i=2;i<=n;i++)f[i][i]=g[i][i]=1;
    for(int l=2;l<n;l++){
        for(int i=2,j=i+l-1;j<=n;i++,j++){
            if(vis[i][j]){
                for(int k=i;k<=j;k++)(f[i][j]+=g[i][k-1]*g[k+1][j])%=mod;
                (g[i][j]+=f[i][j])%=mod;
            }
            for(int k=i;k<j;k++)(g[i][j]+=g[i][k]*f[k+1][j])%=mod;
            // cout<<i<<" "<<j<<" "<<f[i][j]<<" "<<g[i][j]<<"\n";
        }
    }
    printf("%lld\n",g[2][n]);
}

int T;
signed main(){
    // freopen("A.in","r",stdin);
    // freopen(".out","w",stdout);
    
    T=1;
    while(T--)work();
}