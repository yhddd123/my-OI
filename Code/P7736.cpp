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
const int maxn=110;
const int inf=1e9;
bool mbe;

int k,n,a[maxn],m[maxn],ans;
int f[maxn<<1][maxn],g[maxn<<1][maxn];
void work(){
    k=read();
    for(int i=1;i<=k;i++)a[i]=read();n=a[1];
    for(int i=1;i<k;i++)m[i]=read();
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++)f[i][j]=0;
    }
    for(int i=1;i<=n;i++)f[i][i]=1;
    for(int i=1;i<k;i++){
        for(int j=1;j<=m[i];j++){
            int u=read(),v=read();
            for(int k=1;k<=n;k++)(g[v][k]+=f[u][k])%=mod;
        }
        for(int j=1;j<=2*n;j++){
            for(int k=1;k<=n;k++)f[j][k]=g[j][k],g[j][k]=0;
        }
    }
    ans=1;
    for(int i=1;i<=n;i++){
        for(int j=i+1;j<=n;j++)if(f[j][i]){
            while(f[i][i]){
                int d=f[j][i]/f[i][i];
                for(int k=i;k<=n;k++)(f[j][k]+=mod-f[i][k]*d%mod)%=mod;
                swap(f[i],f[j]),ans=mod-ans;
            }
            swap(f[i],f[j]),ans=mod-ans;
        }
    }
    for(int i=1;i<=n;i++)ans=ans*f[i][i]%mod;
    printf("%lld\n",ans);
}

bool med;
int T;
signed main(){
    freopen("A.in","r",stdin);
    freopen("A.out","w",stdout);
    
    // cerr<<(&mbe-&med)/1024.0/1024.0<<"\n";
    
    T=1;
    while(T--)work();
}