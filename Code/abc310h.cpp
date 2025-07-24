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
const int maxn=610;
const int inf=1e18;

int n,m,v=300,ans=inf;
pii a[maxn];
int f[maxn][maxn],g[maxn],h[maxn*maxn];
void work(){
    n=read();m=read();
    for(int i=1;i<=n;i++)a[i]={-read(),read()};
    memset(f,-0x3f,sizeof(f));f[0][0]=0;
    for(int i=1;i<=2*v;i++){
        for(int j=1;j<=n;j++){
            for(int k=max(0ll,a[j].fi);k<=min(2*v,2*v+a[j].fi);k++){
                f[i][k]=max(f[i][k],f[i-1][k-a[j].fi]+a[j].se);
            }
        }
        // for(int j=0;j<=2*v;j++)cout<<f[i][j]<<" ";cout<<"\n";
        for(int j=0;j<=2*v;j++)g[i]=max(g[i],f[i][j]);
    }
    int id=1;for(int i=1;i<=2*v;i++)if(g[i]*id>g[id]*i)id=i;
    // cout<<id<<" "<<g[id]<<"\n";
    memset(h,-0x3f,sizeof(h));h[0]=0;
    for(int i=0;i<=2*v;i++){
        for(int j=i;j<=4*v*v;j++)h[j]=max(h[j],h[j-i]+g[i]);
    }
    for(int i=0;i<=4*v*v;i++)ans=min(ans,i+(m-h[i]+g[id]-1)/g[id]*id);
    printf("%lld\n",ans);
}

int T;
signed main(){
    // freopen("A.in","r",stdin);
    // freopen("A.out","w",stdout);
    
    T=1;
    while(T--)work();
}